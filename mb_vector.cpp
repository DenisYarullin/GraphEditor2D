////////////////////////////////////////////////////////////////////////////////
//
//                               Вектор
//
////////////////////////////////////////////////////////////////////////////////


#include "mb_vector.h"
#include "constraint.h"


//------------------------------------------------------------------------------
// конструктор по умочанию
// ---
MbVector::MbVector() 
  : ax( 0.0 ),
    ay( 0.0 )
{
}


//------------------------------------------------------------------------------
// конструктор по двум координатам
// ---
MbVector::MbVector( double xx, double yy ) 
  : ax( xx )
  , ay( yy )
{
}


//------------------------------------------------------------------------------
// конструктор копирования
// ---
MbVector::MbVector( const MbVector & other )
{
  ax = other.ax;
  ay = other.ay;
}
 

//------------------------------------------------------------------------------
// деструктор
// ---
MbVector::~MbVector()
{
}

//------------------------------------------------------------------------------
// оператор присваивания
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
// получить компоненту x вектора
// ---
double MbVector::GetAx() const
{
  return ax;
}


//------------------------------------------------------------------------------
// получить компоненту y вектора
// ---
double MbVector::GetAy() const
{
  return ay;
}


//------------------------------------------------------------------------------
// установить компоненту x вектора
// ---
void MbVector::SetAx( double axx )
{
  ax = axx;
}

//------------------------------------------------------------------------------
// установить компоненту y вектора
// ---
void MbVector::SetAy( double ayy )
{
  ay = ayy;
}

//------------------------------------------------------------------------------
// инициализация вектора покоординатно
// ---
void MbVector::Initialization( double xx, double yy )
{
  ax = xx;
  ay = yy;
}


//------------------------------------------------------------------------------
// инициализация вектора другим вектором
// ---
void MbVector::Initialization( const MbVector & other )
{
  ax = other.ax;
  ay = other.ay;
}


//------------------------------------------------------------------------------
// нахождение длины вектора
// ---
double MbVector::LengthOfVector() const
{
  return  sqrt( ax * ax + ay * ay );
}


//------------------------------------------------------------------------------
// нормализация вектора
// ---
 MbVector MbVector::Normalization()
 {
   double length = LengthOfVector();
   ax /=  length;
   ay /=  length;
   return * this;
 }


//------------------------------------------------------------------------------
// оператор равенства
// ---
bool MbVector::operator== ( const MbVector & other ) const
{
  return ( (fabs(ax - other.ax) < EPSILON) && (fabs(ay - other.ay) < EPSILON) );
}


//------------------------------------------------------------------------------
// оператор неравенства
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
// оператор сложения двух векторов
// ---
MbVector MbVector::operator+ ( const MbVector & other ) const
{
  return MbVector( ax + other.ax, ay + other.ay );
}


//------------------------------------------------------------------------------
// оператор разности двух векторов
// ---
MbVector MbVector::operator- ( const MbVector & other ) const
{
  return MbVector( ax - other.ax, ay - other.ay );
}


//------------------------------------------------------------------------------
// скалярное произведение векторов
// ---
double MbVector::operator* ( const MbVector & other ) const
{
  return ax * other.ax + ay * other.ay;
}


//------------------------------------------------------------------------------
// векторное произведение двухмерных векторов
// ---
 double MbVector::VectorProduct( const MbVector & other ) const
 {
   return  ax * other.ay - other.ax * ay;
 }


//------------------------------------------------------------------------------
// умножение вектора на число
// ---
 MbVector MbVector::operator* ( double number ) const
 {
   return MbVector( ax * number, ay * number );
 }


 //------------------------------------------------------------------------------
 // деление вектора на число
 // ---
 MbVector MbVector::operator/ ( double number ) const
 {
   return MbVector( ax / number, ay / number);
 }



//------------------------------------------------------------------------------
// сложение вектора с вектором
// ---
void MbVector::operator+= ( const MbVector & other )
{
   ax += other.ax;
   ay += other.ay;
}


//------------------------------------------------------------------------------
// разность вектора с вектором
// ---
void MbVector::operator-= ( const MbVector & other )
{
   ax -= other.ax;
   ay -= other.ay;
}


 //------------------------------------------------------------------------------
 // умножение двух векторов
 // ---
 void MbVector::operator*= ( double number )
 {
   ax *= number;
   ay *= number;
 }


 //------------------------------------------------------------------------------
 // деление вектора на вектор
 // ---
 void MbVector::operator/= ( double number )
 {
   ax /= number;
   ay /= number;
 }


 //------------------------------------------------------------------------------
 // запись в поток в бинарном виде, как POD типы
 // ---
 ofstream & operator<< ( ofstream & out, const MbVector & vector)
 {
   out.write( (char *) & vector.ax, sizeof(double) );
   out.write( (char *) & vector.ay, sizeof(double) );
   return out;
 }


 //------------------------------------------------------------------------------
 // чтение из потока в бинарном виде, как POD типы
 // ---
 ifstream & operator>> ( ifstream & in, MbVector & vector )
 {
   in.read( (char *) & vector.ax, sizeof(double) );
   in.read( (char *) & vector.ay, sizeof(double) );
   return in;
 }
