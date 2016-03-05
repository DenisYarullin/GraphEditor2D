////////////////////////////////////////////////////////////////////////////////
//
//                  Виджет главного окна
//
////////////////////////////////////////////////////////////////////////////////


#include <QtWidgets>
#include "mainwindow.h"
#include "graph_widget.h"


MainWindow::MainWindow(QWidget * parent)
  : QMainWindow( parent )
{
  QTextCodec * codec = QTextCodec::codecForName( "windows-1251" );
  QTextCodec::setCodecForLocale( codec );

  graphWidget = new GraphWidget( qApp->desktop()->height() + 1000, qApp->desktop()->width() + 1000, this );

  setMouseTracking( true );

  CreateActions();
  CreateMenus();

  QScrollArea * areaScroll = new QScrollArea;
  areaScroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
  areaScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
  areaScroll->setWidget( graphWidget );

  CreateToolbars();

  QHBoxLayout *centralLayout = new QHBoxLayout;
  centralLayout->addWidget( areaScroll );

  QWidget *mainWidget = new QWidget;
  mainWidget->setLayout( centralLayout );

  setCentralWidget( mainWidget );
  setWindowTitle( tr("Graphic editor 2D") );
}


/////////////////////////////////СЛОТЫ//////////////////////////////////////////

void MainWindow::GetMode()
{
  if( nurbsButton->isChecked() ) {
      leDegreeBSpline->setEnabled( true );
  }
  else {
      leDegreeBSpline->setEnabled( false );
  }
}


//------------------------------------------------------------------------------
// установка режима работы с кривыми по идентификатору
// ---
void MainWindow::ActionsGroupClicked( int )
{
  graphWidget->SetMode( GraphWidget::Mode(ActionsTypeGroup->checkedId()) );
}


//------------------------------------------------------------------------------
// нарисовать точку
// ---
void MainWindow::DrawPoint()
{
}


//------------------------------------------------------------------------------
// нарисовать отрезок
// ---
void MainWindow::DrawSegment()
{
}


//------------------------------------------------------------------------------
// нарисовать эллипс
// ---
void MainWindow::DrawEllipse()
{
}


//------------------------------------------------------------------------------
// нарисовать Nurbs
// ---
void MainWindow::DrawNurbs()
{
}


//------------------------------------------------------------------------------
// найти пересечения
// ---
void MainWindow::FindIntersection()
{
  graphWidget->CalcIntersects();
}


//------------------------------------------------------------------------------
// очистить все
// ---
void MainWindow::CleanAll()
{
  graphWidget->ClearAll();
}


//------------------------------------------------------------------------------
// удалить выбранные
// ---
void MainWindow::DeleteSelect()
{
  graphWidget->DeleteSelectCurve();
}


//------------------------------------------------------------------------------
// о программе
// ---
void MainWindow::About()
{
  QMessageBox::about(this, tr("About"),tr(""));
}


//------------------------------------------------------------------------------
// подсказка
// ---
void MainWindow::ShowHelp()
{
  QMessageBox::information( this, tr("Information"), tr("") );
}


/////////////////////////////////Действия//////////////////////////////////////////


//------------------------------------------------------------------------------
// создание действий
// ---
void MainWindow::CreateActions()
{
  ExitAction = new QAction( tr("Exit" ), this);
  ExitAction->setShortcut( QKeySequence::Quit );
  connect( ExitAction, SIGNAL(triggered()), this, SLOT(close()) );

  AboutAction = new QAction( tr("About"), this );
  AboutAction->setShortcut( tr("Ctrl+B") );
  AboutAction->setIcon( QIcon(":/images/about.png") );
  connect( AboutAction, SIGNAL(triggered()), this, SLOT(About()) );

  HelpAction = new QAction( tr("Information"), this );
  connect( HelpAction, SIGNAL(triggered()), this, SLOT(ShowHelp()) );
  HelpAction->setIcon( QIcon(":/images/help.png") );

  SaveAction = new QAction( tr("Save"), this );
  SaveAction->setShortcut( QKeySequence::Save );
  SaveAction->setIcon( QIcon(":/images/save.jpg") );
  SaveAction->setToolTip( tr("") );
  connect( SaveAction, SIGNAL(triggered()), graphWidget, SLOT(Save()) );

  LoadAction = new QAction( tr("Load"), this );
  LoadAction->setIcon( QIcon(":/images/open.jpg") );
  LoadAction->setShortcut( QKeySequence::Open );
  LoadAction->setToolTip( tr("") );
  connect( LoadAction, SIGNAL(triggered()), graphWidget, SLOT(Load()) );

  DrawPointAction = new QAction( tr("Draw point"), this );
  //DrawPointAction->setIcon( QIcon(":/images/segment.jpg") );
  DrawPointAction->setToolTip( tr("Нарисовать точку в выбранном месте") );
  connect( DrawPointAction, SIGNAL(triggered()), this, SLOT(DrawPoint()) );

  DrawSegmentAction = new QAction( tr("Draw segment"), this );
  DrawSegmentAction->setIcon( QIcon(":/images/segment.jpg") );
  DrawSegmentAction->setToolTip( tr("Нарисовать отрезок по двум точкам") );
  connect( DrawSegmentAction, SIGNAL(triggered()), this, SLOT(DrawSegment()) );

  DrawEllipseAction = new QAction( tr("Draw Ellipse"), this );
  DrawEllipseAction->setIcon( QIcon(":/images/ellipse.jpg") );
  DrawEllipseAction->setToolTip( tr("") );
  connect( DrawEllipseAction, SIGNAL(triggered()), this, SLOT(DrawEllipse()) );

  DrawNurbsAction = new QAction( tr("Draw nurbs"), this );
  DrawNurbsAction->setIcon( QIcon(":/images/nurbs.jpg") );
  DrawNurbsAction->setToolTip( tr("") );
  connect( DrawNurbsAction, SIGNAL(triggered()), this, SLOT(DrawNurbs()) );

  FindIntersectionAction = new QAction( tr("Find intersections"), this );
  FindIntersectionAction->setIcon( QIcon(":/images/intersect.jpg") );
  FindIntersectionAction->setToolTip( tr("") );
  connect( FindIntersectionAction, SIGNAL(triggered()), this, SLOT(FindIntersection()) );

  DeleteSelectAction = new QAction( tr("Delete select curves"), this );
  DeleteSelectAction->setIcon( QIcon(":/images/delete.jpg") );
  DeleteSelectAction->setToolTip( tr("") );
  connect( DeleteSelectAction, SIGNAL(triggered()), this, SLOT(DeleteSelect()) );

  CleanAllAction = new QAction( tr("Clean all"), this );
  CleanAllAction->setIcon( QIcon(":/images/clean.jpg") );
  CleanAllAction->setToolTip( tr("") );
  connect( CleanAllAction, SIGNAL(triggered()), this, SLOT(CleanAll()) );
}


//------------------------------------------------------------------------------
// создание меню
// ---
void MainWindow::CreateMenus()
{
  FileMenu = menuBar()->addMenu( tr("File") );
  FileMenu->addAction( SaveAction );
  FileMenu->addAction( LoadAction );
  FileMenu->addSeparator();
  FileMenu->addAction( ExitAction );

  CurveMenu = menuBar()->addMenu( tr("Curves") );
  CurveMenu->addAction( DrawPointAction );
  CurveMenu->addAction( DrawSegmentAction );
  CurveMenu->addAction( DrawEllipseAction );
  CurveMenu->addAction( DrawNurbsAction );

  SolutionMenu = menuBar()->addMenu( tr("Intersections") );
  SolutionMenu->addAction( FindIntersectionAction );

  AboutMenu = menuBar()->addMenu( tr("Additionally") );
  AboutMenu->addAction( DeleteSelectAction );
  AboutMenu->addAction( CleanAllAction );
  AboutMenu->addSeparator();
  AboutMenu->addAction( HelpAction );
  AboutMenu->addAction( AboutAction );
}


//------------------------------------------------------------------------------
// создание тулбара
// ---
void MainWindow::CreateToolbars()
{
  QToolButton * createButton = new QToolButton;
  createButton->setCheckable( true );
  createButton->setIcon( QIcon(":/images/vertex.jpg") );
  createButton->setToolTip( tr("Draw point") );

  QToolButton * selectButton = new QToolButton;
  selectButton->setCheckable( true );
  selectButton->setIcon( QIcon(":/images/pointer") );
  selectButton->setToolTip( tr("Select curve") );

  QToolButton * selectAllButton = new QToolButton;
  selectAllButton->setIcon( QIcon(":/images/selectall") );
  selectAllButton->setToolTip( tr("Select all curves") );
  connect( selectAllButton, SIGNAL(clicked()), graphWidget, SLOT(SelectAll()) );

  QToolButton * segmentButton = new QToolButton;
  segmentButton->setCheckable( true );
  segmentButton->setIcon( QIcon(":/images/segment.jpg") );
  segmentButton->setToolTip( tr("Draw segment") );

  QToolButton * ellipseButton = new QToolButton;
  ellipseButton->setCheckable( true );
  ellipseButton->setIcon( QIcon(":/images/ellipse") );
  ellipseButton->setToolTip( tr("Draw ellipse") );

  nurbsButton = new QToolButton;
  nurbsButton->setCheckable( true );
  nurbsButton->setIcon( QIcon(":/images/nurbs") );
  nurbsButton->setToolTip( tr("Draw nurbs") );
  connect( nurbsButton, SIGNAL(toggled(bool)), this, SLOT(GetMode()) );

  QToolButton * intersectButton = new QToolButton;
  intersectButton->setIcon( QIcon(":/images/intersect") );
  intersectButton->setToolTip( tr("Find intersections") );
  connect( intersectButton, SIGNAL(clicked()), graphWidget, SLOT(CalcIntersects()) );

  QToolButton * delSelectButton = new QToolButton;
  delSelectButton->setIcon( QIcon(":/images/delete") );
  delSelectButton->setToolTip( tr("Delete select curves") );
  connect( delSelectButton, SIGNAL(clicked()), graphWidget, SLOT(DeleteSelectCurve()) );

  QToolButton * delIntersectsButton = new QToolButton;
  delIntersectsButton->setIcon( QIcon(":/images/delintersects") );
  delIntersectsButton->setToolTip( tr("Delete points of intersects") );
  connect( delIntersectsButton, SIGNAL(clicked()), graphWidget, SLOT(DeleteIntersections()) );

  QToolButton * cleanButton = new QToolButton;
  cleanButton->setIcon( QIcon(":/images/clean") );
  cleanButton->setToolTip( tr("Clean all") );
  connect( cleanButton, SIGNAL(clicked()), graphWidget, SLOT(ClearAll()) );

  lblDegreeBSpline = new QLabel( tr("Degree B-Spline: ") );
  leDegreeBSpline = new QLineEdit( "3" );
  leDegreeBSpline->setEnabled( false );
  lblDegreeBSpline->setBuddy( leDegreeBSpline );
  QValidator * degreeValidator = new QIntValidator( 1, 100, leDegreeBSpline );
  leDegreeBSpline->setValidator( degreeValidator );
  leDegreeBSpline->setFixedSize( 30, 30 );
  connect( leDegreeBSpline, SIGNAL(textChanged(QString)), graphWidget, SLOT(SetDegreeBSpline(QString)) );

  ActionsTypeGroup = new QButtonGroup( this );
  ActionsTypeGroup->addButton( createButton,    int(GraphWidget::addPoint) );
  ActionsTypeGroup->addButton( selectButton,    int(GraphWidget::editCurve) );
  ActionsTypeGroup->addButton( segmentButton,   int(GraphWidget::addLineSegment) );
  ActionsTypeGroup->addButton( ellipseButton,   int(GraphWidget::addEllipse) );
  ActionsTypeGroup->addButton( nurbsButton,     int(GraphWidget::addNurbs) );
  connect( ActionsTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(ActionsGroupClicked(int)) );

  ActionsToolbar = addToolBar( tr("") );
  ActionsToolbar->addWidget( createButton );
  ActionsToolbar->addWidget( selectButton );
  ActionsToolbar->addWidget( selectAllButton );
  ActionsToolbar->addSeparator();
  ActionsToolbar->addWidget( segmentButton );
  ActionsToolbar->addWidget( ellipseButton );
  ActionsToolbar->addWidget( nurbsButton );
  ActionsToolbar->addSeparator();
  ActionsToolbar->addWidget( intersectButton );
  ActionsToolbar->addSeparator();
  ActionsToolbar->addWidget( delSelectButton );
  ActionsToolbar->addWidget( delIntersectsButton );
  ActionsToolbar->addWidget( cleanButton );
  ActionsToolbar->addSeparator();
  ActionsToolbar->addWidget( lblDegreeBSpline );
  ActionsToolbar->addWidget( leDegreeBSpline );
  ActionsToolbar->addSeparator();
}
