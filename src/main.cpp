#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QtWidgets>
#include <welcome.h>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow window ;
   // welcome w ;
    window.setVideo("/home/muriel/workspace/Exercice1/video.3gp","/home/muriel/workspace/Exercice1",6);
   // window.setFps(24);
    return a.exec();
}
