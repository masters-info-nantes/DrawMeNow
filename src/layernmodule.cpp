#include "layernmodule.h"

layerNModule::layerNModule(int defaultNumber)
{
     setWindowTitle("Choose the Number of Layer");

     layout = new QVBoxLayout(this);
  //   buttonLayout = new QHBoxLayout();

     lab = new QLabel("Choose the Number of Layer :");
     layout->addWidget(lab);

     number = new QSpinBox();
     number->setMaximum(20);
     number->setMinimum(0);
     number->setValue(defaultNumber);
     layout->addWidget(number);
     number->setAlignment(Qt::AlignVCenter);

     ok = new QPushButton("Ok");
     connect(ok, SIGNAL(clicked()), this, SLOT(validate()));
   //  buttonLayout->addWidget(ok);


   /*  cancel = new QPushButton("Cancel");
     connect(cancel, SIGNAL(clicked()), this, SLOT(canceled()));
     buttonLayout->addWidget(cancel);*/


   //  layout->addLayout(buttonLayout);
     layout->addWidget(ok);

}

void layerNModule::validate()
{
    emit numberLChanged(number->value() +1);
}

void layerNModule::setLayerNumber(int num)
{
    number->setValue(num);
}

/*
void layerNModule::canceled()
{
    emit numberLCancel();
}
*/
