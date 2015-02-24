#ifndef NEWPROJECT_H
#define NEWPROJECT_H
#include<QtGui>
#include<QtWidgets>
#include<QObject>
#include<QApplication>
#include "welcome.h"
#include "savelocation.h"

class newProject : public QWidget
{
    Q_OBJECT
public:
    newProject();
    ~newProject();

public slots:
    void browse();
    void goReturn();
    void goMain();

private :
    QString path;
    int freq;
    QVBoxLayout *layout;
    QLabel *labelChoose;
    QHBoxLayout *layoutLoad;
    QLineEdit *loadPath;
    QPushButton *browseButton;
    QVBoxLayout *widgetFreq;
    QLabel *labelChooseFreq;
    QButtonGroup *buttonFreq;
    QRadioButton *button6Freq;
    QRadioButton *button8Freq;
    QRadioButton *button12Freq;
    QRadioButton *button24Freq;
    QHBoxLayout *layoutButton;
    QPushButton *returnButton;
    QPushButton *validateButton;

};

#endif // NEWPROJECT_H
