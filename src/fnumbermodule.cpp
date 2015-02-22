#include "fnumbermodule.h"
#include <QAction>
#include <QApplication>

fnumberModule::fnumberModule(int max)
{
    setFixedSize(200,100);

    layout = new QVBoxLayout();
    choice = new QHBoxLayout();

    lab = new QLabel("Go To (Frame Number) :");
    layout->addWidget(lab);


    box = new QSpinBox();
    if(max ==0)
    {
        box->setMaximum(max);
        box->setMinimum(0);
        box->setValue(0);
    }
    else
    {
        box->setMaximum(max);
        box->setMinimum(1);
        box->setValue(1);
    }

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
    if(max !=0)
    {connect(go, SIGNAL(clicked()), this, SLOT(valideValue()));}

    go->setCursor(Qt::PointingHandCursor);
    choice->addWidget(go);

    layout->addLayout(choice);
    setLayout(layout);
}


void fnumberModule::valideValue()
{
    emit  valueChange(box->value());
}

void fnumberModule::setValue(int value)
{
    box->setValue(value);
}
