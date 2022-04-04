#ifndef __RUNSIMULATIONS__
#define __RUNSIMULATIONS__ 1

#include <queue.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/*----- structure definition -----*/

struct simulationState
{
    QUEUE *left;
    QUEUE *right;
    int trafficLight, iteration, switchIteration, leftPassed, rightPassed;
    int totalLeft, totalRight, maxLeft, maxRight, clearLeft, clearRight;
    gsl_rng *r;
};

typedef struct simulationState STATE;

/*----- function prototypes -----*/

void runOneSimulation (STATE *, float, float, int, int);

#endif