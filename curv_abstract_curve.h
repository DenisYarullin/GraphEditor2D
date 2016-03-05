////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Абстрактный класс для кривых.
         \en Abstract class for the curves. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_ABSTRACT_CURVE_H_
#define __CURVE_ABSTRACT_CURVE_H_


#include <vector>
#include <fstream>


using std::vector;
using std::ofstream;
using std::ifstream;


class MbCartPoint;
class MbVector;


//------------------------------------------------------------------------------
/** \brief \ru Абстрактный класс для кривых.
           \en Abstract class for the curves. \~
  \details \ru  Абстрактный класс для кривых содержит чисто виртуальные функции, переопределяемые в производных классах. \n
*/
//------------------------------------------------------------------------------


class MbCurve
{

private:
    /// \ru Конструктор копирования (не реализовано).
    MbCurve( const MbCurve & );
    /// \ru Оператор присваивания (не реализовано).
    MbCurve & operator= (const MbCurve & );

public:

  enum TypeCurve ///< \ru Типы кривых.
  {
      Segment,  ///< \ru Отрезок.
      Ellipse,  ///< \ru Эллипс.
      Nurbs     ///< \ru Nurbs.
  };

  /// \ru Конструктор по умолчанию.
  MbCurve();
  /// \ru Деструктор.
  virtual ~MbCurve();

  /// \ru Чистая виртуальная функция для нахождения точки по параметру.
  virtual void CalcPointCurve( double t, MbCartPoint & point) const = 0;
  /// \ru Чистая виртуальная функция для определение типа кривой.
  virtual TypeCurve Type() const = 0;
  /// \ru Чистая виртуальная функция для определения первой производной по параметру.
  virtual void FirstDerivative( double t, MbVector & vector ) const = 0;
  /// \ru Чистая виртуальная функция для определения второй производной по параметру.
  virtual void SecondDerivative( double t, MbVector & vector ) const = 0;
  /// \ru Функция для определения кривизны кривой в точке.
  virtual double Curvature( double t ) const;
  /// \ru Функция для сохранения рассчитанных значений параметра в соответствии с кривизной.
  virtual void StepParameter( double minT, double maxT, vector< double > & parameters );
  /// \ru Получить массив опорных точек.
  virtual void GetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors ) const = 0;
  /// \ru Получить минимальное значение параметра.
  virtual double GetMinParam() const = 0;
  /// \ru Получить максимальное значение параметра.
  virtual double GetMaxParam() const = 0;
  /// \ru Изменить данные кривой.
  virtual void SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors, size_t degree ) = 0;
  /// \ru Запись в файл.
  virtual ofstream & out( ofstream & ofs ) const = 0;
  /// \ru Чтение из файла.
  virtual ifstream & in( ifstream & ifs ) = 0;

  /// \ru Оператор вывода в поток.
  friend ofstream & operator<< ( ofstream & out, const MbCurve * );
  /// \ru Оператор ввода в поток.
  friend ifstream & operator>> ( ifstream & in, MbCurve * );
};


#endif //__CURVE_ABSTRACT_CURVE_H_
