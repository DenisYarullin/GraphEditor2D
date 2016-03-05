////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru ����������� ������. \~

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
/** \brief \ru ����� GraphCurve. \~
  \details \ru ����������� ������. \n
*/
//------------------------------------------------------------------------------


class GraphCurve
{
private:

  MbCurvePtr curve;             ///< \ru ��������� �� ������.
  bool       isSelected;        ///< \ru ����, ������������ ����������������� ������.
  QColor     color;             ///< \ru ���� ��������� ������.

public:

  /// \ru ������������ �� ���������.
  GraphCurve();
  /// \ru ����������� �� ������ � �� ���������.
  GraphCurve( MbCurvePtr, bool, const QColor & );
  /// \ru ����������.
  ~GraphCurve();
  /// \ru ����������� �����������.
  GraphCurve( const GraphCurve & );

  /// \ru �������� ������������.
  GraphCurve & operator= ( const GraphCurve & );

  /// \ru ��������� smart ��������� �� ������.
  MbCurvePtr GetCurve() const;
  /// \ru ��������� ��������� �� ������.
  MbCurve * GetCurvePointer() const;

  /// \ru ��������� �������� ����������������� ������.
  bool IsSelected() const;
  /// \ru ��������� ����� ������.
  const QColor & GetColor() const;

  /// \ru ���������� ��������� �� ������.
  void SetCurve( MbCurvePtr );
  /// \ru ���������� ������� �����������������.
  void SetCurveSelected( bool );
  /// \ru ���������� ���� ������.
  void SetColor( QColor & );

  /// \ru ��������� ������.
  void PaintCurve( QPixmap *, const QColor & , const QColor &, size_t & problemPaint );

  /// \ru �������� ������ � �����.
  friend ofstream & operator<< ( ofstream & out, const GraphCurve & );
  /// \ru �������� ����� � �����.
  friend ifstream & operator>> ( ifstream & in, GraphCurve & );
};


#endif // GRAPH_CURVE_H
