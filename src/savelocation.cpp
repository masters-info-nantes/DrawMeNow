#include "savelocation.h"

saveLocation::saveLocation()
{
    setMinimumSize(735,250);

    layout = new QVBoxLayout(this);
     setLayout(layout);

    QFont f( "Arial", 25, QFont::Bold);

     labelChoose = new QLabel("Choose your working directory");
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

saveLocation::~saveLocation()
{
    delete layout;
}

void saveLocation::goMain()
{
    if(loadPath->text().size() > 0)
    {
         MainWindow *window = new MainWindow;
            window->setVideo(videoPath,loadPath->text(),freq);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("You have to select a directory");
        msgBox.exec();
    }
}
void saveLocation::goReturn()
{
    newProject *w = new newProject();
    this->~saveLocation();
}

void saveLocation::setVideoPath(QString path)
{
    videoPath = path;
}

void saveLocation::setFreq(int f)
{
    freq = f;
}

void saveLocation::browse()
{
     savePath = QFileDialog::getOpenFileName(this,
         tr("Choose directory"), "/home");
        loadPath->setText(savePath);
        if(loadPath->text().size() > 0)
        {
            layoutButton->addWidget(validateButton);
        }

}
