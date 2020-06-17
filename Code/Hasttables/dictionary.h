#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct keyValuePair *KVP;


void genHashTable();
void insert(char name[], char password[]);
int hash(char name[]);
char* findPassword(char name[]);
void showTable(void);

void createArray();

#endif
