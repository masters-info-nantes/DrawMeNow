#ifndef ZONEDESSIN_H
#define ZONEDESSIN_H

#include <QtWidgets>
#include <QObject>

class zoneDessin : public QWidget
{
     Q_OBJECT

public:

    zoneDessin(QString path);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setPenColor(QColor color);
    void setPenWidth( int width);
    void setSize(int weight , int height);
    void setRubber(bool isRubber);
    void setImgPath(QString path);

    void resetImage();
    void undo();
    void redo();
    void saveImage();
    void saveImage(QString path);
    void loadImage(QString path);
    void activeSave(bool active);


    QColor getPenColor();
    int getPenWidth();
    QString imgPath;
    bool save;
    QImage  img;


 /*   QPainter *painter;
    QPen pen;
    QPoint deb;
    QPoint fin;*/

    bool tracer;
    bool rubber;

    QPoint pos;
    QPen pen;

    QImage *previous;
    QImage *next;
    QImage *image;
};

#endif // ZONEDESSIN_H
