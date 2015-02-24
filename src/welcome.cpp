#include "welcome.h"


welcome::welcome()
{

        setFixedSize(735,492);

        QFont f( "Arial", 50, QFont::Bold);
        layout = new QVBoxLayout(this);
        setLayout(layout);

        labelWelcome = new QLabel();
            labelWelcome->setText("Welcome to");
            labelWelcome->setFixedSize(735,120);
            labelWelcome->setFont(f);
            labelWelcome->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
            layout->addWidget(labelWelcome);

       labelTitle = new QLabel();
            labelTitle->setText("Draw Me Now !");
            labelTitle->setFixedSize(735,120);
            labelTitle->setFont(f);
            labelTitle->setAlignment(Qt::AlignCenter);
            layout->addWidget(labelTitle);

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
            buttonNewProject->setFixedSize(150,50);
            buttonOpenExisting->setFixedSize(150,50);
            leftButton->addWidget(buttonNewProject);
            rightButton->addWidget(buttonOpenExisting);

         QObject::connect(buttonNewProject, SIGNAL(clicked()), this, SLOT(goNewProject()));

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
