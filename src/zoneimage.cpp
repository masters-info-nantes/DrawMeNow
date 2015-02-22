#include "zoneimage.h"
#include <QAction>
#include <QApplication>

zoneImage::zoneImage(QString imgfolder,QString desFolder, int frameNumber)
{
    setPalette(QPalette(QColor(99, 99, 99)));
    setAutoFillBackground(true);

    //dossier contenant les images et dessins
    this->imgFolder = QString(imgfolder);
    this->desFolder = QString(desFolder);

    layout  = new QVBoxLayout(this);

    //les mini images
    area = new QScrollArea();
    img = new imageDefiler(imgfolder, desFolder);
    connect(img,SIGNAL(imageChanged(QString,QString,int)),this,SLOT(imageChanged(QString,QString,int)));
    connect(img,SIGNAL(viewChange()),this,SLOT(defilerMove()));
    area->setWidget(img);
    area->setAlignment(Qt::AlignVCenter);
    layout->addWidget(area);

    //une ligne pour separer
    QFrame *line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 480, 600, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    //choix du numero d'image
    fnumber = new fnumberModule(frameNumber);
    connect(fnumber,SIGNAL(valueChange(int)),this,SLOT(valueChanged(int)));
    layout->addWidget(fnumber);

    setLayout(layout);
}

void zoneImage::clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void zoneImage::setParam(QString imgfolder,QString desFolder, int frameNumber)
{
    clearLayout(layout);
    setPalette(QPalette(QColor(99, 99, 99)));
    setAutoFillBackground(true);

    this->imgFolder = QString(imgfolder);
    this->desFolder = QString(desFolder);

    //les mini images

    area = new QScrollArea();
    img = new imageDefiler(imgfolder, desFolder);
    connect(img,SIGNAL(imageChanged(QString,QString,int)),this,SLOT(imageChanged(QString,QString,int)));
    connect(img,SIGNAL(viewChange()),this,SLOT(defilerMove()));
    area->setWidget(img);
    area->setAlignment(Qt::AlignVCenter);
    layout->addWidget(area);

    //une ligne pour separer
    QFrame *line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 480, 600, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    //choix du numero d'image
    fnumber = new fnumberModule(frameNumber);
    connect(fnumber,SIGNAL(valueChange(int)),this,SLOT(valueChanged(int)));
    layout->addWidget(fnumber);

}

void zoneImage::setFrameNumber(int number)
{

}

void zoneImage::setCurrentFrame(int index)
{

}

//quand on choisit une image dans le defiler
void zoneImage::imageChanged(QString path,QString desPath,int value)
{
    fnumber->setValue(value);
    emit imageChange(path, desPath);
}

void zoneImage::valueChanged(int value)
{
    if(value%20 !=0)
        {area->verticalScrollBar()->setValue((value%20)*95);}
    else
        {area->verticalScrollBar()->setValue(value*95);}

    img->setCurrentImage(value);
    emit imageChange(img->getCurrentImagePath(), img->getCurrentImageDesPath());
}

void zoneImage::defilerMove()
{
    area->verticalScrollBar()->setValue(0);
}
