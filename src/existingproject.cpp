#include "existingproject.h"

existingProject::existingProject()
{
    setFixedSize(735,250);
    setWindowIcon(QIcon(":Icones/crayon.png"));
    setWindowTitle("Project Location");

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":Fond/saveloc.png")));
    this->setPalette(palette);

    layout = new QVBoxLayout(this);
     setLayout(layout);

    QFont f( "Arial", 25, QFont::Bold);
    QFont f2( "Arial", 10, QFont::Bold);

    //On cherche le fichier .dat contenant les informations du projet existant

     labelChoose = new QLabel("Choose an existing project");
        labelChoose->setFont(f);
        labelChoose->setFixedSize(735,100);
        labelChoose->setStyleSheet(" color : black;");
        labelChoose->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
        layout->addWidget(labelChoose);

    layoutLoad = new QHBoxLayout;
    loadPath = new QLineEdit();
        loadPath->setFixedSize(200,25);
        loadPath->setReadOnly(true);
        layoutLoad->addWidget(loadPath,1,Qt::AlignTop|Qt::AlignRight);

    browseButton = new QPushButton("Browse");
        browseButton->setFixedSize(100,25);
        browseButton->setStyleSheet(" color : black;");
        browseButton->setCursor(Qt::PointingHandCursor);
        layoutLoad->addWidget(browseButton,1,Qt::AlignTop|Qt::AlignLeft);
        layoutLoad->setContentsMargins(130,11,11,11);
        layout->addLayout(layoutLoad);


        //Informations relatives au projet

     widgetFreq = new QVBoxLayout();
     labelVideo = new QLabel();
        labelVideo->setFont(f2);
        labelVideo->setIndent(225);
        labelVideo->setStyleSheet(" color : black; font : bold 12pt;");
     labelFreq = new QLabel();
        labelFreq->setFont(f2);
        labelFreq->setIndent(225);
        labelFreq->setStyleSheet(" color : black; font : bold 12pt;");
     labelLayers = new QLabel();
        labelLayers->setFont(f2);
        labelLayers->setIndent(225);
        labelLayers->setStyleSheet(" color : black; font : bold 12pt;");
     labelLayersFreq = new QLabel();
        labelLayersFreq->setFont(f2);
        labelLayersFreq->setIndent(225);
        labelLayersFreq->setStyleSheet(" color : black; font : bold 12pt;");

       layout->addLayout(widgetFreq);

     layoutButton = new QHBoxLayout();

     returnButton = new QPushButton("Return");
        returnButton->setFixedSize(100,25);
        returnButton->setStyleSheet(" color : black;");
        returnButton->setCursor(Qt::PointingHandCursor);
        layoutButton->addWidget(returnButton,1,Qt::AlignLeft);
        layout->addLayout(layoutButton);

      validateButton = new QPushButton("Validate");
         validateButton->setFixedSize(100,25);
         validateButton->setCursor(Qt::PointingHandCursor);
         validateButton->setStyleSheet(" color : black;");


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


existingProject::~existingProject()
{
    delete layout;
}


void existingProject::goReturn()
{
    welcome *w = new welcome();
    w->show();
    this->~existingProject();
}

void existingProject::goMain()
{
    MainWindow *w = new MainWindow();
    QString projectFolder;
    for(int i = 0; i < desFolder.lastIndexOf("/")  ;i++)
    {
        projectFolder += desFolder.at(i);
    }
   // QMessageBox::information(this, "Draw Me Now", projectFolder);
    w->setVideo(videoPath,projectFolder,freq,false);
    w->setLayerFrequency(layersFreq);
    w->setLayerNumber(layers);
    this->~existingProject();

}


void existingProject::browse()
{
    setFocus();
     path = QFileDialog::getOpenFileName(this,
         tr("Load your project"), "/home",tr("*.dat"));
        loadPath->setText(path);

     if(loadPath->text().size() > 0 )
     {
          QFile file(path);
          file.open(QIODevice::ReadOnly);
          QDataStream in(&file);    // read the data serialized from the file
          QString videoName;
          in >> desFolder >> imgFolder >> videoPath >> freq >> layers >> layersFreq;


          for(int i = videoPath.lastIndexOf("/")+1 ; i< videoPath.size();i++)
          {
              videoName += videoPath.at(i);
          }
         labelChoose->hide();
         labelVideo->setText("Video Name : " + videoName);
         labelFreq->setText("Frequency : " + QString::number(freq) +" fps");
         labelLayers->setText("Layers : " + QString::number(layers -1));
         labelLayersFreq->setText("Layer Frequency : 1/" + QString::number(layersFreq));
         widgetFreq->addWidget(labelVideo);
         widgetFreq->addWidget(labelFreq);
         widgetFreq->addWidget(labelLayers);
         widgetFreq->addWidget(labelLayersFreq);
         layoutLoad->addWidget(loadPath,1,Qt::AlignVCenter|Qt::AlignRight);
         layoutLoad->addWidget(browseButton,1,Qt::AlignVCenter|Qt::AlignLeft);
         layoutButton->addWidget(validateButton,1,Qt::AlignRight);
     }


}

