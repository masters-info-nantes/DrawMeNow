#include "zonepreview.h"

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

    beginning = new QRadioButton("From Beginning",this);
    beginning->setCursor(Qt::PointingHandCursor);
    beginning->setStyleSheet("border-color: black; color : black;");
    layout->addWidget(beginning,0,1);

    lastImg = new QRadioButton("Last x Images",this);
    lastImg->setCursor(Qt::PointingHandCursor);
    lastImg->setStyleSheet("border-color: black; color : black;");
    layout->addWidget(lastImg,1,1);

  /*  QFrame *line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 0, 800, 3));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line,0,2,2,1);*/

    withBg = new QCheckBox("With Background",this);
    withBg->setTristate(false);
    withBg->setCursor(Qt::PointingHandCursor);
    withBg->setStyleSheet("border-color: black; color : black;");

    layout->addWidget(withBg,0,2,2,1);

    preview = new QPushButton("Preview");
    preview->setStyleSheet("border-color: black; color : black;");
    preview->setCursor(Qt::PointingHandCursor);
    layout->addWidget(preview,0,3,2,1);

    setLayout(layout);


}
