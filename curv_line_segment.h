////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Отрезок. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_LINE_SEGMENT_H_
#define __CURVE_LINE_SEGMENT_H_


#include <fstream>


class MbCurve;
class MbCartPoint;
class MbVector;


using std::ofstream;
using std::ifstream;


//------------------------------------------------------------------------------
/** \brief \ru Класс отрезка. \~
  \details \ru Отрезок является потомком класса MbCurve. \n
*/
//------------------------------------------------------------------------------


class MbLineSegment : public MbCurve
{

private:

  MbCartPoint p1;                       ///< \ru Первая точка.
  MbCartPoint p2;                       ///< \ru Вторая точка.

public:
  /// \ru Конструктор по умолчанию.
  MbLineSegment();
  /// \ru Конструктор по двум точкам.
  MbLineSegment( const MbCartPoint &, const MbCartPoint & );
  /// \ru Конструктор по двум точкам, выраженным в координатах.
  MbLineSegment( double x0, double y0, double x1, double y1 );
  /// \ru Конструктор по точку и вектору.
  MbLineSegment( const MbCartPoint &, const MbVector & );
  /// \ru Конструктор копирования.
  MbLineSegment( const MbLineSegment & );

  /// \ru Деструктор.
  virtual ~MbLineSegment();

  /// \ru Оператор присваивания.
  MbLineSegment & operator = ( const MbLineSegment & );

  /// \ru Получить длину сегмента.
  double GetLengthSegment() const;
  /// \ru Получить первую точку.
  const MbCartPoint & GetPointOne() const;
  /// \ru Получить вторую точку.
  const MbCartPoint & GetPointTwo() const;

  /// \ru Найти точку отрезка по параметру.
  virtual void CalcPointCurve( double t, MbCartPoint & point ) const;
  /// \ru Определить тип кривой.
  virtual TypeCurve Type() const;
  /// \ru Вычисление первой производной по параметру.
  virtual void FirstDerivative(double, MbVector & vector ) const;
  /// \ru Вычисление второй производной по параметру.
  virtual void SecondDerivative( double , MbVector & vector ) const;
  /// \ru Вычисление кривизны кривой в точке.
  virtual double Curvature( double t );
  /// \ru Получить массив опорных точек.
  virtual void GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & ) const;
  /// \ru Получить минимальное значение параметра.
  virtual double GetMinParam() const;
  /// \ru Получить максимальное значение параметра.
  virtual double GetMaxParam() const;
  /// \ru Изменить данные кривой.
  virtual void SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors, size_t degree );
  /// \ru Запись в файл.
  virtual ofstream & out( ofstream & ofs ) const;
  /// \ru Чтение из файла.
  virtual ifstream & in( ifstream & ifs );  
};


#endif //__CURVE_LINE_SEGMENT_H_
