#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#include <QtWidgets>
#include <QObject>

class videoModule
{
public:
    videoModule(QString video, int framerate);

    int index;
    int framerate;
    QString video;
    QProcess* process;
    QString command;

    void buildFrame(QString folder);
};

#endif // VIDEOMODULE_H
