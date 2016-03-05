////////////////////////////////////////////////////////////////////////////////
//
//                          Эллипс
//
////////////////////////////////////////////////////////////////////////////////


#include "constraint.h"
#include "mb_cart_point.h"
#include "curv_abstract_curve.h"
#include "curv_ellipse.h"


//------------------------------------------------------------------------------
// конструктор по умолчанию
// ---
MbEllipse::MbEllipse()
  : MbCurve()
  , center()
  , xa()
  , yb()
{
}


//------------------------------------------------------------------------------
// конструктор по центральной точке, точках малой и большой полуоси
// ---
MbEllipse::MbEllipse( MbCartPoint & centerP, MbCartPoint & minP, MbCartPoint & maxP )
  : MbCurve()
  , center( centerP )
  , xa()
  , yb()
{
  xa = maxP - centerP;

  yb.ax = - xa.ay;
  yb.ay =   xa.ax;
  yb.Normalization();

  yb =  yb * ( yb.ax * (minP.x - centerP.x) +  yb.ay * (minP.y - centerP.y) );

}


//------------------------------------------------------------------------------
// конструктор по центральной точке и двум векторам
// ---
MbEllipse::MbEllipse( MbCartPoint & centerPoint, MbVector & xaVec, MbVector & xbVec )
  : MbCurve()
  , center( centerPoint )
  , xa( xaVec )
  , yb( xbVec )
{
}


//------------------------------------------------------------------------------
// конструктор копирования
// ---
MbEllipse::MbEllipse( const MbEllipse & other ) : MbCurve()
{
  center = other.center;
  xa = other.xa;
  yb = other.yb;
}


//------------------------------------------------------------------------------
// деструктор
// ---
MbEllipse::~MbEllipse()
{
}


//------------------------------------------------------------------------------
// оператор присваивания
// ---
MbEllipse &  MbEllipse::operator= ( const MbEllipse & other )
{
if ( this != &other ) {
  center = other.center;
  xa = other.xa;
  yb = other.yb;
}

return *this;
}


//------------------------------------------------------------------------------
// по данному значению параметра вычислить соответствующую точку
// ---
void MbEllipse::CalcPointCurve( double t, MbCartPoint & point ) const
{
  point  = center + xa * cos( t ) + yb * sin( t );
}


//------------------------------------------------------------------------------
// определение типа кривой
// ---
MbCurve::TypeCurve MbEllipse::Type() const
{
  return Ellipse;
}


//------------------------------------------------------------------------------
// вычисление первой производной при заданном значении параметра
// ---
void MbEllipse::FirstDerivative( double t, MbVector & vector ) const
{
  vector = - xa * sin( t ) + yb  * cos( t );
}


//------------------------------------------------------------------------------
// вычисление второй производной при заданном значении параметра
// ---
void MbEllipse::SecondDerivative( double t, MbVector & vector ) const
{
  vector = - xa * cos( t ) - yb * sin( t );
}


//------------------------------------------------------------------------------
// получение контрольных точек кривой
// ---
void MbEllipse::GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & vectors ) const
{
  controlPoints.push_back( center );
  vectors.push_back( xa );
  vectors.push_back( yb );
}


//------------------------------------------------------------------------------
// получение минимального значения параметра
// ---
double MbEllipse::GetMinParam() const
{
  return 0.0;
}


//------------------------------------------------------------------------------
// получение максимального значения параметра
// ---
double MbEllipse::GetMaxParam() const
{
  return 2 * PI;
}


//------------------------------------------------------------------------------
// изменение данных кривой
// ---
void MbEllipse::SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors, size_t )
{
  center = points[0];
  xa = vectors[0];
  xa = vectors[1];
}


//------------------------------------------------------------------------------
// запись в поток
// ---
ofstream & MbEllipse::out( ofstream & ofs ) const
{
  ofs << center;
  ofs << xa;
  ofs << yb;
  return ofs;
}


//------------------------------------------------------------------------------
// чтение из потока
// ---
ifstream & MbEllipse::in( ifstream & ifs )
{
  ifs >> center;
  ifs >> xa;
  ifs >> yb;
  return ifs;
}
