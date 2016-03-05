////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru ������ �������� ���� ����������. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_


#include <QMainWindow>


/// \ru ��������������� ������.
class QButtonGroup;
class QToolButton;
class QLineEdit;
class GraphWidget;
class QLabel;


//------------------------------------------------------------------------------
/** \brief \ru ����� MainWindow. \~
  \details \ru MainWindow �������� �������� ������ QMainWindow. \n
*/
//------------------------------------------------------------------------------


class MainWindow : public QMainWindow
{
  Q_OBJECT

private:

  GraphWidget * graphWidget;          ///< \ru ��������� �� ������ ������� ���������.
  QLabel      * lblDegreeBSpline;     ///< \ru  ��������� �� ������ ������� ��� ���������� ���� ����� �������.
  QLineEdit   * leDegreeBSpline;      ///< \ru  ��������� �� ������ ���������� ���� ��� ����� �������.

  QAction * ExitAction;               ///< \ru �������� ������ �� ����������.
  QAction * AboutAction;              ///< \ru �������� � ����������.
  QAction * HelpAction;               ///< \ru �������� ������ �� ����������.

  QAction * LoadAction;               ///< \ru �������� �������� ������.
  QAction * SaveAction;               ///< \ru �������� ���������� ������.

  QAction * DrawPointAction;          ///< \ru �������� ��������� �����.
  QAction * DrawSegmentAction;        ///< \ru �������� ��������� �������.
  QAction * DrawEllipseAction;        ///< \ru �������� ��������� �������.
  QAction * DrawNurbsAction;          ///< \ru �������� ��������� Nurbs.
  QAction * FindIntersectionAction;   ///< \ru �������� ������ �����������.
  QAction * CleanAllAction;           ///< \ru �������� ���.
  QAction * DeleteSelectAction;       ///< \ru ������� ��� ���������� �������.

  QMenu * FileMenu;                   ///< \ru ���� �������� � ���������� ������.
  QMenu * CurveMenu;                  ///< \ru ���� ������ � �������.
  QMenu * SolutionMenu;               ///< \ru ���� ���������� �����������.
  QMenu * AboutMenu;                  ///< \ru ��������������� ����.

  QToolBar     * ActionsToolbar;      ///< \ru ������.
  QButtonGroup * ActionsTypeGroup;    ///< \ru ������ ������ �� �������.
  QToolButton * nurbsButton;

  size_t height;                      ///< \ru ������ �������� ����.
  size_t width;                       ///< \ru ������ �������� ����.

public:

  /// \ru ����������� �� �������� �������� ���� ����������.
  MainWindow( QWidget * parent = 0 );

private slots:

  void GetMode();
  /// \ru ��������� ������ ������ � �������.
  void ActionsGroupClicked( int );
  /// \ru � ���������.
  void About();
  /// \ru ���������.
  void ShowHelp();
  /// \ru ���������� �����.
  void DrawPoint();
  /// \ru ���������� �������.
  void DrawSegment();
  /// \ru ���������� ������.
  void DrawEllipse();
  /// \ru ���������� Nurbs.
  void DrawNurbs();
  /// \ru ����� �����������.
  void FindIntersection();
  /// \ru �������� ���.
  void CleanAll();
  /// \ru ������� ����������.
  void DeleteSelect();

private:

  /// \ru ������� ��������.
  void CreateActions();
  /// \ru ������� ����.
  void CreateMenus();
  /// \ru ������� ������.
  void CreateToolbars();
};


#endif // __MAINWINDOW_H_
