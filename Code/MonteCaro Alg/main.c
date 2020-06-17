#include <stdio.h>
#include <string.h>
#include "sim.h"
#include "equations.h"
/*
Shane Bolding
Data Stuctures and Algorithms II
project 2
main.c
*/

int main(void)
{
    
    int lambda,mu,M,n;
    //int lambda = 2, mu = 3, M = 2, n = 5000;
    //asks user for info to run the simulation
    printf("Please enter these four values to begin the program\n");
    printf("Lambda: ");
    scanf("%d",&lambda);
    printf("mu: ");
    scanf("%d",&mu);
    printf("M: ");
    scanf("%d",&M);
    printf("n: ");
    scanf("%d",&n);


    runSim(n,lambda,mu,M);
    
    printAnalytical(lambda,mu,M);

    
    
    return 0;
}
