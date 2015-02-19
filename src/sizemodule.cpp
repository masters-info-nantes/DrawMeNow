#include "sizemodule.h"
#include <QAction>
#include <QApplication>
sizeModule::sizeModule(MainWindow *main)
{
      setWindowTitle("Choose Size");

      layout = new QVBoxLayout(this);
      this->main = main;

      label = new QLabel("Draw here to see the pen size :");
      layout->addWidget(label);

      zone = new zoneDessin();
      zone->setSize(200,200);
      layout->addWidget(zone);

 /*     slider = new QSlider(Qt::Horizontal);
      slider->setRange(1, 10);
      slider->setValue(1);
      connect(slider, SIGNAL(valueChanged(int)),this, SLOT(setPenSize(int)));
      layout->addWidget(slider);*/
      size = new QSpinBox;
      size->setMaximum(30);
      size->setMinimum(1);
      size->setValue(1);
      connect(size, SIGNAL(valueChanged(int)),this, SLOT(setPenSize(int)));
      layout->addWidget(size);

      //bouton pour clean la zone de dessin
      clean = new QPushButton("Clean Drawing Area");
      connect(clean, SIGNAL(clicked()),this, SLOT(cleanW()));
      layout->addWidget(clean);

      //bouton de validation
      boutons = new QHBoxLayout(this);
      validate = new QPushButton("Ok");
      connect(validate, SIGNAL(clicked()),this, SLOT(validateW()));
      boutons->addWidget(validate);

      //bouton quitter
      cancel = new QPushButton("Cancel");
      connect(cancel, SIGNAL(clicked()),this, SLOT(cancelW()));
      boutons->addWidget(cancel);

      layout->addLayout(boutons);
      setLayout(layout);

}

void sizeModule::setPenSize(int size)
{
    zone->setPenWidth(size);
    this->size->setValue(size);
}

void sizeModule::setPenColor(QColor color)
{
    zone->setPenColor(color);
}

void sizeModule::validateW()
{
    main->setPenSize(size->value());
    this->close();
}

void sizeModule::cancelW()
{
    this->close();
}

void sizeModule::cleanW()
{
    zone->resetImage();
}
