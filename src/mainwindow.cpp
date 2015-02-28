#include "mainwindow.h"
#include <QtWidgets>
#include <QAction>
#include <QApplication>
#include <newproject.h>
#include <existingproject.h>

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

    connect(openNew,SIGNAL(triggered(bool)),this,SLOT(openNewProject()));
    connect(openExisting,SIGNAL(triggered(bool)),this,SLOT(openExistingProject()));


    //save
    fileSave = new QAction("&Save", this);
    fileSave->setShortcutContext(Qt::WindowShortcut);
    fileSave->setShortcut(Qt::CTRL+Qt::Key_S);
    fileSaveAs = new QAction("Save As ...", this);
    connect(fileSave,SIGNAL(triggered(bool)),this,SLOT(save()));
    connect(fileSaveAs,SIGNAL(triggered(bool)),this,SLOT(saveAs()));

    //export
    exportMovie = new QAction("Movie", this);
    connect(exportMovie,SIGNAL(triggered(bool)),this,SLOT(exportAsMovie()));
    exportImage = new QAction("Images", this);
    connect(exportImage,SIGNAL(triggered(bool)),this,SLOT(exportAsImages()));

    //quitter
    quit = new QAction("&Quit",this);
    quit->setShortcutContext(Qt::WindowShortcut);
    quit->setShortcut(Qt::CTRL+Qt::Key_Q);
    connect(quit,SIGNAL(triggered(bool)),this,SLOT(quitter()));

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
    layerF1->setChecked(true);
    connect(layerF1,SIGNAL(triggered(bool)),this,SLOT(goTo1LF()));
    layerF2 = new QAction("1/2", this);
    layerF2->setCheckable(true);
    connect(layerF2,SIGNAL(triggered(bool)),this,SLOT(goTo2LF()));
    layerF3 = new QAction("1/3", this);
    layerF3->setCheckable(true);
    connect(layerF3,SIGNAL(triggered(bool)),this,SLOT(goTo3LF()));

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

    //quit
    fileMenu->addAction(quit);

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
    layerFr = 1;
    layerNum = 0;
    //layerNum = 4;

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
 /*   layer = new QSpinBox;
    layer->setMaximum(20);
    layer->setMinimum(0);
    layer->setValue(layerNum);*/
    layer = new layerNModule(layerNum);
    connect(layer, SIGNAL(numberLChanged(int)), this, SLOT(setLayerN(int)));
  //  connect(layer, SIGNAL(numberLCancel()), this, SLOT(closeNumberL()));
    layerN->setDefaultWidget(layer);
 //   connect(layer,SIGNAL(valueChanged(int)),this,SLOT(setLayerNumber(int)));

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
    backgButton->setToolTip("Hide the image you are drawing on");
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
    buttonRubber->setToolTip("Eraser");
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
    buttonPen->setToolTip("Pen");
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
    buttonColor->setToolTip("change the color of the pen");
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
    buttonSize->setToolTip("change the size of the pen or eraser");
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
    QLabel *lab7 = new QLabel("                    ");
    toolBar->addWidget(lab7);

    //------Undo---------
    //termine
    buttonUndo = new QToolButton();
    buttonUndo->setCursor(Qt::PointingHandCursor);
    buttonUndo->setIcon(QIcon(":Icones/undo.png"));
    buttonUndo->setShortcut(QKeySequence("Ctrl+Z"));
    buttonUndo->setToolTip("cancels the previous action");
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
    buttonRedo->setToolTip("replay last canceled action");
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
    connect(zoneIm,SIGNAL(imageChange(QString,QString,int)),this,SLOT(imageChanged(QString,QString,int)));
    mainLayout->addWidget(zoneIm);

    //---------------partie droite-----------------------------------
    rLayout = new QVBoxLayout();

    image = new QLabel("test");

    //fond
    fond = new fondDessin();
    zoneDes = new zoneDessin("");
    zoneDes->activeSave(true);

    //layers
    zoneLay = new zoneLayer();
    zoneLay->setStyleSheet("background:transparent;");
    zoneLay->setAttribute(Qt::WA_TranslucentBackground);
  //  zoneDes->setWindowFlags(Qt::FramelessWindowHint);

    //image de fond
    //imgPath = QString(":Fond/capy.jpg");
    //setimage construit la zone de travail
    setImage(":Fond/blanc.png");
    imgPath = ":Fond/blanc.png";

    zoneTravail = new QGridLayout();
    zoneTravail->addWidget(fond,0,0);
    zoneTravail->addWidget(image,0,0);
    zoneTravail->addWidget(zoneLay,0,0);
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


void MainWindow::exportAsImages()
{
    QFileDialog dialog(this);
   // dialog.setDefaultSuffix(".png");
    QString path = dialog.getExistingDirectory(this, "Choose a Directory to Export Images", QString());
  //  QString completepath(path + ".png");
  //  zoneDes->saveImage(completepath);

    if(path != "")
    {
        QDir dir(path);
        dir.mkpath(path);

        for(int i =1; i <=videoM->frameNumber();i++)
        {
            QImage *img;
            img = new QImage(QString(videoM->getDesFolder() + "/dessin" + QString::number(i) + ".png"));
            img->save(QString(path + "/dessin" + QString::number(i) + ".png"));
        }
        QMessageBox::information(this,"Saved","Images Exported!");
    }
}

void MainWindow::exportAsMovie()
{
    QFileDialog dialog(this);
    QString path = dialog.getSaveFileName(this, "Choose a Directory to Export Images", QString());
    if(path != "")
    {
        videoM->createVideo(path,fps);
        connect(videoM,SIGNAL(videoIsReady()),this,SLOT(videoDone()));
    }
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

   /* QPixmap result(pix.size());
    result.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&result);
    double opa = 0.7;
    painter.setOpacity(opa);
    painter.drawPixmap(0, 0, pix);
    painter.end();
    image->setPixmap(result);*/
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


void MainWindow::setVideo(QString path,QString folder,int framerate, bool newM)
{
    videoPath = path;
    fps = framerate;
    projectFolder = folder;

    videoM = new videoModule(videoPath,fps);
    connect(videoM,SIGNAL(firstImageReady()),this,SLOT(imgReady()));

    //decomposition de la video avec un message d'attente et un changement de curseur
    setCursor(Qt::WaitCursor);

    videoM->buildFrame(folder,newM);
    setCursor(Qt::ArrowCursor);

    //on attendras le signal pour changer l'image de fond
    valideFps(framerate);
    zonePre->setFps(fps);
}

void MainWindow::setFps(int fps)
{
   // QMessageBox::information(this,"test","coucou");
    QDir dir(videoM->getImgFolder());
    dir.removeRecursively();


    QDir dir2(videoM->getDesFolder());
    dir2.removeRecursively();

    setVideo(videoPath,projectFolder,fps,true);
}

void MainWindow::imageChanged(QString path , QString desPath, int value)
{
    setImage(path);
    setDessin(desPath,value);
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
//ca aussi
void MainWindow::valideLayerF(int frequency)
{
    if(frequency == 1)
    {
        layerF1->setChecked(true);
        layerF2->setChecked(false);
        layerF3->setChecked(false);

    }else if(frequency == 2)
    {
        layerF1->setChecked(false);
        layerF2->setChecked(true);
        layerF3->setChecked(false);

    }else if(frequency == 3)
    {
        layerF1->setChecked(false);
        layerF2->setChecked(false);
        layerF3->setChecked(true);
    }
}

void MainWindow::goTo6Fps()
{
    QMessageBox msgBox;
    msgBox.setText("You're about to change the fps,it will erase your project");
    msgBox.setInformativeText("Do you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Yes:
                setFps(6);
           break;
       case QMessageBox::Cancel:
            frequency6->setChecked(false);

           break;
       default:
           // should never be reached
           break;
     }

}

void MainWindow::goTo8Fps()
{
    QMessageBox msgBox;
    msgBox.setText("You're about to change the fps,it will erase your project");
    msgBox.setInformativeText("Do you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Yes:
                setFps(8);
           break;
       case QMessageBox::Cancel:
            frequency8->setChecked(false);

           break;
       default:
           // should never be reached
           break;
     }
}

void MainWindow::goTo12Fps()
{
    QMessageBox msgBox;
    msgBox.setText("You're about to change the fps,it will create erase your project");
    msgBox.setInformativeText("Do you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Yes:
                setFps(12);
           break;
       case QMessageBox::Cancel:
            frequency12->setChecked(false);

           break;
       default:
           // should never be reached
           break;
     }
}

void MainWindow::goTo24Fps()
{
    QMessageBox msgBox;
    msgBox.setText("You're about to change the fps,it will erase your project");
    msgBox.setInformativeText("Do you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Yes:
                setFps(24);
           break;
       case QMessageBox::Cancel:
            frequency24->setChecked(false);
           break;
       default:
           // should never be reached
           break;
     }
}

void MainWindow::goTo1LF()
{
    setLayerFrequency(1);
    valideLayerF(1);
}

void MainWindow::goTo2LF()
{
    setLayerFrequency(2);
    valideLayerF(2);
}

void MainWindow::goTo3LF()
{
    setLayerFrequency(3);
    valideLayerF(3);
}

//slot
void MainWindow::setLayerN(int number)
{
    setLayerNumber(number);
    closeNumberL();
}

//normal
void MainWindow::setLayerNumber(int number)
{
   // QMessageBox::information(this, "Draw Me Now", "number of layer change to  : " + QString::number(number));
    layerNum = number;
    layer->setLayerNumber(number-1);
    zoneLay->setLayerNumber(number);
    update();
}

void MainWindow::setLayerFrequency(int frequency)
{
  // QMessageBox::information(this, "Draw Me Now", "frequency change to:" + QString::number(frequency));
    layerFr = frequency;
    zoneLay->setLayerFrequency(frequency);
    update();
}

void MainWindow::imgReady()
{

    setImage(videoM->getCurrentImg());
    //on change les images de cote
    //QMessageBox::information(this, "Draw Me Now", QString::number(videoM->frameNumber()));
    zoneIm->setParam(videoM->getImgFolder(),videoM->getDesFolder(),videoM->frameNumber());
    zoneDes->loadImage(videoM->getCurrentDes());
    //zoneDes->setImgPath(videoM->getCurrentDes());
    createLayers(videoM->getCurrentDes(),1);
    zonePre->setImg(videoM->getDesFolder(),videoM->getImgFolder(),videoM->getCurrentDes(),1);
}

void MainWindow::setDessin(QString path, int value)
{
    zoneDes->loadImage(path);
    zoneDes->setStyleSheet("background:transparent;");
    zoneDes->setAttribute(Qt::WA_TranslucentBackground);
    zoneDes->setWindowFlags(Qt::FramelessWindowHint);
    zoneDes->update();
    createLayers(path,value);
    zonePre->setImg(videoM->getDesFolder(),videoM->getImgFolder(),path,value);
}

void MainWindow::closeNumberL()
{
    layerNumber->close();
    layerMenu->close();
}

void MainWindow::createLayers(QString desPath, int desValue)
{
  //  QMessageBox::information(this,"test", "dessin");
    zoneLay->setDesFolder(videoM->getDesFolder());
    zoneLay->setLayerFrequency(layerFr);
    zoneLay->setLayerNumber(layerNum );
    zoneLay->setCurrentDessin(desPath,desValue);
}

void MainWindow::videoDone()
{
    QMessageBox::information(this,"Video Export", "Video Exported!");
    QDir dir = QDir(videoM->getDesFolder() + "/DessinTemp");
    dir.removeRecursively();
}

void MainWindow::save()
{
     QString fileName;
     for(int i = projectFolder.lastIndexOf("/")+1;i<projectFolder.size();i++)
     {
         fileName += projectFolder.at(i);
     }
     QFile file(projectFolder+"/"+ fileName+".dat");
     file.open(QIODevice::WriteOnly);
     QDataStream out(&file);
     out << QString(videoM->desFolder);
     out << QString(videoM->imgFolder);
     out << QString(videoPath);
     out << (qint32)fps;
     out << (qint32)(layerNum);
     out << (qint32)layerFr;

     QMessageBox::information(this,"Save","Project saved!");

}

void MainWindow::saveAs()
{
        QString savePath = QFileDialog::getExistingDirectory(this,
        tr("Choose directory"), "/home");
        QString fileName;
        for(int i = savePath.lastIndexOf("/")+1;i<savePath.size();i++)
        {
            fileName += savePath.at(i);
        }
       if(savePath.size() > 0)
       {
           QFile file(savePath+"/"+ fileName+".dat");
           file.open(QIODevice::WriteOnly);
           QDataStream out(&file);
           out << QString(videoM->desFolder);
           out << QString(videoM->imgFolder);
           out << QString(videoPath);
           out << (qint32)fps;
           out << (qint32)layerNum;
           out << (qint32)layerFr;
       }

       QMessageBox::information(this,"Save As...","Project saved!");
}

void MainWindow::openNewProject()
{
    newProject *newPro = new newProject();
    this->close();
}

void MainWindow::openExistingProject()
{
    existingProject *exPro = new existingProject();
    this->close();
}

void MainWindow::quitter()
{
    QMessageBox msgBox;
    msgBox.setText("You're about to quit the application");
    msgBox.setInformativeText("Do you want to save your project?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Save:
           save();
           qApp->quit();
           break;
       case QMessageBox::Discard:
           qApp->quit();
           break;
       case QMessageBox::Cancel:

           break;
       default:
           // should never be reached
           break;
     }
}
