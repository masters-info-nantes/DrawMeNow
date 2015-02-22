#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QtWidgets>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow window ;
   // window.setVideo("/home/muriel/workspace/Exercice1/video.3gp","/home/muriel/workspace/Exercice1",8);
  //  window.setFps(24);
    return a.exec();
}
