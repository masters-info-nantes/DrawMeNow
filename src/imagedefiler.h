#ifndef IMAGEDEFILER_H
#define IMAGEDEFILER_H

#include <QtWidgets>
#include <QObject>
#include <QApplication>
#include <imagemodule.h>
#include <vector>

using namespace std;
class imageDefiler : public QWidget
{
    Q_OBJECT
public:
    imageDefiler(QString imgfolder, QString desFolder);

    QVBoxLayout *layout;

    vector<imageModule *> images;
    QPushButton *next;
    QPushButton *previous;
    int index;
    int imgActive;
    QString imgFolder;
    QString desFolder;


    void modifieLayout(int index);
    void setCurrentImage(int current);
    QString getCurrentImagePath();
    QString getCurrentImageDesPath();
    void activeImage(int current);


public slots :

    void nextClick();
    void previousClick();
    void imageChange(QString path,QString desPath, int value);

signals :
    void imageChanged(QString path,QString desPath, int value);
    void viewChange();
};

#endif // IMAGEDEFILER_H
