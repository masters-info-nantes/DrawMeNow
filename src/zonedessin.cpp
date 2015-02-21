#include "zonedessin.h"
#include <qapplication.h>

zoneDessin::zoneDessin()
{
    setFixedSize(780,475);
    setPalette(QPalette(QColor(255, 255, 255)));
    setAutoFillBackground(true);

    tracer = false;
    rubber = false;
    pos = QPoint(0,0);
    pen = QPen(Qt::black);


    //pour faire de jolies lignes
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    setCursor(Qt::CrossCursor);

    image = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    previous = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    next = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);

}

void zoneDessin::setPenColor(QColor color)
{
    pen.setColor(color);
}

void zoneDessin::setPenWidth( int width)
{
    pen.setWidth(width);
}

void zoneDessin::setSize(int weight , int height)
{
    setFixedSize(weight,height);
}

void zoneDessin::setRubber(bool isRubber)
{
    rubber = isRubber;
}

int zoneDessin::getPenWidth()
{
    return pen.width();
}

QColor zoneDessin::getPenColor()
{
    return pen.color();
}

void zoneDessin::resetImage()
{
    image = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    previous = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    next = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    update();
}

void zoneDessin::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawImage(0,0,*image);
}

void zoneDessin::mouseMoveEvent(QMouseEvent *event)
{
    if(tracer)
    {
        if(rubber)
        {
            QPainter painter(image);
           // painter.setBackgroundMode(Qt::TransparentMode);
          //  painter.setBackground(QBrush(QPixmap(":Fond/capy.jpg")));
            painter.setPen(pen);
            painter.setCompositionMode( QPainter::CompositionMode_Clear );
            painter.eraseRect(QRectF(event->pos().x()-(pen.width()/2),event->pos().y()-(pen.width()/2),pen.width(),pen.width()));
            painter.setCompositionMode( QPainter::CompositionMode_SourceOver );
            pos = event->pos();
            update();
        }
        else
        {
            QPainter painter(image);
            painter.setPen(pen);
            painter.drawLine(pos,event->pos());
            pos = event->pos();
            update();
        }
    }
}

void zoneDessin::mousePressEvent(QMouseEvent *event)
{
    tracer = true;
    previous = new QImage(image->copy());
    pos = event->pos();
    if(!rubber)
    {
        QPainter painter(image);
        painter.setPen(pen);
        painter.drawPoint(event->pos());
        update();
    }
}

void zoneDessin::mouseReleaseEvent(QMouseEvent *event)
{
   tracer = false;
   pos = QPoint(0,0);
}

void zoneDessin::undo()
{
    next = new QImage(image->copy());
    image = new QImage(previous->copy());
    update();
}

void zoneDessin::redo()
{
    previous = new QImage(image->copy());
    image = new QImage(next->copy());
    update();
}

void zoneDessin::saveImage(QString path)
{
    image->save(path);
}


