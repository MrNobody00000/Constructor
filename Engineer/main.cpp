#include "greetingwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GreetingWindow w;
    w.show();

    return a.exec();
}
