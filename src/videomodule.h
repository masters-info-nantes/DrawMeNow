#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#include <QtWidgets>
#include <QObject>

class videoModule : public QWidget
{
    Q_OBJECT

public:
    videoModule(QString video, int framerate);

    int index;
    int framerate;
    QString video;
    QProcess* process;
    QProcess* process1;
    QProcess* process2;
    QString command;
    QString command1;
    QString command2;

    QString imgFolder;
    QString desFolder;
    QString currentImg;
    QString currentDes;

    void buildFrame(QString folder);
    QString getImgFolder();
    QString getDesFolder();
    QString getCurrentImg();
    QString getCurrentDes();
    QString goToNextImg();
    int frameNumber();

public slots:

    void imgReady();

signals:
   void firstImageReady();
};

#endif // VIDEOMODULE_H
