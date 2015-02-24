#ifndef SAVELOCATION_H
#define SAVELOCATION_H
#include<QtGui>
#include<QtWidgets>
#include<QObject>
#include<QApplication>
#include "newproject.h"
#include "mainwindow.h"

class saveLocation : public QWidget
{
    Q_OBJECT
public:
    saveLocation();
    ~saveLocation();
   void setVideoPath(QString);
   void setFreq(int);

public slots :
    void goMain();
    void goReturn();
    void browse();

private :
    QString savePath;
    QString videoPath;
    int freq;
    QVBoxLayout *layout;
    QLabel *labelChoose;
    QHBoxLayout *layoutLoad;
    QLineEdit *loadPath;
    QPushButton *browseButton;
    QHBoxLayout *layoutButton;
    QPushButton *returnButton;
    QPushButton *validateButton;
};

#endif // SAVELOCATION_H
