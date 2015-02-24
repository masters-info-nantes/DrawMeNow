#include "zonelayer.h"

zoneLayer::zoneLayer()
{
    setFixedSize(780,475);
    setAutoFillBackground(true);

    layout = new QGridLayout(this);
    layerNumber = 0;
    layerFrequency = 0;
    desFolder = "";
    currentPath ="";
    currentDesValue = 0;
}

void zoneLayer::setLayerNumber(int number)
{
    layerNumber = number;
   // QMessageBox::information(this,"test","path : " + currentPath + " value : " + QString::number(currentDesValue) + " fold : " + desFolder);
    if((currentPath != "") && (currentDesValue != 0) && (desFolder !=""))
        {buildLayers();}
}

void zoneLayer::setLayerFrequency(int frequency)
{
    layerFrequency = frequency;
    if((currentPath != "") && (currentDesValue != 0) && (desFolder !=""))
        {buildLayers();}
}

void zoneLayer::setDesFolder( QString folder)
{
    desFolder = folder;
}

void zoneLayer::setCurrentDessin( QString path, int value)
{
    currentPath = path;
    currentDesValue = value;
    buildLayers();
}

void zoneLayer::clearLayout(QLayout *layout){
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

void zoneLayer::buildLayers()
{
    clearLayout(layout);
    layers.clear();
    int ind = 0;
    double op = 0.2;
    double incr = 1.0/layerNumber;

    //QMessageBox::Information(this,"test",QString::number(incr));
    for(int i=0; i< layerNumber;i++)
    {
        if(i < currentDesValue)
        {
            int numero = currentDesValue - i*layerFrequency;
            QString path = desFolder + "/dessin" + QString::number(numero) + ".png";

            if((path != currentPath))
            {
                QFile *file = new QFile(path);
                if((file->exists()))
                {
                    img =  QImage(path);
                    pix = pix.fromImage(img.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

                  //  image->setPixmap(pix);
                    layers.push_back(new QLabel(""));
                    layers[ind]->setPixmap(pix);

                    //opacite
                     QPixmap result(pix.size());
                     result.fill(Qt::transparent);


                     QPainter painter;
                     painter.begin(&result);
                     double opa = op + ((layerNumber -i)*incr);
                     if (opa >0.85) { opa = 0.85;}
                     painter.setOpacity(opa);
                     painter.drawPixmap(0, 0, pix);
                     painter.end();
                     layers[ind]->setPixmap(result);

                    ind++;
                }
            }
         }
    }


    for(unsigned int j=0;j<layers.size();j++)
    {
         layers[j]->setStyleSheet("background:transparent; ");
         layers[j]->setAttribute(Qt::WA_TranslucentBackground);



         //layers[j]->setWindowFlags(Qt::FramelessWindowHint);
         layout->addWidget(layers[j],0,0);
    }

    update();

}

