////////////////////////////////////////////////////////////////////////////////
//
//                                 �����
//
////////////////////////////////////////////////////////////////////////////////

#include "constraint.h"
#include "mb_cart_point.h"
#include "mb_vector.h"


//------------------------------------------------------------------------------
// ����������� �� ���������
// ---
MbCartPoint::MbCartPoint() 
  : x( 0.0 )
  , y( 0.0 )
{
}


//------------------------------------------------------------------------------
// ����������� �� ���� �����������
// ---
MbCartPoint::MbCartPoint( double xCoord, double yCoord ) 
  : x( xCoord )
  , y( yCoord )
{
}


//------------------------------------------------------------------------------
// ����������� �� ���� �����������
// ---
MbCartPoint::MbCartPoint(const MbVector & other)
  : x( other.ax )
  , y( other.ay )
{
}


//------------------------------------------------------------------------------
// ����������� �����������
// ---
MbCartPoint::MbCartPoint( const MbCartPoint & other )
{
  x = other.x;
  y = other.y;
}


//------------------------------------------------------------------------------
// ����������
// ---
MbCartPoint::~MbCartPoint()
{
}


//------------------------------------------------------------------------------
// ���������� ���������� ����� �������
// ---
double MbCartPoint::GetLength( const MbCartPoint & other ) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt( dx * dx + dy * dy );
}


//------------------------------------------------------------------------------
// ����������� �����
// ---
void MbCartPoint::Move( double dx, double dy )
{
	x += dx;
	y += dy;
}


//------------------------------------------------------------------------------
// ���������������� ����� ������ ������
// ---
void MbCartPoint::InitPoint( const MbCartPoint & other )
{
	x = other.x;
	y = other.y;
}


//------------------------------------------------------------------------------
// ���������������� ����� ������������
// ---
void MbCartPoint::InitPoint( double xCoord, double yCoord )
{
  x = xCoord;
  y = yCoord;
}


//------------------------------------------------------------------------------
// �������� ���������� x �����
// ---
double MbCartPoint::GetXCoord() const
{
  return x;
}


//------------------------------------------------------------------------------
// �������� ���������� y �����
// ---
double MbCartPoint::GetYCoord() const
{
  return y;
}


//------------------------------------------------------------------------------
// ���������� ���������� x �����
// ---
void MbCartPoint::SetXCoord( double xCoord )
{
  x = xCoord;
}


//------------------------------------------------------------------------------
// ���������� ���������� y �����
// ---
void MbCartPoint::SetYCoord( double yCoord )
{
  y = yCoord; 
}


//------------------------------------------------------------------------------
// �������� ������������ �����
// ---
MbCartPoint & MbCartPoint::operator= ( const MbCartPoint & other )
{
	if (this == &other) {
		return *this;
	}
	x = other.x;
	y = other.y;

	return *this;
}


//------------------------------------------------------------------------------
// ������������ ��������� ������� �����
// ---
void MbCartPoint::operator= ( const MbVector & other)
{
  x = other.GetAx();
  y = other.GetAy();
}


//------------------------------------------------------------------------------
// �������� ���� �����
// ---
MbVector MbCartPoint::operator+ (const MbCartPoint & other )
{
  return MbVector( x + other.x, y + other.y );
}


//------------------------------------------------------------------------------
// �������� ���� �����
// ---
MbVector MbCartPoint::operator- ( const MbCartPoint & other )
{
  return MbVector( x - other.x, y - other.y );
}

//------------------------------------------------------------------------------
// ����� ����� � �������
// ---
MbCartPoint MbCartPoint::operator+ ( const MbVector & other)
{
  return MbCartPoint( x + other.ax, y + other.ay );
}


//------------------------------------------------------------------------------
// �������� ����� � �������
// ---
MbCartPoint MbCartPoint::operator- ( const MbVector & other )
{
  return MbCartPoint(x - other.GetAx(), y - other.GetAy());
}


//------------------------------------------------------------------------------
// ������� �������� ������
// ---
MbCartPoint MbCartPoint::operator- ()
{
  return MbCartPoint(-x, -y);
}


//------------------------------------------------------------------------------
// �������� ���������
// ---
MbCartPoint MbCartPoint::operator* ( double number ) const
{
  return MbCartPoint( x * number, y * number );
}


//------------------------------------------------------------------------------
// �������� �������
// ---
MbCartPoint MbCartPoint::operator/ ( double number ) const
{
  return MbCartPoint( x / number, y / number );
}


//------------------------------------------------------------------------------
// �������� ��������
// ---
void MbCartPoint::operator+= ( const MbCartPoint & other )
{
  x += other.x;
  y += other.y;
}


//------------------------------------------------------------------------------
// �������� �������� ���� �����
// ---
void MbCartPoint :: operator-= ( const MbCartPoint & other )
{
  x -= other.x;
  y -= other.y;
}


//------------------------------------------------------------------------------
// ��������� ���� ����� �� �����
// ---
void MbCartPoint::operator*= ( double number )
{
  x *= number;
  y *= number;
}


//------------------------------------------------------------------------------
// ������� ����� �� �����
// ---
void MbCartPoint::operator/= ( double number )
{
  x /= number;
  y /= number;
}


//------------------------------------------------------------------------------
// �������� ���������
// ---
bool MbCartPoint::operator== ( const MbCartPoint & other ) const
{
  return ( (fabs(x - other.x) < EPSILON) && (fabs(y - other.y) < EPSILON) );
}


//------------------------------------------------------------------------------
// �������� �����������
// ---
bool MbCartPoint::operator!= ( const MbCartPoint & other ) const
{
  return ( (fabs(x - other.x) > EPSILON) || (fabs(y - other.y) > EPSILON) );
}


//------------------------------------------------------------------------------
// �������� "������"
// ---
bool MbCartPoint::operator< ( const MbCartPoint & other ) const
{
	return ( x < other.x ) && ( y < other.y );
}
	

//------------------------------------------------------------------------------
// �������� "������"
// ---
bool MbCartPoint::operator> ( const MbCartPoint & other ) const
{
	return (x > other.x) && (y > other.y ); 
}


//------------------------------------------------------------------------------
// ������ � ����� � �������� ����, ��� POD ����
// ---
ofstream & operator<< ( ofstream & out, const MbCartPoint & point)
{
  out.write( (char *) & point.x, sizeof(double) );
  out.write( (char *) & point.y, sizeof(double) );
  return out;
}


//------------------------------------------------------------------------------
// ������ �� ������ � �������� ����, ��� POD ����
// ---
ifstream & operator>> ( ifstream & in, MbCartPoint & point )
{
  in.read( (char *) & point.x, sizeof(double) );
  in.read( (char *) & point.y, sizeof(double) );
  return in;
}
