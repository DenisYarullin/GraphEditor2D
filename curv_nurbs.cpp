////////////////////////////////////////////////////////////////////////////////
//
//                  Неоднородный рациональный B-сплайн (NURBS)
//
////////////////////////////////////////////////////////////////////////////////


#include "constraint.h"
#include "curv_abstract_curve.h"
#include "curv_nurbs.h"
#include "mb_cart_point.h"
#include "mb_vector.h"
#include <algorithm>
#include <functional>


//------------------------------------------------------------------------------
// конструктор по умолчанию
// ---
MbNurbs::MbNurbs()
  : MbCurve()
  , points()
  , degree( 0 )
  , periodic( false )
{
}


//------------------------------------------------------------------------------
// конструктор по количеству опорных точек и порядку B-сплайна
// ---
MbNurbs::MbNurbs(const vector< MbCartPoint > & _points, size_t _degree, bool _periodic )
  : MbCurve()
  , points( _points )
  , degree( _degree )
  , periodic( _periodic )
{
}


//------------------------------------------------------------------------------
// деструктор
// ---
MbNurbs::~MbNurbs()
{
}


//------------------------------------------------------------------------------
// для заданного количества опорных точек и порядка B-сплайна получить узловой вектор
// ---
void MbNurbs::SetKnotVector() const
{
  size_t maxSizeKnot = points.size() + degree;
  size_t numbMaxElem = points.size() + 2;

  knot.resize( maxSizeKnot );

  knot[0] = 0;

  for ( size_t i = 1; i < maxSizeKnot; i++ ) {
    if( periodic == false ) {
      if ( (i > degree ) && (i < numbMaxElem) )
          knot[i] = knot[i - 1] + 1;
      else
          knot[i] = knot[i - 1];
    }
    else
      knot[i] = static_cast< double >( i );
}
}


//------------------------------------------------------------------------------
// получить массив с весовыми коэффициентами
// ---
void MbNurbs::SetWeightArray() const
{
  weight.resize( points.size() );
  std::fill( weight.begin(), weight.end(), 1.0 );
}


//------------------------------------------------------------------------------
// рассчитать нормированные B-сплайны функции для заданного параметра t
// ---
void MbNurbs::CalcNormBSplineFunc( double t, vector<vector<double> > & NmiPrev ) const
{
  SetKnotVector();
  SetWeightArray();

  NmiPrev.resize( degree );
  size_t nplusc = points.size() + degree;
  //std::for_each( NmiPrev.begin(), NmiPrev.end(), std::bind2nd(std::mem_fun_ref( &vector<double>::resize), nplusc) );

  for (size_t i = 0; i < NmiPrev.size(); i++)
  {
    NmiPrev[i].resize(nplusc);
  }

  for ( size_t i = 0; i < nplusc - 2; i++ ){
    if ( ( t >= knot[i]) && (t < knot[i + 1]) )
       NmiPrev[0][i] = 1.0;
    else
       NmiPrev[0][i] = 0.0;
   }

  for( size_t k = 1; k < degree; k++ ) {

    for( size_t i  = 0; i < knot.size() - k; i++ ) {

      if ( (NmiPrev[k - 1][i] != 0) && (NmiPrev[k - 1][i + 1] != 0) )
        NmiPrev[k][i] = ( (knot[i + k + 1] - t) / (knot[i + k + 1] - knot[i + 1]) ) * NmiPrev[k - 1][i + 1]
                      + ( (t - knot[i] ) / (knot[i + k] - knot[i]) ) * NmiPrev[k - 1][i];

      else if ( NmiPrev[k - 1][i] != 0 )
        NmiPrev[k][i] = ( (t - knot[i] ) / (knot[i + k] - knot[i]) ) * NmiPrev[k - 1][i];

      else if ( NmiPrev[k - 1][i + 1] != 0 )
        NmiPrev[k][i] = ( (knot[i + k + 1] - t) / (knot[i + k + 1] - knot[i + 1]) ) * NmiPrev[k - 1][i + 1];

      else
        NmiPrev[k][i] = 0.0;
    }
  }

  if( t == knot[nplusc - 1] ) {
    NmiPrev[degree - 1][points.size()] = 1.0;
  }
}


//------------------------------------------------------------------------------
// по заданным опорным точкам и параметру t получить соответствующую точку на кривой,
// реализация через нормированные B-сплайны
// ---
void MbNurbs::CalcNurbsFromNormB( double t, MbCartPoint & point ) const
{
  vector< vector< double > > NmiPrev;

  CalcNormBSplineFunc( t, NmiPrev );

  MbCartPoint rNum;
  vector< double > NmjWj;

  if ( knot[knot.size() - 1] - t < 5e-6){
    t = knot[knot.size() - 1];
  }

  double denominatorSum = 0.0;

  for( size_t i = 0; i < points.size(); i++ ) {
      NmjWj.push_back( NmiPrev[degree-1][i] * weight[i] );
  }

  for( size_t i = 0; i < points.size(); i++ ) {
      rNum += points[i] * NmjWj[i];
      denominatorSum += NmjWj[i];
  }

  point = rNum / denominatorSum;
}


//------------------------------------------------------------------------------
// по заданному значению параметра t получить соответствующую точку
// ---
void MbNurbs::CalcPointCurve( double t, MbCartPoint & point ) const
{
  CalcNurbsFromNormB( t, point );
}


//------------------------------------------------------------------------------
// идентификатор типа кривой
// ---
MbCurve::TypeCurve MbNurbs::Type() const
{
  return Nurbs;
}


//------------------------------------------------------------------------------
// вычисление первой производной
// ---
void MbNurbs::FirstDerivative( double t, MbVector & vector ) const
{
  std::vector<std::vector<double> > Nmj;
  CalcNormBSplineFunc( t, Nmj );
  MbCartPoint wrPoint;
  MbCartPoint dwrPoint;

  w  = 0.0;
  dw = 0.0;

  for ( size_t j = 0; j < points.size(); j++ ) {
      w += Nmj[degree-1][j] * weight[j];
      wrPoint += points[j] * Nmj[degree-1][j] * weight[j];
  }

  for ( size_t j = 1; j < points.size(); j++ ) {
      dwrPoint += ( (points[j] * weight[j] - points[j - 1] * weight[j - 1])
                  / (knot[j + degree-1] - knot[j]) ) * (degree) * Nmj[degree - 1][j];

      dw += (degree) * Nmj[degree - 2][j] * ( (weight[j] - weight[j - 1])
              / (knot[j + degree-1] - knot[j]) );
  }

  wr.ax  = wrPoint.x;
  wr.ay  = wrPoint.y;
  dwr.ax = dwrPoint.x;
  dwr.ay = dwrPoint.y;

  vector.ax = ( dwr.ax * (1.0 / w) - (wr.ax / (w * w)) * dw );
  vector.ay = ( dwr.ay * (1.0 / w) - (wr.ay / (w * w)) * dw );
}


//------------------------------------------------------------------------------
// вычисление второй производной
// ---
void MbNurbs::SecondDerivative( double t, MbVector & vector ) const
{
  size_t k = 2;

  std::vector< std::vector< double > > Nmj;
  CalcNormBSplineFunc( t, Nmj );
  std::vector< std::vector< MbVector > > pkj( k + 1, std::vector< MbVector >( points.size()) );
  std::vector< std::vector< double > > wkj( k + 1, std::vector< double >( points.size()) );

  MbCartPoint d2wrPoint;

  for( size_t j = k; j < points.size(); j++ ) {
      pkj[0][j].ax = points[j].x * weight[j];
      pkj[0][j].ay = points[j].y * weight[j];
      wkj[0][j] = weight[j];
  }

  for ( size_t i = 1; i <= k; i++ ) {
      for ( size_t j = k; j < points.size(); j++ ) {
          pkj[i][j] = ( (pkj[i - 1][j] - pkj[i - 1][j - 1]) / (knot[j + degree + 1 - i -1] - knot[j]) ) * ( degree + 1 - i-1);
          wkj[i][j] = ( degree + 1 - i - 1) * ( (wkj[i - 1][j] - wkj[i - 1][j - 1]) / (knot[j + degree + 1 - i-1] - knot[j]) );
      }
  }

  for ( size_t j = k; j < points.size(); j++ ) {
      if ( degree == 1 ) {
          d2wrPoint = MbCartPoint();
          d2w = 0.0;
          break;
      }
      d2wrPoint += pkj[k][j] * Nmj[degree - k-1][j];
      d2w  += Nmj[degree - k-1][j] * wkj[k][j];
  }

  d2wr.ax = d2wrPoint.x;
  d2wr.ay = d2wrPoint.y;

  vector.ax = d2wr.ax / w - (2 * wr.ax * dw) / (w * w) - (d2w * wr.ax) / (w * w) + (2 * wr.ax * dw * dw) / (w * w * w);
  vector.ay = d2wr.ay / w - (2 * wr.ay * dw) / (w * w) - (d2w * wr.ay) / (w * w) + (2 * wr.ay * dw * dw) / (w * w * w);

  //vector = d2wr / w - ( 2 * dwr * dw ) / ( w * w ) - ( d2w * wr ) / ( w * w ) + ( 2 * wr * dw * dw) / ( w * w * w );
}


//------------------------------------------------------------------------------
// получение массива контрольных точек кривой
// ---
void MbNurbs::GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & ) const
{
  controlPoints = points;
}


//------------------------------------------------------------------------------
// получение минимального значения параметра
// ---
double MbNurbs::GetMinParam() const
{
  return degree - 1;
}


//------------------------------------------------------------------------------
// получение максимального значения параметра
// ---
double MbNurbs::GetMaxParam() const
{
  //SetKnotVector();
  return points.size() - (degree - 3);
}


//------------------------------------------------------------------------------
// изменение данных кривой
// ---
void MbNurbs::SetDataCurve( vector< MbCartPoint > & _points, vector< MbVector > &, size_t _degree )
{
  points = _points;
  degree = _degree;
}


//------------------------------------------------------------------------------
// запись в поток
// ---
ofstream & MbNurbs::out( ofstream & ofs ) const
{
  size_t size = points.size();
  ofs.write( (char *) & size, sizeof(size_t) );
  for( size_t i = 0; i < points.size(); i++ ) {
      ofs << points[i];
  }
  ofs.write( (char *) & degree, sizeof(size_t) );

  return ofs;
}


//------------------------------------------------------------------------------
// чтение из потока
// ---
ifstream & MbNurbs::in( ifstream & ifs )
{
  size_t size;
  ifs.read( (char *) & size, sizeof(size_t) );
  points.resize( size );
  for( size_t i = 0; i < points.size(); i++ ) {
      ifs >> points[i];
  }
  ifs.read( (char *) & degree, sizeof(size_t) );

  return ifs;
}
