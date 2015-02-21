#include "imagemodule.h"

imageModule::imageModule(QString path, int index)
{
    setPalette(QPalette(QColor(0, 0, 0)));
    setAutoFillBackground(true);

    this->path = path;
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
    img = QImage(path);
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
