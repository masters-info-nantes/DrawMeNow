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
    layout = new QGridLayout(this);

    indexL = new QLabel(QString::number(index));
    //definir la place prise sur la taille
    QSizePolicy spInfo(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo.setHorizontalStretch(1);
    indexL->setSizePolicy(spInfo);
    indexL->setAlignment(Qt::AlignVCenter);

    layout->addWidget(indexL,0,0);

    image = new QLabel("test");
    img = QImage(this->path);
    pix = pix.fromImage(img.scaled(150,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    image->setPixmap(pix);
    //definir la place prise sur la taille
    QSizePolicy spInfo2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo2.setHorizontalStretch(3);
    image->setSizePolicy(spInfo2);

    layout->addWidget(image,0,1);

   // QMessageBox::information(this, "Draw Me Now", this->desPath);
    image2 = new QLabel("test");
    img2 = QImage(this->desPath);
       // QMessageBox::information(this, "Draw Me Now", "ok1");
    pix2 = pix2.fromImage(img2.scaled(150,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
       // QMessageBox::information(this, "Draw Me Now", "ok2");
    image2->setPixmap(pix2);
       // QMessageBox::information(this, "Draw Me Now", "ok1");
    //definir la place prise sur la taille
    QSizePolicy spInfo3(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo3.setHorizontalStretch(3);
    image2->setSizePolicy(spInfo3);

    layout->addWidget(image2,0,1);

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
