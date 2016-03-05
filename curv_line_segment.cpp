////////////////////////////////////////////////////////////////////////////////
//
//                          �������
//
////////////////////////////////////////////////////////////////////////////////


#include "curv_abstract_curve.h"
#include "mb_cart_point.h"
#include "mb_vector.h"
#include "curv_line_segment.h"


//------------------------------------------------------------------------------
// ����������� �� ���������
// ---
MbLineSegment::MbLineSegment() 
  : MbCurve()
  , p1()
  , p2()
{
}


//------------------------------------------------------------------------------
// ����������� �� ���� ������
// ---
MbLineSegment::MbLineSegment( const MbCartPoint & pOne, const MbCartPoint & pTwo )
  : MbCurve()
  , p1( pOne )
  , p2( pTwo )
{
}


//------------------------------------------------------------------------------
// ����������� �� ����������� ���� �����
// ---
MbLineSegment::MbLineSegment( double x0, double y0, double x1, double y1 )
  : MbCurve()
  , p1( x0, y0 )
  , p2( x1, y1 )
{
}


//------------------------------------------------------------------------------
// ����������� �����������
// ---
MbLineSegment::MbLineSegment( const MbLineSegment & other )
  : MbCurve()
  , p1( other.p1 )
  , p2( other.p2 )
{
}


//------------------------------------------------------------------------------
// ����������� �� ����e � �������
// ---
MbLineSegment :: MbLineSegment( const MbCartPoint & pOne, const MbVector & vec )
  : MbCurve()
  , p1( pOne.x, pOne.y )
  , p2( pOne.x + vec.ax, pOne.y + vec.ay )
{
}


//------------------------------------------------------------------------------
// �������� ������������
// ---
MbLineSegment & MbLineSegment::operator= ( const MbLineSegment & other )
{
  if ( this != &other ) {
    p1 = other.GetPointOne();
    p2 = other.GetPointTwo();
  }

  return *this;
}


//------------------------------------------------------------------------------
// ����������
// ---
MbLineSegment::~MbLineSegment()
{
}


//------------------------------------------------------------------------------
// ���������� ����� �������
// ---
double MbLineSegment::GetLengthSegment() const
{
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  return sqrt( dx * dx + dy * dy );
}


//------------------------------------------------------------------------------
// �������� ��������� ����� �������
// ---
const MbCartPoint & MbLineSegment::GetPointOne() const
{
  return p1;
}


//------------------------------------------------------------------------------
// �������� �������� ����� �������
// ---
const MbCartPoint & MbLineSegment::GetPointTwo() const
{
  return p2;
}


//---------------------------------------------------------------------------
/**
  ��������� ����� �� ������, ��������������� ���������.
  \param t - �������� ������.
  \param point - ����������� �����.
*/
//---
void MbLineSegment::CalcPointCurve( double t, MbCartPoint & point ) const
{
  point = p1 * (1.0 - t)  + p2 * t; 
}


//------------------------------------------------------------------------------
// ����������� ���� ������
// ---
MbCurve::TypeCurve MbLineSegment::Type() const
{
  return Segment;
}


//------------------------------------------------------------------------------
// ���������� ������ �����������
// ---
void MbLineSegment::FirstDerivative( double , MbVector & vector ) const
{
  vector.ax = p2.x - p1.x;
  vector.ay = p2.y - p1.y;
}


//------------------------------------------------------------------------------
// ���������� ������ �����������
// ---
void MbLineSegment::SecondDerivative( double, MbVector & vector ) const
{
  vector.ax = 0.0;
  vector.ay = 0.0;
}


//------------------------------------------------------------------------------
// ���������� �������� ������
// ---
double MbLineSegment::Curvature( double )
{
  return 0.0;
}


//------------------------------------------------------------------------------
// ��������� ������������ �������� ���������.
// ---
double MbLineSegment::GetMinParam() const
{
  return 0.0;
}


//------------------------------------------------------------------------------
// ��������� ������������� �������� ���������
// ---
double MbLineSegment::GetMaxParam() const
{
  return 1.0;
}


//------------------------------------------------------------------------------
// ��������� ������ ������
// ---
void MbLineSegment::SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > &, size_t )
{
  p1 = points[0];
  p2 = points[1];
}


//------------------------------------------------------------------------------
// ��������� ����������� ����� ������
// ---
void MbLineSegment::GetDataCurve( vector<MbCartPoint> & controlPoints, vector< MbVector > & ) const
{
  controlPoints.push_back( p1 );
  controlPoints.push_back( p2 );
}


//------------------------------------------------------------------------------
// ������ � �����
// ---
ofstream & MbLineSegment::out( ofstream & ofs ) const
{
  ofs << p1;
  ofs << p2;
  return ofs;
}


//------------------------------------------------------------------------------
// ������ �� ������
// ---
ifstream & MbLineSegment::in( ifstream & ifs )
{
  ifs >> p1;
  ifs >> p2;
  return ifs;
}
