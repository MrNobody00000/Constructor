#ifndef GREETINGWINDOW_H
#define GREETINGWINDOW_H
#include <QWidget>
#include <QtGui>
#include <QLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QFont>
class Programming;
class Testing;
class Simulation;

class GreetingWindow : public QWidget
{
    Q_OBJECT

public:
    GreetingWindow(QWidget *parent = 0);
    // connect other classes
    Programming *progWindow;
    Testing     *testWindow;
    Simulation  *simulateWindow;
    // create GUI elements
    QGridLayout *mainLayout;
    QStackedWidget  *mainStack;
    QGridLayout *greetWLayout;
    QWidget     *greetWindow;
    QPushButton *toProgButton;
    QPushButton *toTestButton;
    QPushButton *backButton;
    QLabel      *windowTitle;
private:
    void createWidgets();
    void layoutWidgets();
    void widgetSettings();
    void comNameChanged(int);
    void CheckComs();
private slots:
    void toProgButtonS();
    void toTestButtonS();
    void backButtonS();
};

#endif // GREETINGWINDOW_H
