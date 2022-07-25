#include <stdio.h>
#include <math.h>
#include <time.h>
/*
 *  Value of pi is approx. 3.1604170318
    Time spent using step-size of 1 hundred : 0.012000

    Value of pi is approx. 3.1435554669
    Time spent using step-size of 1 thousand: 0.002000

    Value of pi is approx. 3.1417914776
    Time spent using step-size of 10 thousand: 0.001000

    Value of pi is approx. 3.1416126164
    Time spent using step-size of 100 thousand: 0.003000

    Value of pi is approx. 3.1415946524
    Time spent using step-size of 1 million: 0.029000

    Value of pi is approx. 3.1415928541
    Time spent using step-size of 10 million: 0.159000

    Value of pi is approx. 3.1415926683
    Time spent using step-size of 100 million: 1.500000
*/
double calculate(int stepsize, int upper, int lower){
    double interval = 1.0/stepsize;
    double area, sum = 0, yValue = 0, xValue = 0;

    for (int i = 0; i < stepsize; i++) {
        yValue = sqrt(1.0 - (xValue * xValue));
        area = yValue * interval;
        sum += area;
        xValue += interval;
    }
    double final = sum * 4;
    return final;
}
int main() {
    double time_spent = 0.0;

    clock_t start = clock();
    printf("Value of pi is approx. %.10f\n", calculate(1000000, 1, 0));
    clock_t end = clock();

    time_spent = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Time spent: %f", time_spent);
    return 0;
}

