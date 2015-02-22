#include "videomodule.h"
#include <QAction>
#include <QApplication>

videoModule::videoModule(QString video, int framerate)
{
    index = 1;
    this->framerate = framerate;
    this->video = video;
    process = new QProcess();
}

void videoModule::buildFrame(QString folder)
{
    desFolder = QString(folder+"/dessins");
    imgFolder = QString(folder+"/images");
    currentImg = QString(imgFolder + "/image1.jpg");
    currentDes = QString(desFolder + "/dessin1.png");

    //creation du dossier images
    process1 = new QProcess();
    command1 = "mkdir " +folder +"/images";
    process1->start(command1);

    //creation du dossier dessins

    process2 = new QProcess();
    command2 = "mkdir " +folder +"/dessins";
    process2->start(command2);

    //creation des images

    command = "avconv -i "+video+" -vsync 1 -r "+QString::number(framerate)+" -an -y " + imgFolder +"/image%d.jpg";
    process->start(command);
    connect(process,SIGNAL(finished(int)),this,SLOT(imgReady()));

}

QString videoModule::getImgFolder()
{
    return imgFolder;
}

QString videoModule::getDesFolder()
{
    return desFolder;
}

QString videoModule::getCurrentImg()
{
    return currentImg;
}
QString videoModule::getCurrentDes()
{
    return currentDes;
}


QString videoModule::goToNextImg()
{
    index += 1;
    currentImg = QString(imgFolder + "/image" + QString::number(index) +".jpg");
    currentDes = QString(desFolder + "/dessin" + QString::number(index) +".png");
    return currentImg;
}

int videoModule::frameNumber()
{
    int res =0;
    QFile *img = new QFile(imgFolder + "/image" + QString::number(res+1) +".jpg");
    while((img->exists()))
    {
        res++;
        img = new QFile(imgFolder + "/image" + QString::number(res+1) +".jpg");
    }
    return res;
}

void videoModule::imgReady()
{
    emit firstImageReady();
}

