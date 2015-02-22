#include "imagemodule.h"
#include <QAction>
#include <QApplication>

imageModule::imageModule(QString path,QString desPath, int index)
{
    setPalette(QPalette(QColor(0, 0, 0)));
    setAutoFillBackground(true);

    this->path = path;
    this->desPath = desPath;
    this->index = index;
    layout = new QHBoxLayout(this);

    indexL = new QLabel(QString::number(index));
    //definir la place prise sur la taille
    QSizePolicy spInfo(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo.setHorizontalStretch(1);
    indexL->setSizePolicy(spInfo);
    indexL->setAlignment(Qt::AlignVCenter);

    layout->addWidget(indexL);
    image = new QLabel("test");
    img = QImage(this->path);
    pix = pix.fromImage(img.scaled(150,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    image->setPixmap(pix);
    //definir la place prise sur la taille
    QSizePolicy spInfo2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo2.setHorizontalStretch(3);
    image->setSizePolicy(spInfo2);

    layout->addWidget(image);

    setLayout(layout);
    setCursor(Qt::PointingHandCursor);

}

void imageModule::setActive(bool active)
{
    if(active)
    {
        setPalette(QPalette(QColor(215, 215, 215)));
        setAutoFillBackground(true);
    }
    else
    {
        setPalette(QPalette(QColor(0, 0, 0)));
        setAutoFillBackground(true);
    }
}

QString imageModule::getPath()
{
    return path;
}

QString imageModule::getDesPath()
{
    return desPath;
}

void imageModule::mousePressEvent(QMouseEvent *event)
{
    emit imageChange(path,desPath,index);
}
