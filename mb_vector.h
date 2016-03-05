////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Вектор. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_VECTOR_H_
#define __MB_VECTOR_H_


#include <cmath>
#include <iostream>
#include <fstream>


using std :: ofstream;
using std :: ifstream;


//------------------------------------------------------------------------------
/** \brief \ru Класс вектора. \~
  \details \ru Класс вектора описывается двумя компонентами в базисном пространстве: координатой x и координатой y. \n
*/
//------------------------------------------------------------------------------


class MbVector
{

public:

  double ax;  /// \ru Компонента вектора x.
  double ay;  /// \ru Компонента вектора y.

  /// \ru Конструктор по умолчанию.
  MbVector ();
  /// \ru Конструктор по координатам.
  MbVector( double xx, double yy );
  /// \ru Конструктор копирования.
  MbVector( const MbVector & );
  /// \ru Деструктор.
  ~MbVector();

  /// \ru Инициализация на заданных координатах.
  void 	Initialization( double xx, double yy );
  /// \ru Инициализация заданным вектором.
  void 	Initialization( const MbVector & );
  /// \ru Нахождение длины вектора.
  double LengthOfVector() const;
  /// \ru Получить первую компоненту вектора.
  double GetAx () const;
  /// \ru Получить вторую компоненту вектора.
  double GetAy () const;
  /// \ru Установить первую компоненту вектора.
  void SetAx( double );
  /// \ru Установить вторую компоненту вектора.
  void SetAy( double );
  /// \ru Нормализация вектора.
  MbVector Normalization();


  /// \ru Оператор присваивания.
  MbVector & operator= ( const MbVector & );
  /// \ru Проверка равенства.
  bool 	operator== ( const MbVector & ) const;
  /// \ru Проверка неравенства.
  bool 	operator!= ( const MbVector & ) const;


  MbVector operator- () const;
  /// \ru Сумма двух векторов.
  MbVector 	operator+ ( const MbVector & ) const;
  /// \ru Разность двух векторов.
  MbVector 	operator- ( const MbVector & ) const;
  /// \ru Умножение вектора на число.
  MbVector 	operator* ( double number ) const;
  /// \ru Деление вектора на число.
  MbVector 	operator/ ( double number ) const;

  /// \ru Сумма двух векторов.
  void 	operator+= ( const MbVector & );
  /// \ru Разность двух векторов.
  void 	operator-= ( const MbVector & );
  /// \ru Умножение вектора на число.
  void 	operator*= ( double );
  /// \ru Деление вектора на число.
  void 	operator/= ( double );
  /// \ru Скалярное произведение двух векторов.
  double operator* ( const MbVector & ) const;
  /// \ru Векторное произведение для двухмерных векторов.
  double VectorProduct( const MbVector & ) const;

  /// \ru Вспомогательная функция для вывода в поток.
  friend ofstream & operator<< ( ofstream & out, const MbVector & );
  friend ifstream & operator>> ( ifstream & in, MbVector & );
};


#endif //__MB_VECTOR_H_
