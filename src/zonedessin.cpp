#include "zonedessin.h"
#include <qapplication.h>

zoneDessin::zoneDessin(QString imgPath)
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

    this->imgPath = imgPath;

    image = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    previous = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    next = new QImage(780,475,QImage::Format_ARGB32_Premultiplied);
    save = false;
}

void zoneDessin::setPenColor(QColor color)
{
    pen.setColor(color);
}

void zoneDessin::setPenWidth( int width)
{
    pen.setWidth(width);
}

void zoneDessin::activeSave(bool active)
{
    save = active;
}

void zoneDessin::setImgPath(QString path)
{
    imgPath = path;
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
   if(save){saveImage();}
   pos = QPoint(0,0);
}

void zoneDessin::undo()
{
    next = new QImage(image->copy());
    image = new QImage(previous->copy());
    if(save){saveImage();}
    update();
}

void zoneDessin::redo()
{
    previous = new QImage(image->copy());
    image = new QImage(next->copy());
    if(save){saveImage();}
    update();
}

void zoneDessin::saveImage()
{
    image->save(imgPath);
}

void zoneDessin::saveImage(QString path)
{
    image->save(path);
}

void zoneDessin::loadImage(QString path)
{
    //si l'image n'existe pas encore il faut la créer
    if(QFile(path).exists())
    {
        resetImage();
        imgPath = path;
        QImage img(path);
        image = new QImage(img.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        previous = image;
        next = image;
    }
    else
    {
        resetImage();
        imgPath = path;
        image->save(path);
    }
    update();
}


