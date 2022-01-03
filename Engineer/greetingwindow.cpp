#include "greetingwindow.h"
#include "programming.h"
#include "testing.h"
#include "simulation.h"
GreetingWindow::GreetingWindow(QWidget *parent)
    : QWidget(parent)
{
    // connect other classes
    progWindow = new Programming(this);
    testWindow = new Testing(this);
    simulateWindow = new Simulation(this);
    // create, layout and set greetind window widgets
    createWidgets();
    layoutWidgets();
    widgetSettings();

    this->setLayout(mainLayout);
    this->showMaximized();
    connect(toProgButton,SIGNAL(clicked()),SLOT(toProgButtonS()));
    connect(toTestButton,SIGNAL(clicked()),SLOT(toTestButtonS()));
    connect(backButton,SIGNAL(clicked()),SLOT(backButtonS()));
}
void GreetingWindow::createWidgets()
{
    mainLayout = new QGridLayout;
    mainStack  = new QStackedWidget;

    greetWLayout    = new QGridLayout;
    greetWindow     = new QWidget;
    toProgButton    = new QPushButton;
    toTestButton    = new QPushButton;
    backButton      = new QPushButton;
    windowTitle     = new QLabel("Программно-технический комплекс Инженер");
}
void GreetingWindow::layoutWidgets()
{
    greetWLayout->addWidget(toProgButton,0,0,Qt::AlignCenter | Qt::AlignCenter);
    greetWLayout->addWidget(toTestButton,0,1,Qt::AlignCenter | Qt::AlignCenter);
    greetWindow->setLayout(greetWLayout);

    mainStack->addWidget(greetWindow);
    mainStack->addWidget(progWindow);
    mainStack->addWidget(testWindow);
    mainStack->addWidget(simulateWindow);

    mainLayout->addWidget(backButton,0,0,Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(windowTitle,0,0,Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(mainStack,1,0);

}
void GreetingWindow::widgetSettings()
{
    mainStack->setCurrentWidget(greetWindow);
    backButton->setVisible(false);
    toProgButton->setStyleSheet("Background: transparent");
    toTestButton->setStyleSheet("Background: transparent");
    backButton->setStyleSheet("Background: transparent");
    toProgButton->setIconSize(QSize(300,300));
    toTestButton->setIconSize(QSize(300,300));
    backButton->setIconSize(QSize(50,50));
    toProgButton->setIcon(QPixmap(":/Icons/Programming.png"));
    toTestButton->setIcon(QPixmap(":/Icons/Testing.png"));
    backButton->setIcon(QPixmap(":/Icons/Back.png"));
    windowTitle->setStyleSheet("Background: transparent");
    windowTitle->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPixelSize(23);
    font.setFamily("Terminator Cyr");
    windowTitle->setFont(font);
}
void GreetingWindow::toProgButtonS()
{
    mainStack->setCurrentWidget(progWindow);
    backButton->setVisible(true);
    windowTitle->setText("Среда разработки");
}
void GreetingWindow::toTestButtonS()
{
    mainStack->setCurrentWidget(testWindow);
    backButton->setVisible(true);
    windowTitle->setText("Раздел проверки подключения");
}
void GreetingWindow::backButtonS()
{
    //if(mainStack->currentWidget() == ;

    mainStack->setCurrentWidget(greetWindow);
    backButton->setVisible(false);
    windowTitle->setText("Программно-технический комплекс Инженер");
}


