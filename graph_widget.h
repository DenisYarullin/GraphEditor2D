////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Виджет для рисования. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __GRAPH_WIDGET_H_
#define __GRAPH_WIDGET_H_

#include <QtWidgets>
#include <QSharedPointer>
#include <vector>


using std::vector;
using std::iterator;
using std::pair;
using std::make_pair;
using std::sort;
using std::find_if;


#include "mb_cart_point.h"
#include "graph_curve.h"


class MbCartPoint;
class GraphCurve;
class MbCurve;


using std::ios;
typedef vector< GraphCurve >::iterator iterCurves;
typedef QSharedPointer< MbCurve > MbCurvePtr;


//------------------------------------------------------------------------------
/** \brief \ru Класс GraphWidget. \~
  \details \ru GraphWidget является потомком класса QWidget. \n
*/
//------------------------------------------------------------------------------


class GraphWidget : public QWidget
{

  Q_OBJECT ///< \ru Возможность использования метаинформации и сигнально-слотовых отношений.

private:

  int width;                                ///< \ru Ширина виджета.
  int height;                               ///< \ru Высота виджета.

  size_t      degree;                         ///< \ru Порядок nurbs.
  QPixmap *   buf;                            ///< \ru Карта для рисования.
  MbCurvePtr  curve;                          ///< \ru Указатель на добавляемую на виджет кривую.

  vector< MbCartPoint > vecPointsCurve;       ///< \ru Вектор точек для построения кривой.
  vector< MbVector >    vectors;              ///< \ru Массив векторов для построения эллипса.
  vector< GraphCurve >  curves;         ///< \ru Вектор кривых.
  vector< MbCartPoint > roots;                ///< \ru Точки пересечения.

  mutable size_t        problemPaint;         ///< \ru Флаг для обозначения проблемы с рисованием.

public:

  /// \ru Конструктор по высоте и ширине создаваемого виджета.
  GraphWidget( int h, int w, QWidget * parent = 0 );
  /// \ru Деструктор
  ~GraphWidget();

  ///< \ru Режимы работы с кривыми.
  enum Mode
  {
     addPoint,         ///< \ru Добавить точку.
     addLineSegment,   ///< \ru Добавить отрезок.
     addEllipse,       ///< \ru Добавить эллипс.
     addNurbs,         ///< \ru Добавить nurbs.
     editCurve         ///< \ru Селектировать кривую.
  };

  Mode curveMode;      ///< \ru Текущий выбранный режим работы с кривыми.

  ///< \ru Установка режима работы с кривыми.
  void SetMode( Mode mode );

public slots:

  ///< \ru Сохранить.
  void Save();
  ///< \ru Загрузить.
  void Load();
  ///< \ru Вычислить пересечения.
  void CalcIntersects();
  ///< \ru Очистить всю рабочую область.
  void ClearAll();
  ///< \ru Выбрать все кривые в рабочей области.
  void SelectAll();
  ///< \ru Удалить выделенные кривые.
  void DeleteSelectCurve();
  ///< \ru Удалить выделенные кривые.
  void DeleteIntersections();
  ///< \ru Установить порядок B-сплайна.
  void SetDegreeBSpline( const QString & degree );

protected:

  ///< \ru Событие движения мыши.
  //virtual void mouseMoveEvent( QMouseEvent * pe );
  ///< \ru Событие отпускания кнопки мыши.
  //virtual void mouseReleaseEvent( QMouseEvent * pe);
  ///< \ru Событие нажатия мыши.
  virtual void mousePressEvent( QMouseEvent * pe );
  ///< \ru Событие рисования.
  virtual void paintEvent( QPaintEvent * pe);

private:

  ///< \ru Селектирование кривой.
  void SelectedCurve( const MbCartPoint & userClick );
  ///< \ru Отмена селектирования кривых.
  void CancelSelected();
  ///< \ru Перерисовать все кривые.
  void Repaint();
};


#endif // GRAPH_WIDGET_H_
