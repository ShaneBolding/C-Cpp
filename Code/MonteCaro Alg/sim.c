#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sim.h"
#include "equations.h"
/*
Shane Bolding
Data Stuctures and Algorithms II
project 2
main.c
*/
//sets the priority queue(PQ) size
#define HEAPSIZE 100



void runSim(int n,int lambda,int mu,int M)
{
    //int for loops
    int i;
    //transfers the value of n so it may be manipulated without a pointer
    int f = n;
    int heapSize = 0;
    //creates the sruct needed to pass multiple values to lessen the parameters needed
    struct stats *Stats = malloc (sizeof (struct stats));
    //makes the priority queue
    struct customer *Heap = malloc (HEAPSIZE * sizeof (struct customer));
    //transfers the value of M
    Stats->Servers = M;
    //makes the original PQ
    for(i=0;i<HEAPSIZE;i++)
    {

        insert(&heapSize, Heap);

    }
    //collects the initial idle time
    Stats->idleTime = Heap[0].arrivalTime / (n*100);
    //creates the FIFO queue
    struct line* FIFO = createEmptyLine();
    //runs the loop until the end of simulation
    while(heapSize!=0)
    {
        //processes the top of the heap;
        processNextEvent(Heap,FIFO,&M,&heapSize,Stats,n);
        //checks to see if PQ needs to be refilled
        if(f!=0&&heapSize<M+1)
        {
            //loop refills PQ
            for(i=heapSize;i<HEAPSIZE;i++)
            {
                insert(&heapSize,Heap);
            }
            f--;
        }
        if(f == 0)
        {
            continue;
        }

    }
    //prints the simulation results once the while loop is finished
    printSimulation(Stats->idleTime,Stats->lineTime,Stats->waitTime,mu,M,lambda);
    return;
}

void insert(int* sp, struct customer heap[]) 
{
    *sp +=1;
    //special logic for if the PQ is empty
    if(*sp<2)
    {
        heap[*sp-1].arrivalTime = GenNextRandomInterval(2);
        heap[*sp-1].departureTime = heap[*sp-1].arrivalTime;
    }//normal logic to fill queue
    else 
    {
        //sets departure time and arrival time to same value initially so the prog
        //can just compare the departure time for every situation 
        heap[*sp-1].arrivalTime = heap[*sp-2].arrivalTime + GenNextRandomInterval(2);
        heap[*sp-1].departureTime = heap[*sp-1].arrivalTime;
    }
    //sets the node to an arrival node
    heap[*sp-1].aod = 0;
    /*Adjust its position*/
    percolateUp(*sp-1, heap);
}
//used for troubleshooting
void printHeap(struct customer heap[])
{
    int i = 0;
    for(i=0;i<HEAPSIZE;i++)
    {
        //arrivals
        if(heap[i].aod == 0)
        {
            printf("%d:  %f   %f  ARRIVAL\n",i,heap[i].arrivalTime,heap[i].departureTime);
        }
        //departed
        if(heap[i].aod == 1)
        {
            printf("%d:  %f   %f  DEPARTURE\n",i,heap[i].arrivalTime,heap[i].departureTime);
        }
        //deleted
        if(heap[i].aod == 2)
        {
            printf("%d:  %f   %f  DELETED\n",i,heap[i].arrivalTime,heap[i].departureTime);
        }
    }
    printf("\n");
    
}

void processNextEvent(struct customer heap[], struct line* Line, int *M, int *sp, struct stats* Stats,int n)
{
    //logic for arrivals
    if(heap[0].aod == 0)
    {
        //checks to see if there is a server available
        if(*M>0)
        {
            //logic for dealing with an arrival and an available server
            *M -= 1;
            heap[0].StartOfServiceTime = heap[0].arrivalTime;
            heap[0].departureTime = heap[0].arrivalTime + GenNextRandomInterval(3);
            heap[0].aod = 1;
            //percolates the departure down
            percolateDown(0,*sp,heap);
            return;
        }
        else
        {
            //creates a FIFO queue
            if(Line->head == NULL)
            {
                Cus newCus = createCus(NULL,heap[0].arrivalTime);
                Line->head = newCus;
                Line->tail = newCus;
            }
            //adds to the tail of FIFO
            else
            {
                Cus newCus = createCus(NULL,heap[0].arrivalTime);
                setNext(Line->tail,newCus);
                Line->tail = newCus;
            }
            //printLine(Line); good place to see the FIFO queue get made
            deleteNode(sp,heap);
            return;
        }   
    }
    //if node is a departure
    if(heap[0].aod == 1)
    {
        *M +=1;
        //adds up the simulation stats
        processStatistics(Stats,Line,heap,*M,n);
        //logic for if no FIFO queue is available at departure
        if(Line->head != NULL)
        {
            //grab head
            Cus temp = Line->head;
            Line->head = temp->next;
            temp->next = NULL;
            heap[0].arrivalTime = temp->arrivalTime;
            heap[0].StartOfServiceTime = heap[0].departureTime;
            heap[0].departureTime = heap[0].StartOfServiceTime + GenNextRandomInterval(3);
            //printLine(Line); good place to see FIFO queue get deleted from
            percolateDown(0,*sp,heap);
            *M -=1;
            return;
        }
        //deletes departure
        deleteNode(sp,heap);
        return;
        
        
    }
}

//standard percolateUp logic for a struct
void percolateUp(int heapIndex, struct customer heap[])
{
    
    int parentIndex;
    struct customer temp;
    if(heapIndex!=0)
    {
        parentIndex = heapIndex/2;
        if(heap[parentIndex].departureTime>heap[heapIndex].departureTime)
        {
            temp = heap[parentIndex];
            heap[parentIndex] = heap[heapIndex];
            heap[heapIndex]= temp;
            percolateUp(parentIndex, heap);
        }
    }
    
}

void deleteNode(int *sp,struct customer heap[])
{
    //sets last node to first node
    heap[0] = heap[*sp-1];
    //sets node to deleted
    heap[*sp-1].aod = 2;
    *sp -= 1;
    //if heap is still active
    if(*sp>0)
    {
        percolateDown(0,*sp,heap);
    }
    
    
    
}

void percolateDown(int heapIndex,int heapSize, struct customer heap[])
{
    //printHeap(heap); a good place to print PQ to see it run
    int leftChildIndex,rightChildIndex, minIndex;
    struct customer temp;
    leftChildIndex = heapIndex*2 + 1;
    rightChildIndex = heapIndex*2 + 2;
    //checks the heapsize to determine how far to go
    if(rightChildIndex>=heapSize)
    {
        if(leftChildIndex>=heapSize)
        {
            return;
        }
        else minIndex=leftChildIndex;
    }
    else
    {
        //compares children
        if(heap[leftChildIndex].departureTime<=heap[rightChildIndex].departureTime)
        {
            minIndex = leftChildIndex;
        }
        else minIndex = rightChildIndex;
        //compares parent and min child and swaps if parent is bigger
        if(heap[heapIndex].departureTime>heap[minIndex].departureTime)
        {
            temp = heap[minIndex];
            heap[minIndex]=heap[heapIndex];
            heap[heapIndex]=temp;
            percolateDown(minIndex,heapSize,heap);
        }

    }
    
    
}
//creates FIFO queue
Line createEmptyLine()
{
    Line newLine = malloc(sizeof *newLine);
    newLine->head = NULL;
    newLine->tail = NULL;

    return newLine;
}
//creates node pointer
Cus createCus(Cus next, float arrivalTime)
{
   Cus newCus = malloc(sizeof *newCus);
   newCus->arrivalTime = arrivalTime;
   newCus->next = next;
   
   return newCus;
}
//sets next pointer to nnode pointer given
void setNext(Cus currentCus, Cus nextCus)
{
    currentCus->next = nextCus;
}
//prints FIFO queue
void printLine(Line currentLine)
{
	Cus currentCus = currentLine->head;
	while(currentCus != NULL)
	{
		//processing on a linked list
		printf("arrivalTime:  %f\n", currentCus->arrivalTime);
		currentCus = currentCus->next;
	}
}

void processStatistics(struct stats* Stats, struct line* Line,struct customer heap[],int M,int n)
{
    //calculate Po by averaging all idle times
    if(Stats->Servers==M)
    {
        Stats->idleTime += (heap[1].arrivalTime - heap[0].departureTime)/(n*100);
    }
    //calculate W by averaging all stuck in system time
    Stats->lineTime += (heap[0].departureTime-heap[0].arrivalTime)/(n*100);
    //calculate L by averaging all wait time
    Stats->waitTime += (heap[0].StartOfServiceTime - heap[0].arrivalTime)/(n*100);
    return;
    
}