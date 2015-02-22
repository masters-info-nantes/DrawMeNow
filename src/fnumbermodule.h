#ifndef FNUMBERMODULE_H
#define FNUMBERMODULE_H

#include <QtWidgets>
#include <QObject>
#include <QApplication>

class fnumberModule : public QWidget
{
    Q_OBJECT
public:
    fnumberModule(int max);

    QVBoxLayout *layout;
    QHBoxLayout *choice;

    QLabel *lab;
    QSpinBox *box;
    QPushButton *go;

    void setValue(int value);

public slots:
    void valideValue();

signals:
     void valueChange(int value);
};

#endif // FNUMBERMODULE_H
