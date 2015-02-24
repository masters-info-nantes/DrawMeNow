#ifndef ZONEPREVIEW_H
#define ZONEPREVIEW_H

#include <QtWidgets>
#include <QObject>
#include <imagenmodule.h>

class zonePreview : public QWidget
{
    Q_OBJECT
public:
    zonePreview();

    QGridLayout *layout;

    QLabel *title;
    QPushButton *preview;
    QRadioButton *beginning;
    QCheckBox *withBg;
    QRadioButton *lastImg;
    imageNModule *img;

    QString currentDes;
    QString imgFolder;
    QString desFolder;
    int desValue;

    int nbLI;
    int fps;

    void setImg(QString desFolder, QString imgFolder,QString current, int value);
    void setFps(int fps);

public slots :
    void go();
    void click();
    void clickLI();
    void nbImgChange(int number);

};

#endif // ZONEPREVIEW_H
