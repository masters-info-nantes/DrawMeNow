#include "mainwindow.h"
#include <QtWidgets>
#include <QAction>
#include <QApplication>

MainWindow::MainWindow()
{
    //utiliser avconv plutot que ffmpeg

    //--------------------style general-------------------------

    setMinimumSize(1050,720);
    setMaximumSize(1050,720);
    //icone et titre de la fenetre
    setWindowIcon(QIcon(":Icones/crayon.png"));
    setWindowTitle("Draw Me Now");

    //style de la fenetre
    QPalette palette;
    //QColor color(242,235,235);
   // QColor color(205,205,205);
    QColor color(Qt::black);
    palette.setBrush(this->backgroundRole(), QBrush(color));
   this->setPalette(palette);


    //-------------------Barre de Menu---------------------------

    menuBar()->setNativeMenuBar(false);

    //--------Actions-------------------------------


    //----menu file actions-----
    //open
    openNew = new QAction("New Project", this);
    openExisting = new QAction("Existing Project", this);

    //save
    fileSave = new QAction("Save", this);
    fileSaveAs = new QAction("Save As ...", this);


    //export
    exportMovie = new QAction("Movie", this);
    exportImage = new QAction("Image", this);
    connect(exportImage,SIGNAL(triggered(bool)),this,SLOT(exportAs()));

   //----menu frequency actions-----

    frequency6 = new QAction("6 fps", this);
    frequency6->setCheckable(true);
    connect(frequency6,SIGNAL(triggered(bool)),this,SLOT(goTo6Fps()));
    frequency8 = new QAction("8 fps", this);
    frequency8->setCheckable(true);
    connect(frequency8,SIGNAL(triggered(bool)),this,SLOT(goTo8Fps()));
    frequency12 = new QAction("12 fps", this);
    frequency12->setCheckable(true);
    connect(frequency12,SIGNAL(triggered(bool)),this,SLOT(goTo12Fps()));
    frequency24 = new QAction("24 fps", this);
    frequency24->setCheckable(true);
    connect(frequency24,SIGNAL(triggered(bool)),this,SLOT(goTo24Fps()));

    //----menu layer frequency actions-----
    layerF1 = new QAction("1/1", this);
    layerF1->setCheckable(true);
    layerF2 = new QAction("1/2", this);
    layerF2->setCheckable(true);
    layerF3 = new QAction("1/3", this);
    layerF3->setCheckable(true);


    //-------Menu File---------

    fileMenu = menuBar()->addMenu("&File");
    //open
    fileOpen = fileMenu->addMenu("Open");
    fileOpen->addAction(openNew);
    fileOpen->addAction(openExisting);
    fileMenu->addSeparator();
    //save
    fileMenu->addAction(fileSave);
    //save as
    fileMenu->addAction(fileSaveAs);
    fileMenu->addSeparator();
    //export as
    fileExportAs =  fileMenu->addMenu("Export As ...");
    fileExportAs->addAction(exportMovie);
    fileExportAs->addAction(exportImage);

    menuBar()->addSeparator();

    //-------Menu Frequency---------
    frequencyMenu = menuBar()->addMenu("Frequency");

    //pour que le menu reste ouvert on les connecte a son ouverture
    connect(frequency6,SIGNAL(triggered(bool)),frequencyMenu,SLOT(show()));
    connect(frequency8,SIGNAL(triggered(bool)),frequencyMenu,SLOT(show()));
    connect(frequency12,SIGNAL(triggered(bool)),frequencyMenu,SLOT(show()));
    connect(frequency24,SIGNAL(triggered(bool)),frequencyMenu,SLOT(show()));

    frequencyMenu->addAction(frequency6);
    frequencyMenu->addAction(frequency8);
    frequencyMenu->addAction(frequency12);
    frequencyMenu->addAction(frequency24);

    menuBar()->addSeparator();

    //-------Menu Layer---------
    layerMenu = menuBar()->addMenu("Layer");
    layerFrequency = layerMenu->addMenu("Layer Frequency");

    //pour que le menu reste ouvert on les connecte a son ouverture
    connect(layerF1,SIGNAL(triggered(bool)),layerMenu,SLOT(show()));
    connect(layerF1,SIGNAL(triggered(bool)),layerFrequency,SLOT(show()));
    connect(layerF2,SIGNAL(triggered(bool)),layerMenu,SLOT(show()));
    connect(layerF2,SIGNAL(triggered(bool)),layerFrequency,SLOT(show()));
    connect(layerF3,SIGNAL(triggered(bool)),layerMenu,SLOT(show()));
    connect(layerF3,SIGNAL(triggered(bool)),layerFrequency,SLOT(show()));

    layerFrequency->addAction(layerF1);
    layerFrequency->addAction(layerF2);
    layerFrequency->addAction(layerF3);
    layerNumber = layerMenu->addMenu("Layer Number");

    //le menu est une qspinbox
    layerN = new QWidgetAction(layerNumber);
    layer = new QSpinBox;
    layer->setMaximum(20);
    layer->setMinimum(0);
    layer->setValue(1);
    layerN->setDefaultWidget(layer);

    layerNumber->addAction(layerN);

    menuBar()->addSeparator();


    //-------------------gestion de la toolbar-------------------

    toolBar = addToolBar("Tools");
    toolBar->setMovable(false);
    toolBar->setStyleSheet("background-color:#DEDEDE;");

    //----show/hide bg button----------
    backgButton = new QCheckBox("Hide background",this);
    backgButton->setTristate(false);
    backgButton->setCursor(Qt::PointingHandCursor);
    connect(backgButton, SIGNAL(clicked(bool)), this, SLOT(hideBackground(bool)));

    //pour eviter que le focus soit sur la checkbox
    setFocus();

    //un label permet de mettre un espace dans la toolbar
    QLabel *lab = new QLabel("                      ");
    toolBar->addWidget(lab);

    toolBar->addWidget(backgButton);

    //espace
    QLabel *lab1 = new QLabel("                      ");
    toolBar->addWidget(lab1);

    toolBar->addSeparator();
    toolBar->addSeparator();

    //espace
    QLabel *lab2 = new QLabel("                      ");
    toolBar->addWidget(lab2);

    //------Gomme---------
    //termine voir aml apprence
    buttonRubber = new QToolButton();
    buttonRubber->setIcon(QIcon(":Icones/Gomme.png"));
    buttonRubber->setChecked(true);
    buttonRubber->setCursor(Qt::PointingHandCursor);
    toolBar->addWidget(buttonRubber);
    connect(buttonRubber, SIGNAL(clicked()), this, SLOT(rubberClick()));

    //espace
    QLabel *lab3 = new QLabel("               ");
    toolBar->addWidget(lab3);

    //------Crayon------------
    buttonPen = new QToolButton();
    buttonPen->setIcon(QIcon(":Icones/crayon.png"));
    buttonPen->setChecked(true);
    buttonPen->setCursor(Qt::PointingHandCursor);
    toolBar->addWidget(buttonPen);
    buttonPen->setStyleSheet(" border-style: inset;\
                             border-width: 2px;\
                             border-radius: 5px;\
                             border-color: black;");
    connect(buttonPen, SIGNAL(clicked()), this, SLOT(penClick()));


    //espace
    QLabel *lab4 = new QLabel("               ");
    toolBar->addWidget(lab4);

    //-------Color---------
    //termine
    buttonColor = new QToolButton();
    buttonColor->setCursor(Qt::PointingHandCursor);
    buttonColor->setStyleSheet("background-color : #000000; border-radius: 5px;");
    toolBar->addWidget(buttonColor);
    connect(buttonColor, SIGNAL(clicked()), this, SLOT(colorClick()));

    //espace
    QLabel *lab5 = new QLabel("               ");
    toolBar->addWidget(lab5);

    //--------size---------
    //termine
    buttonSize = new QToolButton();
    buttonSize->setCursor(Qt::PointingHandCursor);
    buttonSize->setIcon(QIcon(":Icones/size.png"));
    toolBar->addWidget(buttonSize);
    connect(buttonSize, SIGNAL(clicked()), this, SLOT(sizeClick()));
  /*  actionSize = new QAction("size", this);
    actionSize->setShortcut(QKeySequence("Ctrl++"));
    actionSize->setIcon(QIcon(":Icones/size.png"));
    toolBar->addAction(actionSize);
    connect(actionSize, SIGNAL(triggered()), this, SLOT(sizeClick()));*/

    //espace
    QLabel *lab6 = new QLabel("                      ");
    toolBar->addWidget(lab6);

    toolBar->addSeparator();
    toolBar->addSeparator();


    //espace
    QLabel *lab7 = new QLabel("                ");
    toolBar->addWidget(lab7);

    //------Undo---------
    //termine
    buttonUndo = new QToolButton();
    buttonUndo->setCursor(Qt::PointingHandCursor);
    buttonUndo->setIcon(QIcon(":Icones/undo.png"));
    buttonUndo->setShortcut(QKeySequence("Ctrl+Z"));
    toolBar->addWidget(buttonUndo);
    connect(buttonUndo, SIGNAL(clicked()), this, SLOT(undoClick()));

    //espace
    QLabel *lab8 = new QLabel("         ");
    toolBar->addWidget(lab8);

    //------Redo---------
    //termine
    buttonRedo = new QToolButton();
    buttonRedo->setCursor(Qt::PointingHandCursor);
    buttonRedo->setIcon(QIcon(":Icones/redo.png"));
    buttonRedo->setShortcut(QKeySequence("Ctrl+R"));
    toolBar->addWidget(buttonRedo);
    connect(buttonRedo, SIGNAL(clicked()), this, SLOT(redoClick()));


    //une ligne pour separer
    QFrame *line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 60, 1200, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    //-------------------contenu---------------------------------------------

    mainLayout = new QHBoxLayout();

    //---------------partie gauche----------------------------------

    zoneIm = new zoneImage("","",0);
   // zoneIm = new zoneImage("/home/muriel/workspace/Test/src/images",74);
    connect(zoneIm,SIGNAL(imageChange(QString,QString)),this,SLOT(imageChanged(QString,QString)));
    mainLayout->addWidget(zoneIm);

    //---------------partie droite-----------------------------------
    rLayout = new QVBoxLayout();

    image = new QLabel("test");

    //fond
    fond = new fondDessin();
    zoneDes = new zoneDessin("");
    zoneDes->activeSave(true);

    //image de fond
    //imgPath = QString(":Fond/capy.jpg");
    //setimage construit la zone de travail
    setImage(":Fond/blanc.png");
    imgPath = ":Fond/blanc.png";

    zoneTravail = new QGridLayout();
    zoneTravail->addWidget(fond,0,0);
    zoneTravail->addWidget(image,0,0);
    zoneTravail->addWidget(zoneDes,0,0);


    //pour rendre transparent
    zoneDes->setStyleSheet("background:transparent;");
    zoneDes->setAttribute(Qt::WA_TranslucentBackground);
    zoneDes->setWindowFlags(Qt::FramelessWindowHint);

    zonePre = new zonePreview();

    //rLayout->addWidget(zoneDes);
    rLayout->addLayout(zoneTravail);
    rLayout->addWidget(zonePre);


    mainLayout->addLayout(rLayout);


    //besoin d'un widget pour insérer le layout dans la fenetre
    window = new QWidget();
    window->setLayout(mainLayout);
    setCentralWidget(window);

    //au milieu!
    QDesktopWidget *widget = QApplication::desktop();
    int desktop_width = widget->width();
    int desktop_height = widget->height();
    int x = desktop_width / 2 - width() / 2;
    int y = desktop_height / 2 - height() / 2 - 25;
    move(QPoint(x, y));
    show();

}


void MainWindow::sauvegarder()
{
    //Choix du chemin d'enregistrement
  /*  QString texte = "RDV le " + dateedit->text() + " à " + timeedit->text() + "\na : " +lineEdit->text() +"\ndescription: " + textedit->toPlainText();
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer", QString(), "Tout");
    QFile sauvegarde(fichier);
    if (sauvegarde.open(QFile::WriteOnly))
       {
           QTextStream out(&sauvegarde);
           out << texte ;
       }*/
}

void MainWindow::colorClick()
{
     QColor couleur = QColorDialog::getColor(this->zoneDes->getPenColor(), this);
     zoneDes->setPenColor(couleur);
     QString style = "background-color : "+ couleur.name()+"; border-radius: 5px;";
     buttonColor->setStyleSheet(style);
}

void MainWindow::sizeClick()
{
    chooseSize = new sizeModule(this);
    chooseSize->setPenSize(zoneDes->getPenWidth());
    chooseSize->setPenColor(zoneDes->getPenColor());
    chooseSize->move(QPoint(750,200 ));
    chooseSize->show();
}

void MainWindow::setPenSize(int size)
{
    zoneDes->setPenWidth(size);
}

void MainWindow::undoClick()
{
    zoneDes->undo();
}

void MainWindow::redoClick()
{
    zoneDes->redo();
}

void MainWindow::rubberClick()
{
    zoneDes->setRubber(true);
    zoneDes->setCursor(Qt::ClosedHandCursor);
    buttonRubber->setStyleSheet(" border-style: inset;\
                                border-width: 2px;\
                                border-radius: 5px;\
                                border-color: black;");
    buttonPen->setStyleSheet(";");
}

void MainWindow::penClick()
{
    zoneDes->setRubber(false);
    zoneDes->setCursor(Qt::CrossCursor);
    buttonPen->setStyleSheet(" border-style: inset;\
                             border-width: 2px;\
                             border-radius: 5px;\
                             border-color: black;");
    buttonRubber->setStyleSheet(";");
}

//a ameliorer pour le suffixe
void MainWindow::exportAs()
{
    QFileDialog dialog(this);
   // dialog.setDefaultSuffix(".png");
    QString path = dialog.getSaveFileName(this, "Enregistrer", QString(), "Image Files (*.png *.jpg *.bmp)");
    QString completepath(path + ".png");
    zoneDes->saveImage(completepath);
}

void MainWindow::setImage(QString path)
{
    QString finalPath;
    if(path != ":Fond/blanc.png")
    {
        imgPath = path;
        finalPath = path;
    }
    if(backgButton->isChecked())
    {
        finalPath = ":Fond/blanc.png";
    }
    else
    {
        finalPath = path;
    }
    img = QImage(finalPath);
    pix = pix.fromImage(img.scaled(780,475,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    image->setPixmap(pix);
}

//cache l'image de fond ou la remet
void MainWindow::hideBackground(bool checked)
{
    if(checked)
    {
        setImage(":Fond/blanc.png");
    }
    else
    {
        setImage(imgPath);
    }
    setFocus();
}


void MainWindow::setVideo(QString path,QString folder,int framerate)
{
    videoPath = path;
    fps = framerate;
    projectFolder = folder;

    videoM = new videoModule(videoPath,fps);
    connect(videoM,SIGNAL(firstImageReady()),this,SLOT(imgReady()));

    //decomposition de la video avec un message d'attente et un changement de curseur
    setCursor(Qt::WaitCursor);

    videoM->buildFrame(folder);
    setCursor(Qt::ArrowCursor);

    //on attendras le signal pour changer l'image de fond
    valideFps(framerate);
}

void MainWindow::setFps(int fps)
{
   setVideo(videoPath,projectFolder,fps);
}

void MainWindow::imageChanged(QString path , QString desPath)
{
    setImage(path);
    setDessin(desPath);
}

//degueulasse mais bon...
void MainWindow::valideFps(int fps)
{
    if(fps == 6)
    {
        frequency6->setChecked(true);
        frequency8->setChecked(false);
        frequency12->setChecked(false);
        frequency24->setChecked(false);

    }else if(fps == 8)
    {
        frequency6->setChecked(false);
        frequency8->setChecked(true);
        frequency12->setChecked(false);
        frequency24->setChecked(false);

    }else if(fps == 12)
    {
        frequency6->setChecked(false);
        frequency8->setChecked(false);
        frequency12->setChecked(true);
        frequency24->setChecked(false);

    }else if(fps == 24)
    {
        frequency6->setChecked(false);
        frequency8->setChecked(false);
        frequency12->setChecked(false);
        frequency24->setChecked(true);
    }
}

void MainWindow::goTo6Fps()
{
    setFps(6);
}

void MainWindow::goTo8Fps()
{
    setFps(8);
}

void MainWindow::goTo12Fps()
{
    setFps(12);
}

void MainWindow::goTo24Fps()
{
    setFps(24);

}

void MainWindow::imgReady()
{
    setImage(videoM->getCurrentImg());
    //on change les images de cote
    //QMessageBox::information(this, "Draw Me Now", QString::number(videoM->frameNumber()));
    zoneIm->setParam(videoM->getImgFolder(),videoM->getDesFolder(),videoM->frameNumber());
    zoneDes->loadImage(videoM->getCurrentDes());
    //zoneDes->setImgPath(videoM->getCurrentDes());
}

void MainWindow::setDessin(QString path)
{
    zoneDes->loadImage(path);
    zoneDes->setStyleSheet("background:transparent;");
    zoneDes->setAttribute(Qt::WA_TranslucentBackground);
    zoneDes->setWindowFlags(Qt::FramelessWindowHint);
    zoneDes->update();
}
