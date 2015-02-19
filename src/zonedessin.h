#ifndef ZONEDESSIN_H
#define ZONEDESSIN_H

#include <QtWidgets>
#include <QObject>

class zoneDessin : public QWidget
{
     Q_OBJECT

public:

    zoneDessin();
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setPenColor(QColor color);
    void setPenWidth( int width);
    void setSize(int weight , int height);
    void setRubber(bool isRubber);

    QColor getPenColor();
    int getPenWidth();

    void resetImage();
    void undo();
    void redo();
    void saveImage(QString path);




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
