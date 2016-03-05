////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Эллипс. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_ELLIPSE_H_
#define __CURVE_ELLIPSE__H_


#include "mb_vector.h"
#include <fstream>


class MbVector;
class MbCartPoint;
class MbCurve;


using std::ofstream;
using std::ifstream;


//------------------------------------------------------------------------------
/** \brief \ru Класс эллипса. \~
  \details \ru Эллипс является потомком класса MbCurve. \n
*/
//------------------------------------------------------------------------------


class MbEllipse : public MbCurve
{

private:

  mutable MbCartPoint         center;       ///< \ru Центральная точка.
          MbVector            xa;           ///< \ru Вектор для новых координат по оси X.
          MbVector            yb;           ///< \ru Вектор для новых координат по оси Y.

private:
  /// \ru Конструктор по центральнйо точке и двум векторам.
  MbEllipse( MbCartPoint & centerPoint, MbVector & xaVec, MbVector & xbVec );

public:

  /// \ru Конструктор по умолчанию.
  MbEllipse();
  /// \ru Конструктор по трем точкам.
  MbEllipse( MbCartPoint & centerPoint, MbCartPoint & minPoint, MbCartPoint & maxPoint );

  /// \ru Конструктор копирования.
  MbEllipse( const MbEllipse & );
  /// \ru Виртуальный деструктор.
  virtual ~MbEllipse();

  /// \ru Оператор присваивания.
  MbEllipse & operator= ( const MbEllipse & );

  /// \ru Найти следующую точку эллипса по параметру.
  virtual void CalcPointCurve( double t,  MbCartPoint & point ) const;
  /// \ru Определить тип кривой.
  virtual TypeCurve Type() const;
  /// \ru Вычисление первой производной по параметру.
  virtual void FirstDerivative( double t, MbVector & vector ) const;
  /// \ru Вычисление второй производной по параметру.
  virtual void SecondDerivative( double t, MbVector & vector ) const;
  /// \ru Получить массив опорных точек.
  virtual void GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & vectors ) const;
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


#endif //__CURVE_ELLIPSE_H_
