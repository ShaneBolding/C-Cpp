#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "equations.h"
//feed lambda or mu
float GenNextRandomInterval(float avg)
{
    
    float intervalTime;
    float f;

    f = ((float)rand())/RAND_MAX;

    intervalTime = ((-1 * (1.0/avg))*logf(f));
    
    return intervalTime; 
     
}
//gen Po
float genPo(float lambda,float mu,float M)
{
    float Po;
    int i = 0;
    for(i=0;i<M;i++)
    {
        Po += pow((lambda/mu),i)/factorial(i);
    }
    float temp = 1 / factorial(M);
    temp = temp * pow((lambda/mu),M);
    temp = temp * (M*mu/(M*mu-lambda));
    Po += temp;
    Po = 1/Po;
    return Po;
     
}
//gen L
float genAvgNumPeople(float Po,float lambda,float mu,float M)
{
     
     float L = 0;
     float num;
     long den;
     num = pow(lambda,M+1)/pow(mu,M-1);
     den = factorial(M-1) * pow((M*mu - lambda), 2);
     L = num/den;
     L = L * Po;
     L += lambda/mu;
     return L;
     
}

long factorial(int n)
{
  int c;
  long result = 1;
 
  for (c = 1; c <= n; c++)
    result = result * c;
 
  return result;
}

void printSimulation(float Po, float W, float Wq,int mu, int M,int lambda)
{
    float rho,Lq,L;
    //does the math from the gatthered information 
    Lq = Wq * (float)lambda;
    L = Lq + ((float)lambda/(float)mu);
    rho = (float)lambda / ((float)M*(float)mu);
    printf("Simulation Results\n");
    printf("Po:    %f\n",Po);
    printf("L:     %f\n",L);
    printf("W:     %f\n",W);
    printf("Lq:    %f\n",Lq);
    printf("Wq:    %f\n",Wq);
    printf("rho:   %f\n",rho);
    
}

void printAnalytical(float lambda, float mu, float M)
{
    //does the math analytically from the inserted information
    float Po = genPo(lambda,mu,M);
    float L = genAvgNumPeople(Po,lambda,mu,M);
    float W = L/lambda;
    float Lq = L - (lambda/mu);
    float Wq = Lq/lambda;
    printf("Analytical Results\n");
    printf("Po:    %f\n",Po);
    printf("L:     %f\n",L);
    printf("W:     %f\n",W);
    printf("Lq:    %f\n",Lq);
    printf("Wq:    %f\n",Wq);
    printf("rho:   %f\n",(lambda/(M*mu)));
    
    
    
}