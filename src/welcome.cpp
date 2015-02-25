#include "welcome.h"


welcome::welcome()
{

        setWindowIcon(QIcon(":Icones/crayon.png"));
        setWindowTitle("Draw Me Now");

        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(QImage(":Fond/pell.jpg").scaled(735,492,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
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
        buttonOpenExisting= new QPushButton("Open existing Project");
            buttonNewProject->setFixedSize(200,80);
            buttonNewProject->setStyleSheet(" color : black; font:15pt");
            buttonOpenExisting->setFixedSize(200,80);
            buttonOpenExisting->setStyleSheet(" color : black;font:15pt");
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
