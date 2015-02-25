#ifndef WELCOME_H
#define WELCOME_H
#include<QtGui>
#include<QtWidgets>
#include<QObject>
#include<QApplication>
#include "newproject.h"
#include "existingproject.h"
class welcome : public QWidget
{
    Q_OBJECT
public:
    welcome();
    ~welcome();

public slots:
    void goNewProject();
    void goExistingProject();

private :
     QWidget *window;
     QPushButton *buttonNewProject;
     QPushButton *buttonOpenExisting;
     QVBoxLayout *layout;
     QLabel *labelWelcome;
     QLabel *labelTitle;
     QHBoxLayout *buttonLayout;
     QVBoxLayout *leftButton;
     QVBoxLayout *rightButton;


};

#endif // WELCOME_H
