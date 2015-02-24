#ifndef PREVIEWMODULE_H
#define PREVIEWMODULE_H

#include <QtWidgets>
#include <QObject>
#include <fonddessin.h>

class previewModule : public QWidget
{
    Q_OBJECT
public:
    previewModule(QString desFolder, QString imgFolder, QString desPath, int desValue);

    QVBoxLayout *layout;
    QHBoxLayout *buttonLayout;
    QGridLayout *imgLayout;

    QLabel *dessin;
    QLabel *image;
   // QLabel *fond;
    QImage img;
    QImage img2;
    QImage img3;

    QPixmap pix;
    QPixmap pix2;
    QPixmap pix3;

    fondDessin *fond;

    QString imgFolder;
    QString desFolder;

    QPushButton *play;
    QPushButton *pause;
    QPushButton *quit;

    QTimer *timer;

    int desValue;
    int ind;
    int nbImg;
    bool beginning;
    bool hideBg;
    double fps;

    void setBeginning(bool beg);
    void setHideBg(bool hide);
    void setFps(int fps);
    void setNbImg(int number);

public slots:
    void playVideo();
    void pauseVideo();
    void closePreview();
    void nextImg();

};

#endif // PREVIEWMODULE_H
