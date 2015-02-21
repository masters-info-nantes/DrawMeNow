#include "fnumbermodule.h"
#include <QAction>
#include <QApplication>

fnumberModule::fnumberModule()
{
    setFixedSize(200,100);

    layout = new QVBoxLayout();
    choice = new QHBoxLayout();

    lab = new QLabel("Go To (Frame Number) :");
    layout->addWidget(lab);


    box = new QSpinBox();
    box->setMaximum(3);
    box->setMinimum(1);
    box->setValue(1);

    //si on met pas la suite le texte est blanc
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Text,Qt::black);
    box->setPalette(*palette);
    box->setFixedSize(50,30);
    box->setStyleSheet("border-style: outset;\
                       border-radius: 5px;\
                        border-color: black;");

    choice->addWidget(box);

    go = new QPushButton("Go");
    go->setFixedSize(50,30);
   // go->setPalette(*palette);
    go->setStyleSheet("border-color: black; color : black;");

   // connect(go, SIGNAL(clicked(bool)), this, SLOT(hideBackground(bool)));


    choice->addWidget(go);

    layout->addLayout(choice);
    setLayout(layout);
}
