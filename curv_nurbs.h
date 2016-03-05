////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NURBS. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_NURBS_H_
#define __CURVE_NURBS_H_


#include "mb_vector.h"
#include <vector>


using std :: vector;


class MbVector;
class MbCartPoint;
class MbCurve;


//------------------------------------------------------------------------------
/** \brief \ru Класс NURBS. \~
  \details \ru NURBS (Неоднородный рациональный B-сплайн) является потомком класса MbCurve. \n
*/
//------------------------------------------------------------------------------


class MbNurbs : public MbCurve
{

private:

  vector< MbCartPoint > points;                    ///< \ru Массив контрольных опорных точек.
  size_t                degree;                    ///< \ru Порядок B-сплайна.
  bool periodic;

  mutable vector< double > knot;                   ///< \ru Узловой вектор.
  mutable vector< double > weight;                 ///< \ru Массив с весом контрольных точек.

  mutable double w;                                ///< \ru Знаменатель  правой части равенства.
  mutable double dw;                               ///< \ru Первая производная знаменателя.
  mutable double d2w;                              ///< \ru Вторая производная знаменателя.

  mutable MbVector wr;                             ///< \ru Числитель правой части равенства.
  mutable MbVector dwr;                            ///< \ru Первая производная числителя.
  mutable MbVector d2wr;                           ///< \ru Вторая производная числителя.

public:

  /// \ru Конструктор по умолчанию.
  MbNurbs();
  /// \ru Конструктор по количеству опорных точек и порядку вычисляемого B-сплайна.
  MbNurbs( const vector< MbCartPoint > & _points, size_t _degree, bool _periodic = true );
  /// \ru Конструктор коприрования
  MbNurbs( const MbNurbs & );
  /// \ru Оператор присваивания
  MbNurbs & operator= ( const MbNurbs & );
  /// \ru Деструктор.
  virtual ~MbNurbs();

  /// \ru Вычисление значений координат точки для соответствующего параметра.
  virtual void CalcPointCurve( double, MbCartPoint & point ) const;
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

private:

  /// \ru Заполнение узлового вектора.
  void SetKnotVector() const;
  /// \ru Заполнение массива с весами вершин.
  void SetWeightArray() const;
  /// \ru Вычисление нормированных B-сплайнов для определенного значения параметра.
  void CalcNormBSplineFunc( double t, vector< vector< double> > & ) const;
  /// \ru Вычисление радиус-вектора кривой через нормированные B-сплайны.
  void CalcNurbsFromNormB( double t, MbCartPoint & point ) const;
};


#endif //__CURVE_NURBS_H_
