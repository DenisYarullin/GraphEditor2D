////////////////////////////////////////////////////////////////////////////////
//
//                          ������
//
////////////////////////////////////////////////////////////////////////////////


#include "constraint.h"
#include "mb_cart_point.h"
#include "curv_abstract_curve.h"
#include "curv_ellipse.h"


//------------------------------------------------------------------------------
// ����������� �� ���������
// ---
MbEllipse::MbEllipse()
  : MbCurve()
  , center()
  , xa()
  , yb()
{
}


//------------------------------------------------------------------------------
// ����������� �� ����������� �����, ������ ����� � ������� �������
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
// ����������� �� ����������� ����� � ���� ��������
// ---
MbEllipse::MbEllipse( MbCartPoint & centerPoint, MbVector & xaVec, MbVector & xbVec )
  : MbCurve()
  , center( centerPoint )
  , xa( xaVec )
  , yb( xbVec )
{
}


//------------------------------------------------------------------------------
// ����������� �����������
// ---
MbEllipse::MbEllipse( const MbEllipse & other ) : MbCurve()
{
  center = other.center;
  xa = other.xa;
  yb = other.yb;
}


//------------------------------------------------------------------------------
// ����������
// ---
MbEllipse::~MbEllipse()
{
}


//------------------------------------------------------------------------------
// �������� ������������
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
// �� ������� �������� ��������� ��������� ��������������� �����
// ---
void MbEllipse::CalcPointCurve( double t, MbCartPoint & point ) const
{
  point  = center + xa * cos( t ) + yb * sin( t );
}


//------------------------------------------------------------------------------
// ����������� ���� ������
// ---
MbCurve::TypeCurve MbEllipse::Type() const
{
  return Ellipse;
}


//------------------------------------------------------------------------------
// ���������� ������ ����������� ��� �������� �������� ���������
// ---
void MbEllipse::FirstDerivative( double t, MbVector & vector ) const
{
  vector = - xa * sin( t ) + yb  * cos( t );
}


//------------------------------------------------------------------------------
// ���������� ������ ����������� ��� �������� �������� ���������
// ---
void MbEllipse::SecondDerivative( double t, MbVector & vector ) const
{
  vector = - xa * cos( t ) - yb * sin( t );
}


//------------------------------------------------------------------------------
// ��������� ����������� ����� ������
// ---
void MbEllipse::GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & vectors ) const
{
  controlPoints.push_back( center );
  vectors.push_back( xa );
  vectors.push_back( yb );
}


//------------------------------------------------------------------------------
// ��������� ������������ �������� ���������
// ---
double MbEllipse::GetMinParam() const
{
  return 0.0;
}


//------------------------------------------------------------------------------
// ��������� ������������� �������� ���������
// ---
double MbEllipse::GetMaxParam() const
{
  return 2 * PI;
}


//------------------------------------------------------------------------------
// ��������� ������ ������
// ---
void MbEllipse::SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors, size_t )
{
  center = points[0];
  xa = vectors[0];
  xa = vectors[1];
}


//------------------------------------------------------------------------------
// ������ � �����
// ---
ofstream & MbEllipse::out( ofstream & ofs ) const
{
  ofs << center;
  ofs << xa;
  ofs << yb;
  return ofs;
}


//------------------------------------------------------------------------------
// ������ �� ������
// ---
ifstream & MbEllipse::in( ifstream & ifs )
{
  ifs >> center;
  ifs >> xa;
  ifs >> yb;
  return ifs;
}
