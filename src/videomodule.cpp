#include "videomodule.h"

videoModule::videoModule(QString video, int framerate)
{
    index = 1;
    this->framerate = framerate;
    this->video = video;
    process = new QProcess();
}

void videoModule::buildFrame(QString folder)
{
    command = "avconv -i "+video+" -vsync 1 -r "+QString::number(framerate)+" -an -y " + folder+"/image%d.jpg";
   // command = "avconv -i "+video+" -vsync 1 -r "+QString::number(framerate)+" -an -y /home/muriel/workspace/Test/src/images/image%d.jpg";
    process->start(command);
}
