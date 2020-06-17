#ifndef SIM_H
#define SIM_H  

typedef struct customer *Cus;
typedef struct line *Line;
typedef struct stats *Stats;

typedef struct stats
{
    int Servers;
	float idleTime;
    float lineTime;
    float waitTime;

}stats;

typedef struct customer
{
	float arrivalTime;
    float StartOfServiceTime;
    float departureTime;
    int aod;
    Cus next;
}Customer;

typedef struct line{
    Cus head;
    Cus tail;
}FIFO;

//called by Main to run the entire simulation
void runSim(int n,int lambda,int mu,int M);
//inserts new arrivals into the priority queue(PQ)
void insert(int* sp, struct customer heap[]); 
//takes the top value of the heap and then runs it in the simulation
void processNextEvent(struct customer heap[], struct line* Line, int *M, int *sp, struct stats* Stats,int n);
//percolates up for the new inserts
void percolateUp(int heapIndex, struct customer heap[]);
//deletes from the PQ 
void deleteNode(int *sp,struct customer heap[]);
//percolates down for departures
void percolateDown(int heapIndex, int heapSize, struct customer heap[]);
//creates the FiFO queue
Line createEmptyLine();
//creates a node pointer for linked list use
Cus createCus(Cus next, float arrivalTime);
//sets the next pointer to the given node
void setNext(Cus currentCus, Cus nextCus);
//adds up the information for the departures
void processStatistics(struct stats* Stats, struct line* Line,struct customer heap[],int M,int n);
//prints the linked list for troubleshooting (not needed for execution)
void printLine(Line currentLine);
//prints the Priority Queue for troubleshooting (not needed for execution)
void printHeap(struct customer heap[]);
#endif