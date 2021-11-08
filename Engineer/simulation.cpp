#include "simulation.h"
#include "greetingwindow.h"
Simulation::Simulation(GreetingWindow *parent) : QWidget(parent)
{
    fromHead = parent;
}
