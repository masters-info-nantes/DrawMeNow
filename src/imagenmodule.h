#ifndef IMAGENMODULE_H
#define IMAGENMODULE_H

#include <QtWidgets>
#include <QObject>

class imageNModule : public QWidget
{
    Q_OBJECT
public:

    imageNModule(int nb);

    QVBoxLayout *layout;
    QHBoxLayout *buttonLayout;
    QLabel *lab;
    QSpinBox *number;
    QPushButton *ok;
    QPushButton *cancel;

public slots:
    void validate();
    void canceled();

signals:
    void numberIChanged(int);
    void numberICancel();
};

#endif // IMAGENMODULE_H
