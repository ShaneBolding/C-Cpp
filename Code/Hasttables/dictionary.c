#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "file.h"

//defining type of struct keyValuePair
typedef struct keyValuePair 
{
	char name[50];
	char password[50];
	KVP next;
}
kvp;

//declares the MAX array index size
#define MAX 90000
//declares array
struct keyValuePair* array[MAX];

//hashes based on name
int hash(char name[])
{
	int i,index=0;
	for(i=0;i<strlen(name);i++)
	{
		if(name[i]!=' ')
		{
			index = index + (name[i]*137);
		}
	}
	//printf("length of name: %d index: %d\n",strlen(name),index);
	return index%MAX;
}

//generates a hash table
void genHashTable()
{
    
    char const* const fileName = "encryptedData.txt";
    FILE *fp = fopen(fileName, "r");
    char name[36];
    char password[36];
    
    
	createArray();
	
    while(!feof(fp))
    {
        
        fscanf(fp,"%[^\t]\t%[^\n]\n",name,password);
        
        insert(name,password);

    }
    
    fclose(fp);
    //showTable();

}

//inserts all values into the hash table
void insert(char name[], char password[])
{

    //makes a new node
	kvp* newKVP = malloc(sizeof(kvp));

    //gives newKVP info from the parameters
    strcpy(newKVP->name , name);
    strcpy(newKVP->password , password);

    //finds an index
	int index = hash(name);
	//points newKVP's next value to the node array is pointing at
	newKVP->next = array[index];
	//makes the array point at newKVP
    array[index] = newKVP;
	
}

char* findPassword(char name[])
{
    //index like normal
    int index = hash(name);
	
	//should cause this pointer to point at the node the head is pointing to
	KVP currentKVP;
    currentKVP = array[index];
    
    //checks if array holds anything
    while(currentKVP != NULL)
    {

    	//checks if array holds correct name
    	if(strcmp(currentKVP->name,name)==0)
    	{
			return currentKVP->password;

    	}
    	//should get the value the node is pointing to and make currentKVP point at it
    	currentKVP = currentKVP->next;
    }
    return NULL;
    
}

//creates array of KVP
void createArray()
{

	//sets all to null to start with
	int i = 0;
	for (i = 0; i < MAX; i++)
    {
		array[i] = NULL;
		
	}

}
//table used to test existance of hash table and I am leaving it in
void showTable(void)
{
    int i = 0;
    KVP currentKVP;
    for(i=0;i<MAX;i++)
    {
        currentKVP = array[i];
        while(currentKVP!=NULL)
        {
            printf("index: %d\n",i);
            printf("name: %s\n",currentKVP->name);
            currentKVP = currentKVP -> next;
        }
    }
}

