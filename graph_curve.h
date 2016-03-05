////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Графическая кривая. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __GRAPH_CURVE_H_
#define __GRAPH_CURVE_H_


#include <vector>
#include <QColor>
#include <QSharedPointer>
#include <fstream>


using std::ofstream;
using std::ifstream;
using std::vector;


class QPixmap;
class MbVector;
class MbCartPoint;
class MbCurve;


typedef QSharedPointer< MbCurve > MbCurvePtr;


//------------------------------------------------------------------------------
/** \brief \ru Класс GraphCurve. \~
  \details \ru Графическая кривая. \n
*/
//------------------------------------------------------------------------------


class GraphCurve
{
private:

  MbCurvePtr curve;             ///< \ru Указатель на кривую.
  bool       isSelected;        ///< \ru Флаг, определяющий селектированность кривой.
  QColor     color;             ///< \ru Цвет рисования кривой.

public:

  /// \ru Конуструктор по умолчанию.
  GraphCurve();
  /// \ru Конструктор по кривой и ее свойствам.
  GraphCurve( MbCurvePtr, bool, const QColor & );
  /// \ru Деструктор.
  ~GraphCurve();
  /// \ru Конструктор копирования.
  GraphCurve( const GraphCurve & );

  /// \ru Оператор присваивания.
  GraphCurve & operator= ( const GraphCurve & );

  /// \ru Получение smart указателя на кривую.
  MbCurvePtr GetCurve() const;
  /// \ru Получение указателя на кривую.
  MbCurve * GetCurvePointer() const;

  /// \ru Получение признака селектированности кривой.
  bool IsSelected() const;
  /// \ru Получение цвета кривой.
  const QColor & GetColor() const;

  /// \ru Установить указатель на кривую.
  void SetCurve( MbCurvePtr );
  /// \ru Установить признак селектированности.
  void SetCurveSelected( bool );
  /// \ru Установить цвет кривой.
  void SetColor( QColor & );

  /// \ru Рисование кривой.
  void PaintCurve( QPixmap *, const QColor & , const QColor &, size_t & problemPaint );

  /// \ru Оператор вывода в поток.
  friend ofstream & operator<< ( ofstream & out, const GraphCurve & );
  /// \ru Оператор ввода в поток.
  friend ifstream & operator>> ( ifstream & in, GraphCurve & );
};


#endif // GRAPH_CURVE_H
