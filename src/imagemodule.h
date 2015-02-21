#ifndef IMAGEMODULE_H
#define IMAGEMODULE_H

#include <QtWidgets>
#include <QObject>
#include <QApplication>

class imageModule : public QWidget
{
    Q_OBJECT
public:
    imageModule(QString path, int index);

    QHBoxLayout *layout;

    QString path;
    int index;

    QLabel *image;
    QLabel *indexL;
    QImage img;
    QPixmap pix;
};

#endif // IMAGEMODULE_H
