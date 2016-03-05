    ////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Точка. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __MB_CART_POINT_H_
#define __MB_CART_POINT_H_

#include <iostream>
#include <fstream>
#include <cmath>


using std :: ofstream;
using std :: ifstream;
class MbVector;


//------------------------------------------------------------------------------
/** \brief \ru Класс точки. \~
  \details \ru Класс точки описывается двумя компонентами: координатой x и координатой y. \n
*/
//------------------------------------------------------------------------------


class MbCartPoint
{

public:

  double x; ///< \ru Координата x.
  double y; ///< \ru Координата y.

  /// \ru Конструктор по умолчанию.
  MbCartPoint();
  /// \ru Конструктор копирования.
  MbCartPoint( const MbCartPoint & );
  /// \ru Конструктор по координатам.
  MbCartPoint( double, double );
  /// \ru Конструктор по вектору.
  MbCartPoint( const MbVector & other );
  /// \ru Деструктор по умолчанию.
  ~MbCartPoint();

  /// \ru Найти расстояние от точки до точки.
  double GetLength( const MbCartPoint & ) const;
  /// \ru Сдвинуть на заданные приращения.
  void Move( double, double );
  /// \ru Инициализация точки другой точкой.
  void InitPoint( const MbCartPoint & );
  /// \ru Инициализация точки координатами.
  void InitPoint( double, double );
  /// \ru Получить x координату.
  double GetXCoord() const;
  /// \ru Получить y координату.
  double GetYCoord() const;
  /// \ru Установить x координату.
  void SetXCoord( double );
  /// \ru Установить y координату.
  void SetYCoord( double );

  /// \ru Операция присваивания по умолчанию.
  MbCartPoint & operator= ( const MbCartPoint &);
  /// \ Присваивание компонент вектора точке.
  void operator= ( const MbVector & );

  /// \ru Сумма двух точек.
  MbVector operator+ ( const MbCartPoint & );
  /// \ru Разность двух точек.
  MbVector operator- ( const MbCartPoint & );
  /// \ru Сумма точки и вектора.
  MbCartPoint operator+ ( const  MbVector & );
  /// \ru Разность точки и вектора.
  MbCartPoint operator- ( const MbVector & );
  /// \ru Унарный оператор минус.
  MbCartPoint operator- ();

  /// \ru Умножение точки на число.
  MbCartPoint operator* ( double ) const;
  /// \ru Деление точки на число.
  MbCartPoint operator/ ( double ) const;

  /// \ru Сумма двух точек.
  void operator+= ( const MbCartPoint & );
  /// \ru Разность двух точек.
  void operator-= ( const MbCartPoint & );
  /// \ru Умножение точки на число.
  void operator*= ( double number );
  /// \ru Деление точки на число.
  void operator/= ( double number );

  /// \ru Проверка на неравенство.
   bool operator!= ( const MbCartPoint & ) const;
  /// \ru Проверка на равенство.
  bool operator== ( const MbCartPoint & ) const;
  /// \ru Проверка на <.
  bool operator< ( const MbCartPoint & ) const;
  /// \ru Проверка на >.
  bool operator> ( const MbCartPoint & ) const;

  /// \ru Вспомогательная функция для вывода в поток.
  friend ofstream & operator<< ( ofstream & out, const MbCartPoint & );
  friend ifstream & operator>> ( ifstream & in, MbCartPoint & );
};


#endif //_MBCARTPOINT_H_
