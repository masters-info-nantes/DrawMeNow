#include "newproject.h"


newProject::newProject()
{
    setMinimumSize(735,250);

    layout = new QVBoxLayout(this);
     setLayout(layout);

    QFont f( "Arial", 25, QFont::Bold);

     labelChoose = new QLabel("Choose the video");
        labelChoose->setFont(f);
        labelChoose->setFixedSize(735,100);
        labelChoose->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
        layout->addWidget(labelChoose);

    layoutLoad = new QHBoxLayout;
    loadPath = new QLineEdit();
        loadPath->setFixedSize(200,25);
        loadPath->setReadOnly(true);
        layoutLoad->addWidget(loadPath,1,Qt::AlignTop|Qt::AlignRight);

    browseButton = new QPushButton("Browse");
        browseButton->setFixedSize(100,25);
        layoutLoad->addWidget(browseButton,1,Qt::AlignTop|Qt::AlignLeft);
        layoutLoad->setContentsMargins(130,11,11,11);
        layout->addLayout(layoutLoad);

        widgetFreq = new QVBoxLayout();


    labelChooseFreq = new QLabel("Choose video frequency");
        labelChooseFreq->setFont(f);
        labelChooseFreq->setFixedSize(735,100);
        labelChooseFreq->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        labelChooseFreq->hide();
        widgetFreq->addWidget(labelChooseFreq);

     buttonFreq = new QButtonGroup(widgetFreq);
     button6Freq = new QRadioButton("6 img/s");
     button8Freq = new QRadioButton("8 img/s");
     button12Freq = new QRadioButton("12 img/s");
     button24Freq = new QRadioButton("24 img/s");
       buttonFreq->addButton(button6Freq);
       buttonFreq->addButton(button8Freq);
       buttonFreq->addButton(button12Freq);
       buttonFreq->addButton(button24Freq);

       layout->addLayout(widgetFreq);

     layoutButton = new QHBoxLayout();

     returnButton = new QPushButton("Return");
        returnButton->setFixedSize(100,25);
        layoutButton->addWidget(returnButton,1,Qt::AlignLeft);
        layout->addLayout(layoutButton);

      validateButton = new QPushButton("Validate");
         validateButton->setFixedSize(100,25);


    QObject::connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    QObject::connect(returnButton, SIGNAL(clicked()), this, SLOT(goReturn()));
    QObject::connect(validateButton, SIGNAL(clicked()), this, SLOT(goMain()));

    //au milieu!
    QDesktopWidget *widget = QApplication::desktop();
    int desktop_width = widget->width();
    int desktop_height = widget->height();
    int x = desktop_width / 2 - width() / 2;
    int y = desktop_height / 2 - height() / 2 - 25;
    move(QPoint(x, y));

    show();
}

newProject::~newProject()
{
    delete layout;
}


void newProject::goReturn()
{
    welcome *w = new welcome();
    this->~newProject();
}

void newProject::goMain()
{
    bool selected = false;
    if(button6Freq->isChecked())
    {
        freq = 6;
        selected = true;
    }
    else if(button8Freq->isChecked())
    {
        freq = 8;
        selected = true;
    }
    else if(button12Freq->isChecked())
    {
        freq = 12;
        selected = true;
    }
    else if(button24Freq->isChecked())
    {
        freq = 24;
        selected = true;
    }

    if(selected)
    {
        saveLocation *save = new saveLocation();
            save->setVideoPath(loadPath->text());
            save->setFreq(freq);
        this->~newProject();
    }
    else
    {
         QMessageBox msgBox;
         msgBox.setText("Select a frequency");
         msgBox.exec();
    }
}



void newProject::browse()
{
     path = QFileDialog::getOpenFileName(this,
         tr("Load Video"), "/home");
        loadPath->setText(path);
     if(loadPath->text().size() > 0 )
     {
         labelChoose->hide();
         labelChooseFreq->show();
         widgetFreq->addWidget(button6Freq,1,Qt::AlignHCenter);
         widgetFreq->addWidget(button8Freq,1,Qt::AlignHCenter);
         widgetFreq->addWidget(button12Freq,1,Qt::AlignHCenter);
         widgetFreq->addWidget(button24Freq,1,Qt::AlignHCenter);
         layoutButton->addWidget(validateButton,1,Qt::AlignRight);
     }


}
