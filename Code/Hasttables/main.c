#include <stdio.h>
#include <string.h>
#include "file.h"
#include "dictionary.h"
/*
Shane Bolding
Data Stuctures and Algorithms II
project 1
main.c
*/


int main(void)
{

    genRawData();
    genEncryptedData();
    genHashTable();
    checkPasswords();
    
    
    return 0;
}