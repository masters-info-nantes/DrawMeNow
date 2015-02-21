#include "zoneimage.h"

zoneImage::zoneImage()
{
    setPalette(QPalette(QColor(99, 99, 99)));
    setAutoFillBackground(true);


    layout  = new QVBoxLayout(this);

    area = new QScrollArea();
    img = new imageDefiler();
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

    fnumber = new fnumberModule();
    layout->addWidget(fnumber);

    setLayout(layout);
}

void zoneImage::setFrameNumber(int number)
{

}

void zoneImage::setCurrentFrame(int index)
{

}
