#ifndef EXISTINGPROJECT_H
#define EXISTINGPROJECT_H
#include<QtGui>
#include<QtWidgets>
#include<QObject>
#include<QApplication>
#include "welcome.h"
#include "savelocation.h"

class existingProject : public QWidget
{
    Q_OBJECT
public:
    existingProject();
    ~existingProject();

public slots:
    void browse();
    void goReturn();
    void goMain();

private :
    QString path;
    QString videoPath;
    QString desFolder;
    QString imgFolder;
    int freq;
    int layers;
    int layersFreq;
    QVBoxLayout *layout;
    QLabel *labelChoose;
    QHBoxLayout *layoutLoad;
    QLineEdit *loadPath;
    QPushButton *browseButton;
    QVBoxLayout *widgetFreq;
    QLabel *labelVideo;
    QLabel *labelFreq;
    QLabel *labelLayers;
    QLabel *labelLayersFreq;
    QHBoxLayout *layoutButton;
    QPushButton *returnButton;
    QPushButton *validateButton;

};

#endif // EXISTINGPROJECT_H
