////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Виджет главного окна приложения. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_


#include <QMainWindow>


/// \ru Преопределенные классы.
class QButtonGroup;
class QToolButton;
class QLineEdit;
class GraphWidget;
class QLabel;


//------------------------------------------------------------------------------
/** \brief \ru Класс MainWindow. \~
  \details \ru MainWindow является потомком класса QMainWindow. \n
*/
//------------------------------------------------------------------------------


class MainWindow : public QMainWindow
{
  Q_OBJECT

private:

  GraphWidget * graphWidget;          ///< \ru Указатель на объект виджета рисования.
  QLabel      * lblDegreeBSpline;     ///< \ru  Указатель на объект надписи для текстового поля ввода порядка.
  QLineEdit   * leDegreeBSpline;      ///< \ru  Указатель на объект текстового поля для ввода порядка.

  QAction * ExitAction;               ///< \ru Действие выхода из приложения.
  QAction * AboutAction;              ///< \ru Действие о приложении.
  QAction * HelpAction;               ///< \ru Действие помощи по приложению.

  QAction * LoadAction;               ///< \ru Действие загрузки данных.
  QAction * SaveAction;               ///< \ru Действие сохранения данных.

  QAction * DrawPointAction;          ///< \ru Действие рисования точки.
  QAction * DrawSegmentAction;        ///< \ru Действие рисования отрезка.
  QAction * DrawEllipseAction;        ///< \ru Действие рисования эллипса.
  QAction * DrawNurbsAction;          ///< \ru Действие рисования Nurbs.
  QAction * FindIntersectionAction;   ///< \ru Действие поиска пересечений.
  QAction * CleanAllAction;           ///< \ru Очистить все.
  QAction * DeleteSelectAction;       ///< \ru Удалить все выделенные объекты.

  QMenu * FileMenu;                   ///< \ru Меню загрузки и сохранения файлов.
  QMenu * CurveMenu;                  ///< \ru Меню работы с кривыми.
  QMenu * SolutionMenu;               ///< \ru Меню нахождений пересечений.
  QMenu * AboutMenu;                  ///< \ru Вспомогательное меню.

  QToolBar     * ActionsToolbar;      ///< \ru Тулбар.
  QButtonGroup * ActionsTypeGroup;    ///< \ru Группа кнопок на тулбаре.
  QToolButton * nurbsButton;

  size_t height;                      ///< \ru Высота главного окна.
  size_t width;                       ///< \ru Ширина главного окна.

public:

  /// \ru Конструктор по созданию главного окна приложения.
  MainWindow( QWidget * parent = 0 );

private slots:

  void GetMode();
  /// \ru Установка режима работы с кривыми.
  void ActionsGroupClicked( int );
  /// \ru О программе.
  void About();
  /// \ru Подсказки.
  void ShowHelp();
  /// \ru Нарисовать точку.
  void DrawPoint();
  /// \ru Нарисовать отрезок.
  void DrawSegment();
  /// \ru Нарисовать эллипс.
  void DrawEllipse();
  /// \ru нарисовать Nurbs.
  void DrawNurbs();
  /// \ru Найти пересечения.
  void FindIntersection();
  /// \ru Очистить все.
  void CleanAll();
  /// \ru Удалить выделенные.
  void DeleteSelect();

private:

  /// \ru Создать действия.
  void CreateActions();
  /// \ru Создать меню.
  void CreateMenus();
  /// \ru Создать тулбар.
  void CreateToolbars();
};


#endif // __MAINWINDOW_H_
