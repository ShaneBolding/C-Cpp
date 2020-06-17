#ifndef EQUATIONS_H
#define EQUATIONS_H  

//generates the random float from 0 to 1
float GenNextRandomInterval(float avg);
//calculates analytically Po
float genPo(float lambda,float mu,float M);
//calculates analytically L
float genAvgNumPeople(float Po,float lambda,float mu,float M);
//A factorial fxn for calculations
long factorial(int n);
//calculates and prints the information from the simulation
void printSimulation(float Po, float W, float Wq, int mu, int M,int lambda);
//calculates and prints the information analytically
void printAnalytical(float lambda, float mu, float M);
#endif
