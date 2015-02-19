#ifndef SIZEMODULE_H
#define SIZEMODULE_H

#include <QtWidgets>
#include <QObject>
#include <zonedessin.h>
#include <mainwindow.h>
#include <QAction>
#include <QApplication>

class MainWindow;

class sizeModule : public QWidget
{
    Q_OBJECT

public slots:
    void setPenSize(int);
    void validateW();
    void cancelW();
    void cleanW();

public:
    sizeModule(MainWindow * main);

    MainWindow *main;
    zoneDessin *zone;
    QSlider *slider;
    QSpinBox *size;

    QLabel *label;
    QVBoxLayout *layout;
    QHBoxLayout *boutons;
    QPushButton *clean;
    QPushButton *validate;
    QPushButton *cancel;

    void setPenColor(QColor color);
};

#endif // SIZEMODULE_H
