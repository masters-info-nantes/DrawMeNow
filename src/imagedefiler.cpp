#include "imagedefiler.h"

imageDefiler::imageDefiler()
{

    layout = new QVBoxLayout();

    firstIM = new imageModule("/home/muriel/workspace/Exercice1/capy.jpg",1);
    layout->addWidget(firstIM);

    secondIM = new imageModule("/home/muriel/workspace/Exercice1/capy.jpg",2);
    layout->addWidget(secondIM);


    thirdIM = new imageModule("/home/muriel/workspace/Exercice1/capy.jpg",3);
    layout->addWidget(thirdIM);

    test1 = new imageModule("/home/muriel/workspace/Exercice1/capy.jpg",3);
    layout->addWidget(test1);
    test2 = new imageModule("/home/muriel/workspace/Exercice1/capy.jpg",3);
    layout->addWidget(test2);

    layout->setAlignment(Qt::AlignVCenter);
    setLayout(layout);

}
