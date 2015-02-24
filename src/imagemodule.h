#ifndef IMAGEMODULE_H
#define IMAGEMODULE_H

#include <QtWidgets>
#include <QObject>
#include <QApplication>

class imageModule : public QWidget
{
    Q_OBJECT
public:
    imageModule(QString path,QString desPath, int index);

    QGridLayout *layout;

    QString path;
    QString desPath;
    int index;

    QLabel *image;
    QLabel *indexL;
    QLabel *dessin;
    QImage img;
    QPixmap pix;

    QLabel *image2;
    QImage img2;
    QPixmap pix2;


    void setActive(bool active);
    void mousePressEvent(QMouseEvent *event);
    QString getPath();
    QString getDesPath();

signals:
    void imageChange(QString path,QString desPath,int index);
};

#endif // IMAGEMODULE_H
