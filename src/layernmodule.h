#ifndef LAYERNMODULE_H
#define LAYERNMODULE_H

#include <QtWidgets>
#include <QObject>

class layerNModule : public QWidget
{
    Q_OBJECT

public:
    layerNModule(int defaultNumber);

    QVBoxLayout *layout;
    QHBoxLayout *buttonLayout;
    QLabel *lab;
    QSpinBox *number;
    QPushButton *ok;
    QPushButton *cancel;


    void setLayerNumber(int num);

public slots:
    void validate();
  //  void canceled();

signals:
    void numberLChanged(int);
  //  void numberLCancel();

};

#endif // LAYERNMODULE_H
