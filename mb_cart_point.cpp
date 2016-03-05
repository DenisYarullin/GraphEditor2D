////////////////////////////////////////////////////////////////////////////////
//
//                                 Точка
//
////////////////////////////////////////////////////////////////////////////////

#include "constraint.h"
#include "mb_cart_point.h"
#include "mb_vector.h"


//------------------------------------------------------------------------------
// конструктор по умолчанию
// ---
MbCartPoint::MbCartPoint() 
  : x( 0.0 )
  , y( 0.0 )
{
}


//------------------------------------------------------------------------------
// конструктор по двум координатам
// ---
MbCartPoint::MbCartPoint( double xCoord, double yCoord ) 
  : x( xCoord )
  , y( yCoord )
{
}


//------------------------------------------------------------------------------
// конструктор по двум координатам
// ---
MbCartPoint::MbCartPoint(const MbVector & other)
  : x( other.ax )
  , y( other.ay )
{
}


//------------------------------------------------------------------------------
// конструктор копирования
// ---
MbCartPoint::MbCartPoint( const MbCartPoint & other )
{
  x = other.x;
  y = other.y;
}


//------------------------------------------------------------------------------
// деструктор
// ---
MbCartPoint::~MbCartPoint()
{
}


//------------------------------------------------------------------------------
// рассчитать расстояние между точками
// ---
double MbCartPoint::GetLength( const MbCartPoint & other ) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt( dx * dx + dy * dy );
}


//------------------------------------------------------------------------------
// переместить точку
// ---
void MbCartPoint::Move( double dx, double dy )
{
	x += dx;
	y += dy;
}


//------------------------------------------------------------------------------
// инициализировать точку другой точкой
// ---
void MbCartPoint::InitPoint( const MbCartPoint & other )
{
	x = other.x;
	y = other.y;
}


//------------------------------------------------------------------------------
// инициализировать точку координатами
// ---
void MbCartPoint::InitPoint( double xCoord, double yCoord )
{
  x = xCoord;
  y = yCoord;
}


//------------------------------------------------------------------------------
// получить компоненту x точки
// ---
double MbCartPoint::GetXCoord() const
{
  return x;
}


//------------------------------------------------------------------------------
// получить компоненту y точки
// ---
double MbCartPoint::GetYCoord() const
{
  return y;
}


//------------------------------------------------------------------------------
// установить компоненту x точки
// ---
void MbCartPoint::SetXCoord( double xCoord )
{
  x = xCoord;
}


//------------------------------------------------------------------------------
// установить компоненту y точки
// ---
void MbCartPoint::SetYCoord( double yCoord )
{
  y = yCoord; 
}


//------------------------------------------------------------------------------
// оператор присваивания точки
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
// присваивание компонент вектора точке
// ---
void MbCartPoint::operator= ( const MbVector & other)
{
  x = other.GetAx();
  y = other.GetAy();
}


//------------------------------------------------------------------------------
// сложение двух точек
// ---
MbVector MbCartPoint::operator+ (const MbCartPoint & other )
{
  return MbVector( x + other.x, y + other.y );
}


//------------------------------------------------------------------------------
// разность двух точек
// ---
MbVector MbCartPoint::operator- ( const MbCartPoint & other )
{
  return MbVector( x - other.x, y - other.y );
}

//------------------------------------------------------------------------------
// сумма точки и вектора
// ---
MbCartPoint MbCartPoint::operator+ ( const MbVector & other)
{
  return MbCartPoint( x + other.ax, y + other.ay );
}


//------------------------------------------------------------------------------
// разность точки и вектора
// ---
MbCartPoint MbCartPoint::operator- ( const MbVector & other )
{
  return MbCartPoint(x - other.GetAx(), y - other.GetAy());
}


//------------------------------------------------------------------------------
// унарный оператор минуса
// ---
MbCartPoint MbCartPoint::operator- ()
{
  return MbCartPoint(-x, -y);
}


//------------------------------------------------------------------------------
// оператор умножения
// ---
MbCartPoint MbCartPoint::operator* ( double number ) const
{
  return MbCartPoint( x * number, y * number );
}


//------------------------------------------------------------------------------
// оператор деления
// ---
MbCartPoint MbCartPoint::operator/ ( double number ) const
{
  return MbCartPoint( x / number, y / number );
}


//------------------------------------------------------------------------------
// оператор сложения
// ---
void MbCartPoint::operator+= ( const MbCartPoint & other )
{
  x += other.x;
  y += other.y;
}


//------------------------------------------------------------------------------
// оператор разности двух точек
// ---
void MbCartPoint :: operator-= ( const MbCartPoint & other )
{
  x -= other.x;
  y -= other.y;
}


//------------------------------------------------------------------------------
// умножение двух точки на число
// ---
void MbCartPoint::operator*= ( double number )
{
  x *= number;
  y *= number;
}


//------------------------------------------------------------------------------
// деление точки на число
// ---
void MbCartPoint::operator/= ( double number )
{
  x /= number;
  y /= number;
}


//------------------------------------------------------------------------------
// оператор равенства
// ---
bool MbCartPoint::operator== ( const MbCartPoint & other ) const
{
  return ( (fabs(x - other.x) < EPSILON) && (fabs(y - other.y) < EPSILON) );
}


//------------------------------------------------------------------------------
// оператор неравенства
// ---
bool MbCartPoint::operator!= ( const MbCartPoint & other ) const
{
  return ( (fabs(x - other.x) > EPSILON) || (fabs(y - other.y) > EPSILON) );
}


//------------------------------------------------------------------------------
// оператор "меньше"
// ---
bool MbCartPoint::operator< ( const MbCartPoint & other ) const
{
	return ( x < other.x ) && ( y < other.y );
}
	

//------------------------------------------------------------------------------
// оператор "больше"
// ---
bool MbCartPoint::operator> ( const MbCartPoint & other ) const
{
	return (x > other.x) && (y > other.y ); 
}


//------------------------------------------------------------------------------
// запись в поток в бинарном виде, как POD типы
// ---
ofstream & operator<< ( ofstream & out, const MbCartPoint & point)
{
  out.write( (char *) & point.x, sizeof(double) );
  out.write( (char *) & point.y, sizeof(double) );
  return out;
}


//------------------------------------------------------------------------------
// чтение из потока в бинарном виде, как POD типы
// ---
ifstream & operator>> ( ifstream & in, MbCartPoint & point )
{
  in.read( (char *) & point.x, sizeof(double) );
  in.read( (char *) & point.y, sizeof(double) );
  return in;
}
