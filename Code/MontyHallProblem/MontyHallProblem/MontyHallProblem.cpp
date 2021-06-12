// MontyHallProblem.cpp : Which is right?
// 6/12/2021

#include <iostream>
//#include <tuple>

struct results
{
    float sitterResult;
    float switcherResult;
};

//test variables
int tests = 1000000;    //number of sub tests per test
int numOfDoors = 100;   //number of doors
int testNumber = 10;    //number of total tests

results testMontyHallProblem(void)
{
    
    int** doors = (int **)calloc(tests, sizeof(int*));
    for (int i = 0; i < tests; i++)
    {
        doors[i] = (int*)calloc(numOfDoors, sizeof(int));
    }
    if (!doors)
    {
        std::cout << "Memory Allocation Failed";
        exit(1);
    }

    results temp;
    for (int i = 0; i < tests; i++)
    {
        int car = (rand() * 661) % numOfDoors;
        if (car < numOfDoors || car >= 0)
        {
            doors[i][car] = 1;
        }       
    }

    //initalize Sitter
    int* Sitter;
    Sitter = (int *)calloc(tests, sizeof(int));
    if (!Sitter) {
        std::cout << "Memory Allocation Failed";
        exit(1);
    }
    //initalize Switcher
    int* Switcher;
    Switcher = (int*)calloc(tests, sizeof(int));
    if (!Switcher) {
        std::cout << "Memory Allocation Failed";
        exit(1);
    }

    for (int i = 0; i < tests; i++)
    {
        int choice = (rand() * 73) % numOfDoors;
        Sitter[i] = doors[i][choice];
    }
    for (int i = 0; i < tests; i++)
    {
        int reveal;
        int choice = (rand() * 569) % numOfDoors;
        for (int j = 0; j < numOfDoors; j++)
        {
            if (j != choice && doors[i][j] != 1)
            {
                doors[i][j] = 2;
            }
        }
        for (int j = 0; j < numOfDoors; j++)
        {
            if (doors[i][j] != 2 && j != choice)
            {
                Switcher[i] = doors[i][j];
                //std::cout << "Switcher choice " << i << ": " << Switcher[i] << std::endl;;
            }
        }
    }

    //figure out percentage
    float sumSitter = 0, sumSwitcher = 0;

    for (int i = 0; i < tests; i++)
    {
        sumSitter += Sitter[i];
        sumSwitcher += Switcher[i];
    }

    temp.sitterResult = (sumSitter / tests) * 100;
    temp.switcherResult = (sumSwitcher / tests) * 100;

    free(Sitter);
    free(Switcher);
    for (int i = 0; i < tests; i++)
    {
        free(doors[i]);
    }

    return temp;
}

int main()
{
    results test;

    float totalAvgSitter = 0;
    float totalAvgSwitcher = 0;
    
    for (int i = 0; i < testNumber; i++)
    {
        test = testMontyHallProblem();
        std::cout << "Sitter percent average correct out of "<< tests <<" guesses (test " << i << ") : " << test.sitterResult << std::endl;
        std::cout << "Switcher percent average correct out of " << tests << " guesses (test " << i << ") : " << test.switcherResult << std::endl;
        totalAvgSitter += test.sitterResult;
        totalAvgSwitcher += test.switcherResult;
    }

    std::cout << "Sitter percent average correct out of " << testNumber <<" of " << tests << ") : " << totalAvgSitter/(float)testNumber << std::endl;
    std::cout << "Switcher percent average correct out of " << testNumber << " of " << tests << ") : " << totalAvgSwitcher/(float)testNumber << std::endl;

    return 0;
}
