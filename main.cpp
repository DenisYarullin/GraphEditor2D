#include <QtWidgets>
#include <QApplication>
#include "mainwindow.h"


int main(int argv, char *args[])
{
  QApplication app(argv, args);

  MainWindow mainWindow;
  mainWindow.setWindowIcon( QIcon(":/images/title.jpg") );
  mainWindow.showMaximized();

  return app.exec();
}

