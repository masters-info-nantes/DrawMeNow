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
    bool newM;
    QString video;
    QProcess* process;
    QProcess* process1;
    QProcess* process2;

    QProcess *exportProcess;
    QString command;
    QString command1;
    QString command2;

    QString imgFolder;
    QString desFolder;
    QString currentImg;
    QString currentDes;

    void buildFrame(QString folder, bool newM);
    QString getImgFolder();
    QString getDesFolder();
    QString getCurrentImg();
    QString getCurrentDes();
    QString goToNextImg();
    int frameNumber();

    void createVideo(QString path, int fps);

public slots:

    void imgReady();
    void videoReady();

signals:
   void firstImageReady();
   void videoIsReady();
};

#endif // VIDEOMODULE_H
