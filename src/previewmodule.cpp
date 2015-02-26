#include "previewmodule.h"
#include <QtWidgets>
#include <QAction>
#include <QApplication>


previewModule::previewModule(QString desFolder, QString imgFolder,QString desPath, int desValue)
{
    setWindowTitle("Preview");
    setPalette(QPalette(QColor(Qt::black)));
    setAutoFillBackground(true);

    layout = new QVBoxLayout(this);
    imgLayout = new QGridLayout();
    buttonLayout = new QHBoxLayout();

    this->desValue = desValue;
    this->imgFolder = imgFolder;
    this->desFolder = desFolder;

    dessin = new QLabel("test");
    img = QImage(desPath);
    pix = pix.fromImage(img.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    dessin->setPixmap(pix);

    image = new QLabel("test");
    img2 = QImage(imgFolder + "/image" + QString::number(desValue) + ".jpg");
    pix2 = pix2.fromImage(img2.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    image->setPixmap(pix2);

    image->setStyleSheet("background:transparent;");
    image->setAttribute(Qt::WA_TranslucentBackground);

  /*  fond = new QLabel("test");
    img3 = QImage(":Fond/blanc.png");
    pix3 = pix3.fromImage(img3.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    fond->setPixmap(pix3);*/
    fond = new fondDessin();

    //dessin transparent
    dessin->setStyleSheet("background:transparent;");
    dessin->setAttribute(Qt::WA_TranslucentBackground);
    dessin->setWindowFlags(Qt::FramelessWindowHint);

    imgLayout->addWidget(fond,0,0);
    imgLayout->addWidget(image,0,0);
    imgLayout->addWidget(dessin,0,0);

    move(QPoint(400,150));

    layout->addLayout(imgLayout);


    play = new QPushButton("");
    //style
    play->setIcon(QIcon(":Icones/play.png"));
    play->setIconSize(QSize(80,80));
    play->setFixedSize(80,80);
    play->setStyleSheet("QPushButton{border: none;outline: none;}");
    play->setCursor(Qt::PointingHandCursor);
    //fonction
    connect(play, SIGNAL(clicked()),this,SLOT(playVideo()));

    pause = new QPushButton("");
    //style
    pause->setIcon(QIcon(":Icones/pause.png"));
    pause->setIconSize(QSize(80,80));
    pause->setFixedSize(80,80);
    pause->setStyleSheet("QPushButton{border: none;outline: none;}");
    pause->setCursor(Qt::PointingHandCursor);
    //fonction
    connect(pause, SIGNAL(clicked()),this,SLOT(pauseVideo()));

    stop = new QPushButton("");
    //style
    stop->setIcon(QIcon(":Icones/stop.png"));
    stop->setIconSize(QSize(80,80));
    stop->setFixedSize(80,80);
    stop->setStyleSheet("QPushButton{border: none;outline: none;}");
    stop->setCursor(Qt::PointingHandCursor);
    //fonction
    connect(stop, SIGNAL(clicked()),this,SLOT(stopVideo()));

    quit = new QPushButton("Close");
    quit->setIcon(QIcon(":Icones/close.png"));
    quit->setCursor(Qt::PointingHandCursor);
    quit->setFixedSize(80,35);
    //fonction
    connect(quit, SIGNAL(clicked()),this,SLOT(closePreview()));


    buttonLayout->addWidget(stop);
    buttonLayout->addWidget(play,2,Qt::AlignRight);
    buttonLayout->addWidget(pause,2,Qt::AlignCenter);

    buttonLayout->addWidget(quit,1,Qt::AlignRight);


    layout->addLayout(buttonLayout);

    beginning = false;
    hideBg = false;
    fps = 6;
    nbImg = 0;

    //permet de savoir si c est en cours
    ind = 0;
}

void previewModule::setBeginning(bool beg)
{
    beginning = beg;
}

void previewModule::setHideBg(bool hide)
{
     hideBg = hide;
    if(hide)
    {
        img2 = QImage(":Fond/blanc.png");
        pix2 = pix2.fromImage(img2.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        image->setPixmap(pix2);
    }
}

void previewModule::setNbImg(int number)
{
    nbImg = number;
}


void previewModule::setFps(int fps)
{
    this->fps = (double)fps;
}

void previewModule::playVideo()
{
    //si c'est déja en cours on refait pas tout
    if(ind ==0)
    {
        if(beginning)
            {ind = 1;}
        else
        {
            ind = desValue - nbImg -1;
            if(ind < 1)
                {ind = 1;}
        }
        timer = new QTimer();
        timer->connect(timer, SIGNAL(timeout()),this, SLOT(nextImg()));
        double interv = 1.0/fps * 1000.0;

        timer->setInterval((int) interv);
    }
    timer->start();
}

void previewModule::pauseVideo()
{
    timer->stop();
}

void previewModule::nextImg()
{
    if(!beginning)
    {
        QFile *img3 = new QFile(imgFolder + "/image" + QString::number(ind) +".jpg");
        if((img3->exists()) && (ind<=desValue))
        {
            if(!hideBg)
            {
                img2 = QImage(imgFolder + "/image" + QString::number(ind) + ".jpg");
                pix2 = pix2.fromImage(img2.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                image->setPixmap(pix2);
            }

            img = QImage(desFolder + "/dessin" + QString::number(ind) + ".png");
            pix = pix.fromImage(img.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            dessin->setPixmap(pix);

            ind ++;
        }
        else
        {//QMessageBox::information(this,"test", QString::number(ind));
            timer->stop();
            ind =0;
        }
    }
    else
    {
        QFile *img3 = new QFile(imgFolder + "/image" + QString::number(ind) +".jpg");
        if(img3->exists())
        {
            if(!hideBg)
            {
                img2 = QImage(imgFolder + "/image" + QString::number(ind) + ".jpg");
                pix2 = pix2.fromImage(img2.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                image->setPixmap(pix2);
            }

            img = QImage(desFolder + "/dessin" + QString::number(ind) + ".png");
            pix = pix.fromImage(img.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            dessin->setPixmap(pix);

            ind ++;
        }
        else
        {
            timer->stop();
            ind = 0;
        }
    }

}

void previewModule::closePreview()
{
    this->close();
}

void previewModule::stopVideo()
{
    timer->stop();
    ind = 0;
}
