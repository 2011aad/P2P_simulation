
#include "simulation.h"
#include "event.h"
#include <iostream>
#include <queue>
#include <vector>


using namespace std;

int main()
{
    Simulation sim = Simulation(100, 500000, 30, 10, 10, 1);
    sim.run();

    cout<<"Mean queue length: "<<sim.meanQueueLength()<<endl;
    return 0;
}



