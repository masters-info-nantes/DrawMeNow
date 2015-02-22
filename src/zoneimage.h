#ifndef ZONEIMAGE_H
#define ZONEIMAGE_H

#include <QtWidgets>
#include <QObject>
#include <imagemodule.h>
#include <fnumbermodule.h>
#include <imagedefiler.h>

class zoneImage : public QWidget
{
      Q_OBJECT

public:
    zoneImage(QString folder, QString desFolder, int frameNumber);

    QVBoxLayout *layout;
    QScrollArea *area;
    imageDefiler *img;
    fnumberModule *fnumber;

    QString imgFolder;
    QString desFolder;

    void setFrameNumber(int number);
    void setCurrentFrame(int index);
    void setParam(QString imgfolder,QString desFolder, int frameNumber);
    void clearLayout(QLayout *layout);
public slots:
    void imageChanged(QString path,QString desPath,int value);
    void valueChanged(int value);
    void defilerMove();

signals:
    void imageChange(QString path, QString desPath);


};

#endif // ZONEIMAGE_H
