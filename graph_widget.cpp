#include <algorithm>
#include <functional>
#include "graph_widget.h"
#include "mb_cart_point.h"
#include "curv_abstract_curve.h"
#include "curv_line_segment.h"
#include "curv_ellipse.h"
#include "curv_nurbs.h"
#include "graph_curve.h"
#include "func_support.h"
#include "constraint.h"


//------------------------------------------------------------------------------
// конструктор виджета по длине и ширине области рисования
// ---
GraphWidget::GraphWidget( int h, int w, QWidget * parent )
  : QWidget( parent )
  , width( w )
  , height( h )
{
  resize( w, h );

  problemPaint = 0;
  degree = 3;

  buf = new QPixmap( width, height );
  buf->fill( Qt::white );

  setPalette( QPalette(QColor(128, 128, 128)) );
  setMouseTracking( true );
}


//------------------------------------------------------------------------------
// деструктор
// ---
GraphWidget::~GraphWidget()
{
}


//------------------------------------------------------------------------------
// установка режима работы с кривыми
// ---
void GraphWidget::SetMode( Mode mode )
{
  curveMode = mode;
}


//------------------------------------------------------------------------------
// установка степени B-сплайна( nurbs )
// ---
void GraphWidget::SetDegreeBSpline( const QString & _degree )
{
  degree = static_cast< size_t >( _degree.toInt() );
}


//------------------------------------------------------------------------------
// реализация события нажатия мыши
// ---
void GraphWidget::mousePressEvent( QMouseEvent * pe )
{
  if ( pe->buttons() & Qt::LeftButton ) {

    switch ( curveMode ) {

    case addPoint:
      break;

    case addLineSegment:
      vecPointsCurve.push_back( MbCartPoint( pe->x(), pe->y()) );
      if ( vecPointsCurve.size() >= 2 ) {
        curve = MbCurvePtr( new MbLineSegment( vecPointsCurve[0], vecPointsCurve[1]) );
        GraphCurve graphCurve( curve, false, QColor(Qt::gray) );
        curves.push_back( graphCurve );
        vecPointsCurve.clear();
      }
      break;

    case addEllipse:
      vecPointsCurve.push_back( MbCartPoint( pe->x(), pe->y()) );
      if ( vecPointsCurve.size() >= 3 ) {
        curve = MbCurvePtr( new MbEllipse( vecPointsCurve[0], vecPointsCurve[1], vecPointsCurve[2]) );
        GraphCurve graphCurve( curve, false, QColor(Qt::blue) );
        curves.push_back ( graphCurve );
        vecPointsCurve.clear();
        vectors.clear();
      }
      break;

    case addNurbs:
      vecPointsCurve.push_back( MbCartPoint( pe->x(), pe->y()) );
      if ( vecPointsCurve.size() >= degree ) {
        if( !curve.isNull() && curve->Type() == MbCurve::Nurbs ) {
          curve->SetDataCurve( vecPointsCurve, vectors, degree );
        } else {
          curve = MbCurvePtr( new MbNurbs( vecPointsCurve, degree ) );
        }
      }
      break;
    case editCurve: {
       MbCartPoint pointClick( pe->x(), pe->y() );
       if ( !curves.empty() )
          SelectedCurve( pointClick );

    } break;

    default:
        break;
    }
  }
  else if ( Qt::RightButton ) {
    if ( curveMode == addNurbs && vecPointsCurve.size() >= degree) {
      curves.push_back( GraphCurve(curve, false, QColor(Qt::green)) );
      vecPointsCurve.clear();
      curve.clear();
    }
    else {
      CancelSelected();
    }
  }

  update();
  Repaint();

  QWidget::mousePressEvent( pe );
}


//------------------------------------------------------------------------------
// реализация события рисования
// ---
void GraphWidget::paintEvent( QPaintEvent * pe )
{
  QWidget::paintEvent( pe );

  QPainter painter;
  painter.begin( this );
  painter.drawPixmap( 0, 0, *buf );
  painter.end();
}


//------------------------------------------------------------------------------
// сохранение в файл
// ---
void GraphWidget::Save()
{
  if ( !curves.empty() ) {
    QString fileName = QFileDialog::getSaveFileName( this, tr("Save curves"), ".", tr("Curves (*.gph)") );

    if ( !fileName.isEmpty()) {
      if ( !(fileName.right(4) == ".gph") ) fileName += ".gph";
      ofstream file;
      std::string fileNameString = fileName.toStdString();
      file.open( fileNameString.c_str(), ios::out | ios::binary );
      if ( file.is_open() ) {
        for( iterCurves i = curves.begin(); i != curves.end(); ++i ){
          file << (*i).GetCurve()->Type();
          file << (*i);
        }
        file.close();

      } else {
        QMessageBox::warning( this, tr("Write error"), tr("Imposible to create a file!") );
      }
    }
  } else {
    QMessageBox::warning( this, tr("Error"), tr("The graph is empty!") );
  }
}


//------------------------------------------------------------------------------
// загрузка из файла
// ---
void GraphWidget::Load()
{
  if ( !curves.empty() ) {
    if ( QMessageBox::warning( this, tr("Curves"),
                               tr("Current curves will be removed.\nDo you want to continue?"),
                               QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes ) {
      ClearAll();

    } else {
      return;
    }
  }

  QString fileName = QFileDialog::getOpenFileName( this, tr("Load curves"), ".", tr("Curves (*.gph)") );

  if ( !fileName.isEmpty() ) {
    ifstream file;
    std::string fileNameString = fileName.toStdString();
    file.open( fileNameString.c_str(), ios::in | ios::binary );
    if ( file.is_open() ) {
      MbCurve::TypeCurve modeType;
      int mode = 0;
      while( true ) {

        file >> mode;
        if ( file.eof() ) break;

        modeType = static_cast< MbCurve::TypeCurve >( mode );

        switch ( modeType ) {
        case MbCurve::Segment:
          curve = MbCurvePtr( new MbLineSegment );
          break;
        case MbCurve::Ellipse:
          curve = MbCurvePtr( new MbEllipse );
          break;
        case MbCurve::Nurbs:
          curve = MbCurvePtr( new MbNurbs );
          break;
        default:
          break;
        }

        GraphCurve gCurve( curve, false, QColor(Qt::white) );
        file >> gCurve;
        curves.push_back( gCurve );
      }
      Repaint();
      file.close();

    } else {
        QMessageBox::warning( this, tr("Read error!"), tr("Imposible to open a file!") );
    }
  }
}


//------------------------------------------------------------------------------
// вычисление пересечений
// ---
void GraphWidget::CalcIntersects()
{
  roots.clear();

  if( !curves.empty() ) {
    for( iterCurves i = curves.begin(); i + 1 != curves.end(); ++i ) {
      if ( !(*i).IsSelected() )
          continue;
      for( iterCurves j = i + 1; j != curves.end(); ++j ) {
        if( (*j).IsSelected() )
            ComputeIntersects( (*i).GetCurve(), (*j).GetCurve(), roots );
      }
    }
  }
  Repaint();
  update();
}


//------------------------------------------------------------------------------
// очистка всей рабочей области
// ---
void GraphWidget::ClearAll()
{
  if ( buf ) {
      buf->fill( Qt::white );
  }
  curves.clear();
  vecPointsCurve.clear();
  vectors.clear();
  roots.clear();
  curve.clear();
  update();
}


//------------------------------------------------------------------------------
// селектирование всех кривых в рабочей области
// ---
void GraphWidget::SelectAll()
{
  for ( iterCurves i = curves.begin(); i != curves.end(); ++i) {
    (*i).SetCurveSelected( true );
  }
  Repaint();
}


//------------------------------------------------------------------------------
// удаление выделенных кривых
// ---
void GraphWidget::DeleteSelectCurve()
{
  curves.erase( std::remove_if(curves.begin(), curves.end(), DeleteSelect), curves.end() );
  update();
  Repaint();
}


//------------------------------------------------------------------------------
// удаление точек пересечения кривых
// ---
void GraphWidget::DeleteIntersections()
{
  roots.clear();
  Repaint();
}


//------------------------------------------------------------------------------
// нахождение кривой для селектирования
// ---
void GraphWidget::SelectedCurve( const MbCartPoint & userClick )
{
  vector< pair< GraphCurve, double > > nearestCurve;
  vector< double > param;
  vector< double > distances;
  vector< MbCartPoint > points;
  MbCartPoint point;
  double distance;

  for ( iterCurves i = curves.begin(); i != curves.end(); ++i) {

    double tMin = (*i).GetCurve()->GetMinParam();
    double tMax = (*i).GetCurve()->GetMaxParam();

    (*i).GetCurve()->StepParameter( tMin, tMax, param );
    foreach ( double t, param ) {
        (*i).GetCurve()->CalcPointCurve( t, point );
        points.push_back( point );
    }

    for( vector< MbCartPoint >::iterator j = points.begin(); j + 1 != points.end(); ++j ) {
        distance = DistBetweenPointSegment( *j, *(j + 1), userClick);
        distances.push_back( fabs(distance) );
    }

    double minDistance = * std::min_element( distances.begin(), distances.end() );
    nearestCurve.push_back( make_pair( *i, minDistance) );

    param.clear();
    points.clear();
    distances.clear();
  }

  sort( nearestCurve.begin(), nearestCurve.end(), SortPair );

  if( nearestCurve[0].second >= radius )
    return;

  iterCurves i = find_if( curves.begin(), curves.end(), FindFirst(nearestCurve[0].first.GetCurve()) );
  (*i).SetCurveSelected( true );
}


//------------------------------------------------------------------------------
// перерисовска всех объектов
// ---
void GraphWidget::Repaint()
{

  if ( buf ) {
      buf->fill( Qt::white );
  }

  if ( !curve.isNull() && curve->Type() == MbCurve::Nurbs ) {
      GraphCurve graphCurve( curve, false, QColor(Qt::green) );
      graphCurve.PaintCurve( buf, Qt::black, graphCurve.GetColor(), problemPaint );
  }

  if( !curves.empty() ) {
    for( iterCurves i = curves.begin(); i != curves.end(); ++i ) {
      if ( (*i).IsSelected() ) {
        (*i).PaintCurve( buf, Qt::red, Qt::red, problemPaint );
      } else {
        (*i).PaintCurve( buf, Qt::black, (*i).GetColor(), problemPaint );
      }
      if ( problemPaint ) {
          curves.erase( i );
          i = curves.begin();
      }
    }
    update();
  }

  if( !roots.empty() ) {
    QPainter painter;
    painter.begin( buf );
    painter.setPen( QPen(Qt::magenta, 5) );
    foreach ( MbCartPoint point, roots ) {
      painter.drawPoint( point.x, point.y );
    }
    painter.end();
  }
}

//------------------------------------------------------------------------------
// отмена селектирования
// ---
void GraphWidget::CancelSelected()
{
  for ( iterCurves i = curves.begin(); i != curves.end(); ++i) {
    (*i).SetCurveSelected( false );
  }
}
