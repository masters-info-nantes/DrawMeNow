#ifndef ZONEPREVIEW_H
#define ZONEPREVIEW_H

#include <QtWidgets>
#include <QObject>

class zonePreview : public QWidget
{
    Q_OBJECT
public:
    zonePreview();

    QGridLayout *layout;

    QLabel *title;
    QPushButton *preview;
    QRadioButton *beginning;
    QCheckBox *withBg;
    QRadioButton *lastImg;

};

#endif // ZONEPREVIEW_H
