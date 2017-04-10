/* Vigenere Chiper
 * take a string and a key 'k' as imput and return
 * an encrypted string using 'k' as the shift value
 * for the Ceaser Chiper.
 *
 * Usage:  ./vigenere key 
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string key;
string phrase;


int main(int argc, string argv[])
{
    key = argv[1];
    
    // check if just the encryption key was given as argument
    if (argc != 2)
    {
        printf("wrong number of arguments\n");
        return 1;        
    }
    else
    {
        // check if the key is composed of only alphabetical chars
        for (int i = 0, len = strlen(key); i < len; i++)
        {
            if (isalpha(key[i]) == false)
            {
                printf("key must be composed of letters only\n");
                return 1;
            }
        }   
                               
        // ask for a text to be encrypted
        phrase = GetString();
    }
    
    int upper = 'A';
    int lower = 'a';
    int key_i = 0;    // key index
    int key_l = strlen(key);  // key lenght
    int k;
    
    
    // iterate over the letter of the phrase
    for (int i = 0, len = strlen(phrase); i < len; i++)
    {       
        
        // check if the character is a letter
        if (isalpha(phrase[i]))
        {
            // generate the key shift based on the char
            if (isupper(key[key_i % key_l]))
            {
                k = key[key_i % key_l] - upper;
            } 
            else if (islower(key[key_i % key_l]))
            {
                k = key[key_i % key_l] - lower;
            }
            
            
            
            // check if it's upper case or not and encrypt using the given key
            if (isupper(phrase[i]))
            {
                printf("%c", ((phrase[i] - upper + k) % 26) + upper);              
                key_i++; // increment key index              
            }
            else
            {
                printf("%c", ((phrase[i] - lower + k) % 26) + lower);              
                key_i++;  // increment key index              
            }
               
        }
        // print non alphabetical character
        else
        {
            printf("%c", phrase[i]);
        }
    }
    
    printf("\n");
    
    return 0; 
}     
