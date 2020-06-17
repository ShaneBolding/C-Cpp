#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dictionary.h"
#include "file.h"
#include "password.h"

//defines the value of key
#define key "456def789"

//generates the rawData.dat file
void genRawData(void)
{
    //sets all the variables needed
    char const* const fileName = "lastNames.txt";
    FILE *fp = fopen(fileName, "r");
    char line[256];
    char* pch;
    char password[10];
    int i,j,k;
    
    //while loop to read line by line of the file
    while(fgets(line, sizeof(line) ,fp))
    {
        i = 0;
        //tokening
        pch = strtok(line," ");
        
        while(pch != NULL)
        {
            
            //slows program to allow different passwords for the 0th, 10000th ... place
            for(j=0;j<100;j++)
            {
                for(k=0;k<200;k++)
                {
                    k++; //absolutely does nothing
                }
            } 
            
            //breaks the while after first tokened item
            if(i>0)
            {
                break;
            }
            //ensures passord is cleared 
            memset(password,0,sizeof(password));
            //makes the name lwr case
            lwrCase(pch);
            //puts a tab between name and password
            strcat(pch,"\t");
            //puts password on string after generating a password
            strcat(pch,generatePassword(password));
            //prints rawData.dat
            printFile(pch,"rawData.dat");
            pch = strtok(NULL, " ");
            i++;
        }

    }
    
    fclose(fp);
    
}
//prints a string into a file name given by parameters
void printFile(char userIds[],char fileName[])
{
    
    //char line[256];
        
    FILE *fp = fopen(fileName, "a");
    
    fprintf(fp, "%s\n" , userIds);
    
    
    
    fclose(fp);
        
}
//generates encryptedData.txt
void genEncryptedData(void)
{
    
    char const* const fileName = "rawData.dat";
    FILE *fp = fopen(fileName, "r");
    char name[36];
    char password[36];
    
    //run till end of file
    while(!feof(fp))
    {
        //grabs name and password seperated by a tab
        fscanf(fp,"%[^\t]\t%[^\n]\n",name,password);
        //encrypts using a key defined at the top of file
        encryption(key,password);
        strcat(name,"\t");
        strcat(name,password);
        //prints into a file called encryptedData.txt
        printFile(name,"encryptedData.txt");

    }
    
    fclose(fp);
    
}
//turns all letters from name lower case
char* lwrCase(char a[])
{
    
    int len,i;
    len = strlen(a);
    for(i = 0; i < len; ++i)
    {
        if(a[i]<91 && a[i]>64)
        {
            a[i] = a[i] + 32;
        }
        else continue;   
    }
    return a;
    
}
//prints the 6 lines of information comparing rawData.dat and the created hashtable
void checkPasswords(void)
{
    
    int i = 0;
    //need all these char arrays so I can store the data and compare them
    char const* const fileName = "rawData.dat";
    FILE *fp = fopen(fileName, "r");
    char name[36];
    char password[36];
    char secPass[36];
    char hashPass[36];
    char falsePass[36];
    char falseEncrypt[36];
    
    //reads rawData.dat until end of file
    while(!feof(fp))
    {
        fscanf(fp,"%[^\t]\t%[^\n]\n",name,password);
        //every 10000 name will be used
        if(i%10000 == 0)
        {
            //copys information before its manipulated
            strcpy(secPass,password);
            strcpy(falsePass,password);
            //changes the 4th letter of the password to a unless it is a
            if(falsePass[3] != 'a')
                falsePass[3] = 'a';
            else falsePass[3] ='b';
            //copys the fake password before manipulation
            strcpy(falseEncrypt,falsePass);
            //encrypts the false and real password
            encryption(key,falseEncrypt);
            encryption(key,password);
            //gets the password from the hashtable by using the name 
            strcpy(hashPass,findPassword(name));
            //prints info
            printf("name from rawData.dat: %s\npassword before encryption: %s\n",name,secPass);
            printf("password encrypted: %s\npassword from hashtable:%s\n",password,hashPass);
            printf("false password before encryption: %s\nfalse password encrypted: %s\n\n",falsePass,falseEncrypt);
        }
        
    i++;
    }
    
    fclose(fp);
    
    
        
}
