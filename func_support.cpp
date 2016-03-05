#include "func_support.h"
#include "mb_vector.h"
#include "mb_cart_point.h"
#include "constraint.h"
#include "curv_abstract_curve.h"
#include "curv_line_segment.h"
#include "graph_curve.h"


#include <QDebug>


//------------------------------------------------------------------------------
// расстояние между произвольными точкой и отрезком
// ---
double DistBetweenPointSegment( const MbCartPoint & pSegOne, const MbCartPoint & pSegTwo, const MbCartPoint & point )
{
  MbCartPoint tempPoint;
  double a, b, c, t, r0;

  double r1 = pSegOne.GetLength( point );
  double r2 = pSegTwo.GetLength( point );
  double r12 = pSegTwo.GetLength( pSegOne );

  if ( r1 >= tempPoint.GetLength( MbCartPoint(r2, r12)) )
      return r2;

  else if ( r2 >= tempPoint.GetLength( MbCartPoint(r1, r12)) )
      return r1;

  else {
      a = pSegTwo.y - pSegOne.y;
      b = pSegOne.x - pSegTwo.x;
      c = - pSegOne.x * ( pSegTwo.y - pSegOne.y ) + pSegOne.y * ( pSegTwo.x - pSegOne.x ) ;
      t =  tempPoint.GetLength( MbCartPoint(a, b) );

      if (  c > 0) {

          a = - a;
          b = - b;
          c = - c;
      }

      r0 = ( a * point.x + b * point.y + c ) / t;

      return r0;
  }
}


//------------------------------------------------------------------------------
// нахождение начальных приближений с помощью пересечения прямых
// ---
void FindInitApprLine( const MbCurvePtr curve1,  const MbCurvePtr curve2, vector< std:: pair< double, double> > & initT )
{
  double w1, w2;
  double t10, t20;
  double lenFirstVec, lenSecondVec;
  MbCartPoint p1, p2;
  MbVector v1, v2;
  MbVector n1, n2;
  vector< double > param1;
  vector< double > param2;

  curve1->StepParameter( curve1->GetMinParam(), curve1->GetMaxParam(), param1 );
  curve2->StepParameter( curve2->GetMinParam(), curve2->GetMaxParam(), param2 );

  for ( std::vector< double >::iterator i = param1.begin(); i + 1 != param1.end(); ++i ) {
  
    curve1->CalcPointCurve ( (*i), p1 );
    curve1->FirstDerivative( (*i), v1 );

    lenFirstVec = 1.0 / v1.LengthOfVector();

    n1.ax = - lenFirstVec * v1.ay;
    n1.ay =   lenFirstVec * v1.ax;

    for ( std::vector< double >::iterator j = param2.begin(); j + 1 != param2.end(); ++j ){
    
      curve2->CalcPointCurve( (*j), p2 );
      curve2->FirstDerivative( (*j), v2 );

      lenSecondVec = 1.0 / v2.LengthOfVector();

      n2.ax = - lenSecondVec * v2.ay;
      n2.ay =   lenSecondVec * v2.ax;

      w1 = ( n2 * ( p2 - p1 ) ) / ( n2 * v1 );
      w2 = ( n1 * ( p1 - p2 ) ) / ( n1 * v2 );

      if ( w1 >= - (*(i + 1) - *i) && w1 <=  (*(i + 1) - *i) &&
           w2 >= - (*(j + 1) - *j) && w2 <=  (*(j + 1) - *j) )
      {
          t10 = (*i) + w1;
          t20 = (*j) + w2;
          if ( t10 > 0.0 && t20 > 0.0 )
              initT.push_back( std::make_pair(t10, t20) );
      }
    }
  }
}


//------------------------------------------------------------------------------
// нахождение пересечений кривых
// ---
void ComputeIntersects(const MbCurvePtr curve1, const MbCurvePtr curve2, vector< MbCartPoint > & roots )
{
  vector< std::pair< double, double > > initT;
  vector< std::pair< double, double > > rootT;

  double t1Max = curve1->GetMaxParam();
  double t2Max = curve2->GetMaxParam();
  double t1Min = curve1->GetMinParam();
  double t2Min = curve2->GetMinParam();

  double Jacobian[2][2];
  double MatrixA1[2][2];
  double MatrixA2[2][2];

  MbCartPoint p1, p2;
  MbVector    v1, v2;

  double t1Init, t2Init;
  double t1Root, t2Root;

  int j = 0;

  FindInitApprLine( curve1, curve2, initT );

  for ( vector< std::pair< double, double > >::iterator i = initT.begin(); i != initT.end(); ++i ) {

    j = 0;

    t1Init = (*i).first;
    t2Init = (*i).second;

    while( true ) {

      j++;

      if (j > 128) break;

      curve1->FirstDerivative( t1Init, v1 );
      curve2->FirstDerivative( t2Init, v2 );

      curve1->CalcPointCurve( t1Init, p1 );
      curve2->CalcPointCurve( t2Init, p2 );

      Jacobian[0][0] =   v1.ax;
      Jacobian[0][1] = - v2.ax;
      Jacobian[1][0] =   v1.ay;
      Jacobian[1][1] = - v2.ay;

      MatrixA1[0][0] = p1.x - p2.x;
      MatrixA1[0][1] = - v2.ax;
      MatrixA1[1][0] = p1.y - p2.y;
      MatrixA1[1][1] = - v2.ay;

      MatrixA2[0][0] = v1.ax;
      MatrixA2[0][1] = p1.x - p2.x;
      MatrixA2[1][0] = v1.ay;
      MatrixA2[1][1] = p1.y - p2.y;

      double detJ  = Jacobian[0][0] * Jacobian[1][1] - Jacobian[0][1] * Jacobian[1][0];
      double detA1 = MatrixA1[0][0] * MatrixA1[1][1] - MatrixA1[0][1] * MatrixA1[1][0];
      double detA2 = MatrixA2[0][0] * MatrixA2[1][1] - MatrixA2[0][1] * MatrixA2[1][0];

      if ( detA1 / detJ < t1Max - t1Min && detA2 / detJ < t2Max - t2Min )
      {
          t1Root = t1Init - ( detA1 / detJ );
          t2Root = t2Init - ( detA2 / detJ );
      }
      else
          break;

      if ( fabs(t1Root - t1Init) < EPSILON && fabs(t2Root - t2Init) < EPSILON) {
          rootT.push_back( std::make_pair (t1Root, t2Root) );
          break;
      }
      else {
          t1Init = t1Root;
          t2Init = t2Root;
      }
    }
  }
  vector< std::pair< double, double > >::iterator l = unique( rootT.begin(), rootT.end(), DeleteDuplicate );
  rootT.erase( l, rootT.end() );

  for ( vector< std::pair< double, double > >::iterator k = rootT.begin(); k != rootT.end(); ++k ) {
    curve1->CalcPointCurve( (*k).first, p1 );
    //curve2->CalcPointCurve( (*k).second, p2 );
    roots.push_back( p1 );
    //roots.push_back( p2 );
  }

  /*for ( vector< std::pair< double, double > >::iterator k = initT.begin(); k != initT.end(); ++k ) {
      curve1->CalcPointCurve( (*k).first, p1 );
      curve2->CalcPointCurve( (*k).second, p2 );
      roots.push_back( MbCartPoint(p1) );
  }*/

}


//------------------------------------------------------------------------------
// предикат для сортировки  vector< pair< MCurve *, double > > по second,
// second - наименьшее расстояние от пользовательского места клика мышью.
// ---
bool SortPair(const pair< GraphCurve, double > & p1, const pair< GraphCurve, double > & p2 )
{
    return p1.second < p2.second;
}


//------------------------------------------------------------------------------
// предикат для удаления из vector< GraphCurve > по признаку селектирвоанности
// ---
bool DeleteSelect( const GraphCurve & curve )
{
    return curve.IsSelected() == true;
}


//------------------------------------------------------------------------------
// предикат для удаления дублирующихся элементов из vector< pair< double, double > >
// ---
bool DeleteDuplicate( const pair< double, double > & p1, const pair< double, double >  & p2 )
{
  return ( fabs(p1.first - p2.first) < XI) && (fabs(p1.second - p2.second) < XI );
}


//------------------------------------------------------------------------------
// реализация конструктора для функционального объекта по поиску кривых в vector< GraphCurve >
// ---
FindFirst::FindFirst(const MbCurvePtr & i )
    :toFind( i )
{
}


//------------------------------------------------------------------------------
// реализация оператора () для функционального объекта по поиску мат кривых в vector< GraphCurve >
// ---
bool FindFirst::operator ()( const GraphCurve & p ) const
{
    return p.GetCurve() == toFind;
}
