#ifndef IMAGEDEFILER_H
#define IMAGEDEFILER_H

#include <QtWidgets>
#include <QObject>
#include <QApplication>
#include <imagemodule.h>

class imageDefiler : public QWidget
{
    Q_OBJECT
public:
    imageDefiler();

    QVBoxLayout *layout;
    imageModule *firstIM;
    imageModule *secondIM;
    imageModule *thirdIM;
    imageModule *test1;
    imageModule *test2;
};

#endif // IMAGEDEFILER_H
