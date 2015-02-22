#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <zonedessin.h>
#include <zonepreview.h>
#include <fonddessin.h>
#include <zoneimage.h>
#include <QtWidgets>
#include <QObject>
#include <sizemodule.h>
#include <videomodule.h>

class sizeModule;

class MainWindow : public QMainWindow
{
        Q_OBJECT
public:
    MainWindow();

    //----mise en forme-------
    QHBoxLayout *mainLayout;
    QVBoxLayout *rLayout;
    QWidget *window; /*!< widget main window*/

    //-------toolbar----------
    QToolBar *toolBar;

    QCheckBox *backgButton;

    QToolButton *buttonColor;
    QToolButton *buttonPen;
    QToolButton *buttonRubber;
    QToolButton *buttonSize;
    QToolButton *buttonUndo;
    QToolButton *buttonRedo;

    //------barre de menu------
    //file
    QMenu *fileMenu;
    QMenu *fileOpen;
    QAction *openNew;
    QAction *openExisting;
    QAction *fileSave;
    QAction *fileSaveAs;
    QMenu *fileExportAs;
    QAction *exportMovie;
    QAction *exportImage;

    //frequency
    QMenu *frequencyMenu;
    QAction *frequency6;
    QAction *frequency8;
    QAction *frequency12;
    QAction *frequency24;

    QCheckBox *f6cb;
    QCheckBox *f8cb;
    QCheckBox *f12cb;
    QCheckBox *f24cb;


    //layer
    QMenu *layerMenu;
    QMenu *layerFrequency;
    QAction *layerF1;
    QAction *layerF2;
    QAction *layerF3;
    QMenu *layerNumber;
    QWidgetAction *layerN;
    QSpinBox *layer;

    //fond
    QMenu *bgMenu;
    QAction *bgChange;

    //--------contenu---------
    zoneDessin *zoneDes;
    zonePreview *zonePre;
    zoneImage * zoneIm;
    fondDessin *fond;
    sizeModule *chooseSize;

    QGridLayout *zoneTravail;
    QLabel *image;
    QImage img;
    QPixmap pix;

    videoModule *videoM;
    //-----donnees----------
    QString imgPath;
    QString videoPath;
    QString projectFolder;
    int layerFr;
    int layerNum;
    int fps;


    void setPenSize(int size);
    void setImage(QString path);
    void setVideo(QString path,QString folder,int framerate);
    void setFps(int fps);
    void setDessin(QString path);

    void valideFps(int fps);

public slots:

    void sauvegarder();
    void colorClick();
    void sizeClick();
    void undoClick();
    void redoClick();
    void rubberClick();
    void penClick();
    void imageChanged(QString path, QString desPath);

    void goTo6Fps();
    void goTo8Fps();
    void goTo12Fps();
    void goTo24Fps();

    void exportAs();
    void hideBackground(bool checked);
    void imgReady();
};

#endif // MAINWINDOW_H
