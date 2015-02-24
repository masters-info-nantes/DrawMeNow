#include "imagedefiler.h"
#include <QAction>
#include <QApplication>

imageDefiler::imageDefiler(QString imgfolder, QString desFolder)
{

    layout = new QVBoxLayout(this);
    index = 1;
    this->imgFolder = imgfolder;
    this->desFolder = desFolder;
    if((this->imgFolder != "") && (this->desFolder!=""))
    {         ;
        modifieLayout(0);
        activeImage(1);
    }
   // setLayout(layout);
}

//rajouter emit signal pour scrollbar
void imageDefiler::nextClick()
{
    modifieLayout(index);
    activeImage(1);
    emit viewChange();
}

void imageDefiler::previousClick()
{
    modifieLayout(index -40);
    activeImage(1);
}
void clearLayout(QLayout *layout){
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
void imageDefiler::modifieLayout(int index)
{
    //QMessageBox::information(this,"test",QString::number(index) );
    clearLayout(layout);
    images.clear();
    this->index = index;

    if(index >=20)
    {
        previous = new QPushButton("Previous");
        previous->setCursor(Qt::PointingHandCursor);
        previous->setStyleSheet("border-color: black; color : black;");
        connect(previous, SIGNAL(clicked()), this, SLOT(previousClick()));
        layout->addWidget(previous);
    }

    next = new QPushButton("next");
    next->setCursor(Qt::PointingHandCursor);
    next->setStyleSheet("border-color: black; color : black;");
    connect(next, SIGNAL(clicked()), this, SLOT(nextClick()));

    for(int i=0;i<(20);i++)
    {
            //QMessageBox::information(this,"test",folder + "/image" + QString::number(i+1) +".jpg");
         QFile img(imgFolder + "/image" + QString::number(index + i+1) +".jpg");
         if(img.exists())
         {
             images.push_back(new imageModule(imgFolder + "/image" + QString::number(index + i+1) +".jpg" ,
                                              desFolder + "/dessin" + QString::number(index + i+1) +".png" ,
                                              (index+1 - ((index)%20)) +i));
             connect(images[i], SIGNAL(imageChange(QString,QString,int)),this, SLOT(imageChange(QString,QString,int)));
             layout->addWidget(images[i]);
             this->index += 1;
         }else
         {
             this->index += 1;
             next->hide();
         }
     }
     QFile img2(imgFolder + "/image" + QString::number(this->index) +".jpg");
     if(!(img2.exists()))
     {
          next->hide();
     }

    layout->addWidget(next);

    layout->setAlignment(Qt::AlignVCenter);
    update();
}

//gerer la scrollbar
void imageDefiler::setCurrentImage(int current)
{
 // QMessageBox::information(this,"test","image changed " + QString::number(current+1 - (current+1%20)));
    if(current%20 != 0)
    {
        modifieLayout(current - ((current)%20) );
    }
    else
    {   //en theorie pas de pb vu que le min c est 1 pas 0
        modifieLayout(current -20);
    }

    activeImage(current);

}


QString imageDefiler::getCurrentImagePath()
{
    return images[imgActive]->getPath();
}

void imageDefiler::imageChange(QString path,QString desPath,int value)
{
    setCurrentImage(value);
     emit imageChanged(path,desPath,value);
}

void imageDefiler::activeImage(int current)
{

    if(current%20 !=0)
    {
        images[current%20 -1]->setActive(true);
        imgActive =current%20 -1;
    }else
    {
        images[19]->setActive(true);
        imgActive =19;
    }
}

QString imageDefiler::getCurrentImageDesPath()
{
    return images[imgActive]->getDesPath();
}
