#ifndef FNUMBERMODULE_H
#define FNUMBERMODULE_H

#include <QtWidgets>
#include <QObject>
#include <QApplication>

class fnumberModule : public QWidget
{
    Q_OBJECT
public:
    fnumberModule();

    QVBoxLayout *layout;
    QHBoxLayout *choice;

    QLabel *lab;
    QSpinBox *box;
    QPushButton *go;
};

#endif // FNUMBERMODULE_H
