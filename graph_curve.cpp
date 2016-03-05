////////////////////////////////////////////////////////////////////////////////
//
//                 ����������� ������
//
////////////////////////////////////////////////////////////////////////////////


#include <QPainter>
#include <algorithm>
#include "mb_vector.h"
#include "mb_cart_point.h"
#include "graph_curve.h"
#include "curv_abstract_curve.h"


//------------------------------------------------------------------------------
// ����������� �� ���������
// ---
GraphCurve::GraphCurve()
  : isSelected( false )
  , color( Qt::white )
{
}


//------------------------------------------------------------------------------
// ����������� �� ��������� �� ������ � �� ���������
// ---
GraphCurve::GraphCurve( MbCurvePtr _curve, bool selected, const QColor & col )
  : curve( _curve )
  , isSelected( selected )
  , color( col )
{
}


//------------------------------------------------------------------------------
// ����������� �����������
// ---
GraphCurve::GraphCurve( const GraphCurve & other )
{
  curve = other.curve;
  isSelected = other.isSelected;
  color = other.color;
}


//------------------------------------------------------------------------------
// ����������
// ---
GraphCurve::~GraphCurve()
{
}


//------------------------------------------------------------------------------
// ����������
// ---
GraphCurve & GraphCurve::operator= ( const GraphCurve & other )
{
  if ( this != &other ) {
    curve = other.curve;
    isSelected = other.isSelected;
    color = other.color;
  }

  return *this;
}


//------------------------------------------------------------------------------
// ��������� smart ��������� �� ������
// ---
MbCurvePtr GraphCurve::GetCurve() const
{
  return curve;
}


//------------------------------------------------------------------------------
// ��������� ��������� �� ������
// ---
MbCurve * GraphCurve::GetCurvePointer() const
{
  return curve.data();
}


//------------------------------------------------------------------------------
// ��������� �������� ����������������� ������
// ---
bool GraphCurve::IsSelected() const
{
  return isSelected;
}


//------------------------------------------------------------------------------
// ��������� ����� ������
// ---
const QColor & GraphCurve::GetColor() const
{
  return color;
}


//------------------------------------------------------------------------------
// ��������� �������� ����������������� ������
// ---
void GraphCurve::SetCurveSelected( bool selected )
{
  isSelected = selected;
}


//------------------------------------------------------------------------------
// ��������� ��������� �� ������
// ---
void GraphCurve::SetCurve( MbCurvePtr _curve )
{
  curve = _curve;
}


//------------------------------------------------------------------------------
// ��������� ����� ������
// ---
void GraphCurve::SetColor( QColor & col )
{
  color = col;
}


//------------------------------------------------------------------------------
// ������� ��������� ������
// ---
void GraphCurve::PaintCurve(QPixmap * buf, const QColor & col1, const QColor  &col2 , size_t & problemPaint )
{
  QPainter painter;
  QPainterPath path;
  MbCartPoint point;
  vector< MbCartPoint > points;
  vector< MbVector > vectors;
  vector< double > param;

  problemPaint = 0;

  painter.begin( buf );

  double tMin = curve->GetMinParam();
  double tMax = curve->GetMaxParam();

  curve->GetDataCurve( points, vectors );
  curve->StepParameter( tMin, tMax, param );
  curve->CalcPointCurve( param[0], point );

  path.moveTo( point.x, point.y );

  painter.setPen( col2 );
  for( vector< double >::iterator i = param.begin() + 1; i != param.end(); ++i) {
    curve->CalcPointCurve( *i, point );
    if ( point.x < 0.0 || point.y < 0.0 ) {
      problemPaint = 1;
      return;
    }
    path.lineTo( point.x, point.y );
  }

  painter.drawPath( path );

  painter.setPen( QPen(col1, 5) );

  if( !points.empty() ) {
    for( size_t j = 0; j < points.size(); ++j ) {
      painter.drawPoint( points[j].x, points[j].y );
      }
  }

  if( !vectors.empty() ) {
    for( size_t j = 0; j < vectors.size(); ++j ) {
      painter.drawPoint(  points[0].x + vectors[j].ax, points[0].y + vectors[j].ay );
    }
  }
  painter.end();
}


//------------------------------------------------------------------------------
// ������� ������ ����������� ������
// ---
ofstream & operator<< ( ofstream & out, const GraphCurve & gCurve )
{
  out << gCurve.curve.data();
  int r = gCurve.color.red();
  int g = gCurve.color.green();
  int b = gCurve.color.blue();
  out.write( (char *) & r, sizeof(int) );
  out.write( (char *) & g, sizeof(int) );
  out.write( (char *) & b, sizeof(int) );
  return out;
}


//------------------------------------------------------------------------------
// ������� ������ ����������� ������
// ---
ifstream & operator>> ( ifstream & in, GraphCurve & gCurve )
{
  int r = 0, g = 0, b = 0;
  in >> gCurve.curve.data();
  in.read( (char *) & r, sizeof(int) );
  in.read( (char *) & g, sizeof(int) );
  in.read( (char *) & b, sizeof(int) );
  QColor temp( r, g, b );
  gCurve.SetColor( temp );
  return in;
}

