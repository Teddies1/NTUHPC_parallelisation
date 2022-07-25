#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
/*
    with the serial program, the time taken to compute pi with 100 million step sizes was 1.5 seconds
    with a pi value of 3.1415926683
    we shall use the 100 million step size to benchmark our parallelisation process

    with a threadcount of 2, we get
    Value of pi is approx. 3.1415926683
    Time spent: 0.856000

    with a threadcount of 3, we get
    Value of pi is approx. 3.1415926683
    Time spent: 0.934000

    with a threadcount of 4, we get
    Value of pi is approx. 3.1415926683
    Time spent: 1.160000

 */
double calculate(long stepsize, int upper, int lower){

    double interval;
    double area, sum, yValue, xValue;
    int i;
    #pragma omp parallel private(area) shared(sum, xValue, interval)
    {
        interval = 1.0/stepsize;
        sum = 0; xValue = 0;
    }

    #pragma omp parallel for reduction(+: sum)
    for (i = 0; i < stepsize; i++) {
        yValue = sqrt(1.0 - (xValue * xValue));
        area = yValue * interval;
        sum += area;
        xValue += interval;
    }

    double final = sum * 4;
    return final;
}
int main(int argc, char** argv) {
    int thread = atoi(argv[1]);
    #pragma omp parallel num_threads(thread)
    {
        double time_spent = 0.0;

        clock_t start = clock();
        printf("Threadcount: %d\n", omp_get_num_threads());
        printf("Value of pi is approx. %.10f\n", calculate(100000000, 1, 0));
        clock_t end = clock();

        time_spent = (double)(end-start)/CLOCKS_PER_SEC;

        printf("Time spent: %f\n", time_spent);

    }
    return 0;
}

