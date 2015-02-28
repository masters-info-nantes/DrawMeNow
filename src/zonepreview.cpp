#include "zonepreview.h"
#include "previewmodule.h"
#include <QAction>
#include <QApplication>
#include "imagenmodule.h"

zonePreview::zonePreview()
{
    setFixedSize(780,159);
   // setPalette(QPalette(QColor(0, 0, 0)));
    setPalette(QPalette(QColor(99, 99, 99)));
    setAutoFillBackground(true);

    layout = new QGridLayout();

    title = new QLabel("Preview :");
    title->setStyleSheet("font: 18pt; color : white");
    layout->addWidget(title,0,0,2,1);
    QSizePolicy spInfo(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo.setHorizontalStretch(1);
    title->setSizePolicy(spInfo);

    beginning = new QRadioButton("From Beginning",this);
    beginning->setCursor(Qt::PointingHandCursor);
    beginning->setStyleSheet("border-color: black; color : black; font: 13pt; ");
    layout->addWidget(beginning,0,1);
    QSizePolicy spInfo2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo2.setHorizontalStretch(2);
    beginning->setSizePolicy(spInfo2);
    connect(beginning,SIGNAL(clicked()),this,SLOT(click()));

    //par default on part du debut
    beginning->setChecked(true);
    setFocus();

    lastImg = new QRadioButton("Last x Images",this);
    lastImg->setCursor(Qt::PointingHandCursor);
    lastImg->setStyleSheet("border-color: black; color : black; font: 13pt; ");
    layout->addWidget(lastImg,1,1);
    QSizePolicy spInfo3(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo3.setHorizontalStretch(2);
    lastImg->setSizePolicy(spInfo3);
    connect(lastImg,SIGNAL(clicked()),this,SLOT(clickLI()));

  /*  QFrame *line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 0, 800, 3));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line,0,2,2,1);*/

    withBg = new QCheckBox("With Background",this);
    withBg->setTristate(false);
    withBg->setCursor(Qt::PointingHandCursor);
    withBg->setStyleSheet("border-color: black; color : black;  font: 13pt; ");
    QSizePolicy spInfo4(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo4.setHorizontalStretch(2);
    withBg->setSizePolicy(spInfo4);
    connect(withBg,SIGNAL(clicked()),this,SLOT(click()));

    //par default avec bg
    withBg->setChecked(true);
    setFocus();

    layout->addWidget(withBg,0,2,2,1);

    preview = new QPushButton("Preview");
    preview->setToolTip("click here to see the video you are creating");
    connect(preview,SIGNAL(clicked()),this,SLOT(go()));
    connect(preview,SIGNAL(clicked()),this,SLOT(click()));
    //style
    //    preview->setStyleSheet("border-color: black; color : black; font: bold 15pt; border-style :outset; border-radius : 3px;border-width: 3px; background-color: white");

    preview->setStyleSheet("border-color: black; color : black; font: bold 15pt; ");
    preview->setCursor(Qt::PointingHandCursor);
    layout->addWidget(preview,0,3,2,1);
    QSizePolicy spInfo5(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spInfo5.setHorizontalStretch(2);
    preview->setSizePolicy(spInfo5);
    preview->setMaximumSize(150,100);

    currentDes = "";
    imgFolder= "";
    desFolder = "";
    desValue = 0;
    nbLI = 1;

    setLayout(layout);
}

void zonePreview::setFps(int fps)
{
     this->fps = fps;
}

void zonePreview::setImg(QString desFolder, QString imgFolder,QString current, int value)
{
    currentDes = current;
    this->imgFolder= imgFolder;
    this->desFolder = desFolder;
    desValue = value;
}

void zonePreview::go()
{
   // QMessageBox::information(this,"test", "des : " + currentDes + " fold : " + imgFolder + " fold2 : "+ desFolder);
    if((currentDes !="")&& (imgFolder != "") && (desFolder != ""))
    {
        previewModule *preview = new previewModule(desFolder,imgFolder,currentDes,desValue);
        preview->setBeginning(beginning->isChecked());
        preview->setHideBg(!(withBg->isChecked()));
        preview->setNbImg(nbLI);
        preview->setFps(fps);
        preview->show();
    }
}

void zonePreview::click()
{
    setFocus();
}

void zonePreview::clickLI()
{
    //ouvrir une fenetre pour obtenir le numero dans la var nbLI;
    img = new imageNModule(nbLI);
    connect(img,SIGNAL(numberIChanged(int)),this,SLOT(nbImgChange(int)));
    img->show();
    //setFocus();
}

void zonePreview::nbImgChange(int number)
{
    nbLI = number;
    lastImg->setText("Last " + QString::number(nbLI) + " images");
    setFocus();
}
