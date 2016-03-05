////////////////////////////////////////////////////////////////////////////////
//
//                               ������
//
////////////////////////////////////////////////////////////////////////////////


#include "mb_vector.h"
#include "constraint.h"


//------------------------------------------------------------------------------
// ����������� �� ��������
// ---
MbVector::MbVector() 
  : ax( 0.0 ),
    ay( 0.0 )
{
}


//------------------------------------------------------------------------------
// ����������� �� ���� �����������
// ---
MbVector::MbVector( double xx, double yy ) 
  : ax( xx )
  , ay( yy )
{
}


//------------------------------------------------------------------------------
// ����������� �����������
// ---
MbVector::MbVector( const MbVector & other )
{
  ax = other.ax;
  ay = other.ay;
}
 

//------------------------------------------------------------------------------
// ����������
// ---
MbVector::~MbVector()
{
}

//------------------------------------------------------------------------------
// �������� ������������
// ---
MbVector & MbVector::operator= ( const MbVector & other )
{
  if ( this != &other ){
    ax = other.ax;
    ay = other.ay;
  }
  return *this;
}
  

//------------------------------------------------------------------------------
// �������� ���������� x �������
// ---
double MbVector::GetAx() const
{
  return ax;
}


//------------------------------------------------------------------------------
// �������� ���������� y �������
// ---
double MbVector::GetAy() const
{
  return ay;
}


//------------------------------------------------------------------------------
// ���������� ���������� x �������
// ---
void MbVector::SetAx( double axx )
{
  ax = axx;
}

//------------------------------------------------------------------------------
// ���������� ���������� y �������
// ---
void MbVector::SetAy( double ayy )
{
  ay = ayy;
}

//------------------------------------------------------------------------------
// ������������� ������� �������������
// ---
void MbVector::Initialization( double xx, double yy )
{
  ax = xx;
  ay = yy;
}


//------------------------------------------------------------------------------
// ������������� ������� ������ ��������
// ---
void MbVector::Initialization( const MbVector & other )
{
  ax = other.ax;
  ay = other.ay;
}


//------------------------------------------------------------------------------
// ���������� ����� �������
// ---
double MbVector::LengthOfVector() const
{
  return  sqrt( ax * ax + ay * ay );
}


//------------------------------------------------------------------------------
// ������������ �������
// ---
 MbVector MbVector::Normalization()
 {
   double length = LengthOfVector();
   ax /=  length;
   ay /=  length;
   return * this;
 }


//------------------------------------------------------------------------------
// �������� ���������
// ---
bool MbVector::operator== ( const MbVector & other ) const
{
  return ( (fabs(ax - other.ax) < EPSILON) && (fabs(ay - other.ay) < EPSILON) );
}


//------------------------------------------------------------------------------
// �������� �����������
// ---
bool MbVector::operator!= ( const MbVector & other ) const
{
  return ( (fabs(ax - other.ax) > EPSILON) || (fabs(ay - other.ay) > EPSILON) );
}


MbVector MbVector::operator- () const
{
  return MbVector( -ax, -ay );
}


//------------------------------------------------------------------------------
// �������� �������� ���� ��������
// ---
MbVector MbVector::operator+ ( const MbVector & other ) const
{
  return MbVector( ax + other.ax, ay + other.ay );
}


//------------------------------------------------------------------------------
// �������� �������� ���� ��������
// ---
MbVector MbVector::operator- ( const MbVector & other ) const
{
  return MbVector( ax - other.ax, ay - other.ay );
}


//------------------------------------------------------------------------------
// ��������� ������������ ��������
// ---
double MbVector::operator* ( const MbVector & other ) const
{
  return ax * other.ax + ay * other.ay;
}


//------------------------------------------------------------------------------
// ��������� ������������ ���������� ��������
// ---
 double MbVector::VectorProduct( const MbVector & other ) const
 {
   return  ax * other.ay - other.ax * ay;
 }


//------------------------------------------------------------------------------
// ��������� ������� �� �����
// ---
 MbVector MbVector::operator* ( double number ) const
 {
   return MbVector( ax * number, ay * number );
 }


 //------------------------------------------------------------------------------
 // ������� ������� �� �����
 // ---
 MbVector MbVector::operator/ ( double number ) const
 {
   return MbVector( ax / number, ay / number);
 }



//------------------------------------------------------------------------------
// �������� ������� � ��������
// ---
void MbVector::operator+= ( const MbVector & other )
{
   ax += other.ax;
   ay += other.ay;
}


//------------------------------------------------------------------------------
// �������� ������� � ��������
// ---
void MbVector::operator-= ( const MbVector & other )
{
   ax -= other.ax;
   ay -= other.ay;
}


 //------------------------------------------------------------------------------
 // ��������� ���� ��������
 // ---
 void MbVector::operator*= ( double number )
 {
   ax *= number;
   ay *= number;
 }


 //------------------------------------------------------------------------------
 // ������� ������� �� ������
 // ---
 void MbVector::operator/= ( double number )
 {
   ax /= number;
   ay /= number;
 }


 //------------------------------------------------------------------------------
 // ������ � ����� � �������� ����, ��� POD ����
 // ---
 ofstream & operator<< ( ofstream & out, const MbVector & vector)
 {
   out.write( (char *) & vector.ax, sizeof(double) );
   out.write( (char *) & vector.ay, sizeof(double) );
   return out;
 }


 //------------------------------------------------------------------------------
 // ������ �� ������ � �������� ����, ��� POD ����
 // ---
 ifstream & operator>> ( ifstream & in, MbVector & vector )
 {
   in.read( (char *) & vector.ax, sizeof(double) );
   in.read( (char *) & vector.ay, sizeof(double) );
   return in;
 }
