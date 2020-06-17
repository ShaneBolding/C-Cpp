#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "password.h"

//strpbrk
/* strcspn example */

char* generatePassword(char a[]){
    
    int i;
    time_t t;
    int asciiJump = 0;
    int var = 0;
    
    srand((unsigned) time(&t));
    
    for(i=0;i<9;i++)
    {
        var = rand() % 2;
        
        if(var == 0)
        {
            asciiJump = 48 + (rand() % 9);
        }
        else if(var == 1)
        {
            asciiJump = 97 + (rand() % 25);
        }
        a[i] = asciiJump;
    }
    a[9] = '\0';
    
    return a;
}

char* encryption(char key[],char password[])
{
    
    int passwordLen = strlen(password);
    int keyLen = strlen(key);
    int i, j;
 
    char newKey[passwordLen], encryptedPassword[passwordLen];// decryptedPassword[passwordLen];
 
    //generating new key
    for(i = 0, j = 0; i < passwordLen; ++i, ++j){
        if(j == keyLen)
            {
                j = 0;
            }
 
        newKey[i] = key[j];
    }
 
    newKey[i] = '\0';
 
    int temp; 
    //encryption
    for(i = 0; i < passwordLen; ++i)
        {
            if(newKey[i]>96 && newKey[i]<123)
            {
                //locates the key vs cypher plus password for the algorithm below
                temp = ((newKey[i] - 'a') + password[i]);
                if(password[i]>96)
                {
                    if(temp<123)
                    {
                        encryptedPassword[i] = temp;
                    }
                    else if((temp - 123)>9)
                    {
                        encryptedPassword[i] = (((temp - 123) - 10) + 'a');
                    }
                    else encryptedPassword[i] = ((temp - 123) + 48);
                }
                else 
                {
                    if(temp<58)
                    {
                        encryptedPassword[i] = temp;
                    }
                    else encryptedPassword[i] = ((temp - 58) + 'a');
                }
            }
            else
            {
                
                temp = ((newKey[i] - 48) + password[i]);
                if(temp > 122)
                {
                    encryptedPassword[i] = ((temp - 122) + 47);
                }
                if(temp > 96 && temp < 123)
                {
                    encryptedPassword[i] = temp;
                }
                if(temp > '9' && temp < 97)
                {
                    encryptedPassword[i] = temp - 58 + 'a';
                }
                if(temp >= '0' && temp <= '9')
                {
                    encryptedPassword[i] = temp;
                }
            }
        }
    
 
    encryptedPassword[i] = '\0';
 
  
    for(i = 0; i < passwordLen; ++i)
    {
        password[i] = encryptedPassword[i];
    }
	return password;

    
}