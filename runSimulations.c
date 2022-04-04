#include <runSimulations.h>

int main(int argc, char *argv[])
{
    STATE state;
    QUEUE *left = createQueue();
    QUEUE *right = createQueue();

    const gsl_rng_type *T;
    gsl_rng            *r;

    /* Create a random number generator. */
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    /* Seed the random number generator to current time. */
    gsl_rng_set(r, time(0));

    int leftPeriod, rightPeriod;
    float leftArrival, rightArrival, averageWaitLeft, averageWaitRight;

    printf("Please enter the left arrival rate (0.0 to 1.0): ");

    do
    {
        if (scanf("%f", &leftArrival) != 1)
        {
            printf("Invalid input type\n");
            fprintf(stderr, "error Invalid Input Type: An invalid type was inputted.\n");
            exit(EXIT_FAILURE);
        }
        if (leftArrival < 0.0 || leftArrival > 1.0)
        {
            printf("Please enter a decimal number between 0.0 and 1.0: ");
        }
    }
    while(leftArrival < 0.0 || leftArrival > 1.0);

    printf("Please enter the right arrival rate (0.0 to 1.0): ");

    do
    {
        if (scanf("%f", &rightArrival) != 1)
        {
            printf("Invalid input type\n");
            fprintf(stderr, "error Invalid Input Type: An invalid type was inputted.\n");
            exit(EXIT_FAILURE);
        }
        if (rightArrival < 0.0 || rightArrival > 1.0)
        {
            printf("Please enter a decimal number between 0.0 and 1.0: ");
        }
    }
    while(rightArrival < 0.0 || rightArrival > 1.0);

    printf("Please enter the left traffic light green period (1 to 100): ");

    do
    {
        if (scanf("%d", &leftPeriod) != 1)
        {
            printf("Invalid input type\n");
            fprintf(stderr, "error Invalid Input Type: An invalid type was inputted.\n");
            exit(EXIT_FAILURE);
        }
        if (leftPeriod < 1 || leftPeriod > 100)
        {
            printf("Please enter an integer between 1 and 100: ");
        }
    }
    while(leftPeriod < 1 || leftPeriod > 100);

    printf("Please enter the right traffic light green period (1 to 100): ");

    do
    {
        if (scanf("%d", &rightPeriod) != 1)
        {
            printf("Invalid input type\n");
            fprintf(stderr, "error Invalid Input Type: An invalid type was inputted.\n");
            exit(EXIT_FAILURE);
        }
        if (rightPeriod < 1 || rightPeriod > 100)
        {
            printf("Please enter an integer between 1 and 100: ");
        }
    }
    while(rightPeriod < 1 || rightPeriod > 100);

    printf("\nParameter values:\n");
    printf("    from left:\n");
    printf("        traffic arrival rate:  %.02f\n",leftArrival);
    printf("        traffic light period:  %03d\n",leftPeriod);
    printf("    from right:\n");
    printf("        traffic arrival rate:  %.02f\n",rightArrival);
    printf("        traffic light period:  %03d\n",rightPeriod);

    state.left = left;
    state.right = right;
    state.trafficLight = 0;
    state.iteration = 0;
    state.switchIteration = leftPeriod;
    state.leftPassed = 0;
    state.rightPassed = 0;
    state.totalLeft = 0;
    state.totalRight = 0;
    state.maxLeft = 0;
    state.maxRight = 0;
    state.clearLeft = 0;
    state.clearRight = 0;
    state.r = r;

    /* Runs until hundred iterations and both queues are empty. */
    while (isEmpty(state.left) != 1 || isEmpty(state.right) != 1 || state.iteration < 100)
    {
        runOneSimulation(&state, leftArrival, rightArrival, leftPeriod, rightPeriod);
    }
    averageWaitLeft = (double)state.totalLeft / (double)state.leftPassed;
    averageWaitRight = (double)state.totalRight / (double)state.rightPassed;

    printf("\nResults (averaged over 100 runs):\n");
    printf("    from left:\n");
    printf("        number of vehicles:     %03d\n",state.leftPassed);
    printf("        average waiting time:   %.02f\n",averageWaitLeft);
    printf("        maximum waiting time:   %03d\n",state.maxLeft);
    printf("        clearance time:         %03d\n",state.clearLeft);
    printf("    from right:\n");
    printf("        number of vehicles:     %03d\n",state.rightPassed);
    printf("        average waiting time:   %.02f\n",averageWaitRight);
    printf("        maximum waiting time:   %03d\n",state.maxRight);
    printf("        clearance time:         %03d\n",state.clearRight);

    /* Freeing up allocated memory. */
    emptyQueue(state.left);
    emptyQueue(state.right);
    gsl_rng_free(state.r);

    return EXIT_SUCCESS;
}

/* Runs one iteration of the simulation, updating the state as it does. */
void runOneSimulation (STATE *state, float leftArrival, float rightArrival,
                       int leftPeriod, int rightPeriod)
{
    int joinedIteration, waitTime = 0;

    /* Change traffic light colour */
    if (state->switchIteration <= state->iteration)
    {
        if (state->trafficLight == 1)
        {
            state->trafficLight = 0;
            state->switchIteration = state->iteration + leftPeriod;
        }
        else
        {
            state->trafficLight = 1;
            state->switchIteration = state->iteration + rightPeriod;
        }
        state->iteration++;
        return;
    }
    
    /* Adds vehicles if iterations are below hundred. */
    if (state->iteration <= 100)
    {
        if (gsl_rng_uniform(state->r) < leftArrival)
        {
            enqueue(state->left, state->iteration);
        }

        if (gsl_rng_uniform(state->r) < rightArrival)
        {
            enqueue(state->right, state->iteration);
        }

    }
    /* Once iterations are over a hundred stop adding vehicles
    and start counting clearance time. */
    else if (state->iteration > 100)
    {
        if(isEmpty(state->left) != 1)
        {
            state->clearLeft++;
        }
        if (isEmpty(state->right) != 1)
        {
            state->clearRight++;
        }
    }

    /* Removes vehicle from queue depending on which light is green. */
    /* Upon leaving queue the wait time is calculated for the vehicle. */
    if (gsl_rng_uniform(state->r) >= 0.5f && state->trafficLight == 0 && isEmpty(state->left) != 1)
    {
        state->leftPassed++;
        joinedIteration = dequeue(state->left);
        waitTime = state->iteration - joinedIteration;
        state->totalLeft = state->totalLeft + waitTime;
        if (state->maxLeft < waitTime)
        {
            state->maxLeft = waitTime;
        }
    }
    else if (gsl_rng_uniform(state->r) >= 0.5f && state->trafficLight == 1 && isEmpty(state->right) != 1)
    {
        state->rightPassed++;
        joinedIteration = dequeue(state->right);
        waitTime = state->iteration - joinedIteration;
        state->totalRight = state->totalRight + waitTime;
        if (state->maxRight < waitTime)
        {
            state->maxRight = waitTime;
        }
    }
    state->iteration++;
}