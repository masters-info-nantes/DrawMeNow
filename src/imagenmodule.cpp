#include "imagenmodule.h"

imageNModule::imageNModule(int nb)
{
    setWindowTitle("See last x images");

    layout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout();

    lab = new QLabel("Choose the number of image you want to see : ");
    layout->addWidget(lab);

    number = new QSpinBox();
    number->setMaximum(20);
    number->setMinimum(1);
    number->setValue(nb);
    layout->addWidget(number);
    number->setAlignment(Qt::AlignVCenter);

    ok = new QPushButton("Ok");
    connect(ok, SIGNAL(clicked()), this, SLOT(validate()));
    buttonLayout->addWidget(ok);


    cancel = new QPushButton("Cancel");
    connect(cancel, SIGNAL(clicked()), this, SLOT(canceled()));
    buttonLayout->addWidget(cancel);


    layout->addLayout(buttonLayout);

    move(650,300);

}

void imageNModule::validate()
{
   emit numberIChanged(number->value());
    this->close();
}

void imageNModule::canceled()
{
   this->close();
}
