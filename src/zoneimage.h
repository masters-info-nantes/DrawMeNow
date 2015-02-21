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
    zoneImage();

    QVBoxLayout *layout;
    QScrollArea *area;
    imageDefiler *img;
    fnumberModule *fnumber;

    void setFrameNumber(int number);
    void setCurrentFrame(int index);

};

#endif // ZONEIMAGE_H
