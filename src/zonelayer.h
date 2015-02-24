#ifndef ZONELAYER_H
#define ZONELAYER_H

#include <QtWidgets>
#include <QObject>
#include <vector>
using namespace std;

class zoneLayer : public QWidget
{
    Q_OBJECT
public:
    zoneLayer();

    QGridLayout *layout;
    vector<QLabel *> layers;

    QString desFolder;
    QString currentPath;
    QImage img;
    QPixmap pix;
    QLabel *lab;

    int layerNumber;
    int layerFrequency;
    int currentDesValue;

    void setLayerNumber(int number);
    void setLayerFrequency(int frequency);
    void setDesFolder(QString path);
    void setCurrentDessin( QString path, int value);
    void buildLayers();
    void clearLayout(QLayout *layout);

};

#endif // ZONELAYER_H
