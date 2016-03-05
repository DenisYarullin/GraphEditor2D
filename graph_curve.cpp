////////////////////////////////////////////////////////////////////////////////
//
//                 Графическая кривая
//
////////////////////////////////////////////////////////////////////////////////


#include <QPainter>
#include <algorithm>
#include "mb_vector.h"
#include "mb_cart_point.h"
#include "graph_curve.h"
#include "curv_abstract_curve.h"


//------------------------------------------------------------------------------
// конструктор по умолчанию
// ---
GraphCurve::GraphCurve()
  : isSelected( false )
  , color( Qt::white )
{
}


//------------------------------------------------------------------------------
// конструктор по указателю на кривую и ее свойствам
// ---
GraphCurve::GraphCurve( MbCurvePtr _curve, bool selected, const QColor & col )
  : curve( _curve )
  , isSelected( selected )
  , color( col )
{
}


//------------------------------------------------------------------------------
// конструктор копирования
// ---
GraphCurve::GraphCurve( const GraphCurve & other )
{
  curve = other.curve;
  isSelected = other.isSelected;
  color = other.color;
}


//------------------------------------------------------------------------------
// деструктор
// ---
GraphCurve::~GraphCurve()
{
}


//------------------------------------------------------------------------------
// деструктор
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
// получение smart указателя на кривую
// ---
MbCurvePtr GraphCurve::GetCurve() const
{
  return curve;
}


//------------------------------------------------------------------------------
// получение указателя на кривую
// ---
MbCurve * GraphCurve::GetCurvePointer() const
{
  return curve.data();
}


//------------------------------------------------------------------------------
// получение признака селектированности кривой
// ---
bool GraphCurve::IsSelected() const
{
  return isSelected;
}


//------------------------------------------------------------------------------
// получение цвета кривой
// ---
const QColor & GraphCurve::GetColor() const
{
  return color;
}


//------------------------------------------------------------------------------
// установка признака селектированности кривой
// ---
void GraphCurve::SetCurveSelected( bool selected )
{
  isSelected = selected;
}


//------------------------------------------------------------------------------
// установка указателя на кривую
// ---
void GraphCurve::SetCurve( MbCurvePtr _curve )
{
  curve = _curve;
}


//------------------------------------------------------------------------------
// установка цвета кривой
// ---
void GraphCurve::SetColor( QColor & col )
{
  color = col;
}


//------------------------------------------------------------------------------
// функция рисования кривой
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
// функция записи графической кривой
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
// функция чтения графической кривой
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

