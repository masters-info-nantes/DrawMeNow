#include "welcome.h"


welcome::welcome()
{

        setWindowIcon(QIcon(":Icones/crayon.png"));
        setWindowTitle("Draw Me Now");

        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(QImage(":Fond/welcome.png").scaled(735,492,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        this->setPalette(palette);

        setFixedSize(735,492);

        QFont f( "Arial", 50, QFont::Bold);

        layout = new QVBoxLayout(this);
        setLayout(layout);

        //Titre de l'application

        labelWelcome = new QLabel();
            labelWelcome->setText("Welcome to");
            labelWelcome->setFixedSize(735,120);
            labelWelcome->setStyleSheet(" color : black;");
            labelWelcome->setFont(f);
            labelWelcome->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
            layout->addWidget(labelWelcome);

       labelTitle = new QLabel();
            labelTitle->setText("Draw Me Now !");
            labelTitle->setFixedSize(735,120);
            labelTitle->setStyleSheet(" color : black;");
            labelTitle->setFont(f);
            labelTitle->setAlignment(Qt::AlignCenter);
            layout->addWidget(labelTitle);


          //Boutons pour creer/ouvrir un projet

        buttonLayout = new QHBoxLayout();
            layout->addLayout(buttonLayout);

        leftButton = new QVBoxLayout();
        rightButton = new QVBoxLayout();
            leftButton->setAlignment(Qt::AlignCenter);
            rightButton->setAlignment(Qt::AlignCenter);
            buttonLayout->addLayout(leftButton);
            buttonLayout->addLayout(rightButton);

        buttonNewProject = new QPushButton("New Project");
        buttonOpenExisting= new QPushButton("Existing Project");
            buttonNewProject->setFixedSize(220,80);

            buttonNewProject->setStyleSheet(" QPushButton{background-color:#D4D4D4;color : black; font: bold 17pt;border-style :outset; border-width: 3px;border-radius: 8px;\
                                                border-color : black; padding: 6px;}");
            buttonNewProject->setToolTip("Create a new project");
            buttonNewProject->setCursor(Qt::PointingHandCursor);

            buttonOpenExisting->setFixedSize(220,80);
            buttonOpenExisting->setToolTip("Open an existing project");
            buttonOpenExisting->setStyleSheet(" QPushButton{background-color:#D4D4D4;color : black; font: bold 17pt;border-style :outset; border-width: 3px;border-radius: 8px;\
                                                border-color : black; padding: 6px;}");
            buttonOpenExisting->setCursor(Qt::PointingHandCursor);
            leftButton->addWidget(buttonNewProject);
            rightButton->addWidget(buttonOpenExisting);
          setFocus();

         QObject::connect(buttonNewProject, SIGNAL(clicked()), this, SLOT(goNewProject()));
         QObject::connect(buttonOpenExisting, SIGNAL(clicked()), this, SLOT(goExistingProject()));

         //au milieu!
         QDesktopWidget *widget = QApplication::desktop();
         int desktop_width = widget->width();
         int desktop_height = widget->height();
         int x = desktop_width / 2 - width() / 2;
         int y = desktop_height / 2 - height() / 2 - 25;
         move(QPoint(x, y));
         show();
}

welcome::~welcome()
{
    delete layout;
}

void welcome::goNewProject()
{
    newProject *newpro = new newProject();
    this->~welcome();

}

void welcome::goExistingProject()
{
    existingProject *expro = new existingProject();
    this->~welcome();
}
