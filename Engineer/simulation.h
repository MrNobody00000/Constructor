#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include "greetingwindow.h"
class Simulation : public QWidget
{
    Q_OBJECT
public:
    Simulation(GreetingWindow *parent = 0);

    GreetingWindow  *fromHead;
};

#endif // SIMULATION_H
