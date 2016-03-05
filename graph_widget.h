////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru ������ ��� ���������. \~

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
/** \brief \ru ����� GraphWidget. \~
  \details \ru GraphWidget �������� �������� ������ QWidget. \n
*/
//------------------------------------------------------------------------------


class GraphWidget : public QWidget
{

  Q_OBJECT ///< \ru ����������� ������������� �������������� � ���������-�������� ���������.

private:

  int width;                                ///< \ru ������ �������.
  int height;                               ///< \ru ������ �������.

  size_t      degree;                         ///< \ru ������� nurbs.
  QPixmap *   buf;                            ///< \ru ����� ��� ���������.
  MbCurvePtr  curve;                          ///< \ru ��������� �� ����������� �� ������ ������.

  vector< MbCartPoint > vecPointsCurve;       ///< \ru ������ ����� ��� ���������� ������.
  vector< MbVector >    vectors;              ///< \ru ������ �������� ��� ���������� �������.
  vector< GraphCurve >  curves;         ///< \ru ������ ������.
  vector< MbCartPoint > roots;                ///< \ru ����� �����������.

  mutable size_t        problemPaint;         ///< \ru ���� ��� ����������� �������� � ����������.

public:

  /// \ru ����������� �� ������ � ������ ������������ �������.
  GraphWidget( int h, int w, QWidget * parent = 0 );
  /// \ru ����������
  ~GraphWidget();

  ///< \ru ������ ������ � �������.
  enum Mode
  {
     addPoint,         ///< \ru �������� �����.
     addLineSegment,   ///< \ru �������� �������.
     addEllipse,       ///< \ru �������� ������.
     addNurbs,         ///< \ru �������� nurbs.
     editCurve         ///< \ru ������������� ������.
  };

  Mode curveMode;      ///< \ru ������� ��������� ����� ������ � �������.

  ///< \ru ��������� ������ ������ � �������.
  void SetMode( Mode mode );

public slots:

  ///< \ru ���������.
  void Save();
  ///< \ru ���������.
  void Load();
  ///< \ru ��������� �����������.
  void CalcIntersects();
  ///< \ru �������� ��� ������� �������.
  void ClearAll();
  ///< \ru ������� ��� ������ � ������� �������.
  void SelectAll();
  ///< \ru ������� ���������� ������.
  void DeleteSelectCurve();
  ///< \ru ������� ���������� ������.
  void DeleteIntersections();
  ///< \ru ���������� ������� B-�������.
  void SetDegreeBSpline( const QString & degree );

protected:

  ///< \ru ������� �������� ����.
  //virtual void mouseMoveEvent( QMouseEvent * pe );
  ///< \ru ������� ���������� ������ ����.
  //virtual void mouseReleaseEvent( QMouseEvent * pe);
  ///< \ru ������� ������� ����.
  virtual void mousePressEvent( QMouseEvent * pe );
  ///< \ru ������� ���������.
  virtual void paintEvent( QPaintEvent * pe);

private:

  ///< \ru �������������� ������.
  void SelectedCurve( const MbCartPoint & userClick );
  ///< \ru ������ �������������� ������.
  void CancelSelected();
  ///< \ru ������������ ��� ������.
  void Repaint();
};


#endif // GRAPH_WIDGET_H_
