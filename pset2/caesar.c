/* Caesar Chiper
 * take a string and a key 'k' as imput and return
 * an encrypted string using 'k' as the shift value
 * for the Ceaser Chiper.
 *
 * Usage:  ./caesar key 
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int k;
string phrase;


int main(int argc, string argv[])
{
    // check if just the encryption key was given as argument
    if (argc != 2)
    {
        printf("wrong arguments\n");
        return 1;        
    }
    else
    {
        // convert the key to an int
        k = atoi(argv[1]);
                
        // ask for a text to be encrypted
        phrase = GetString();
    }
    // iterate over the letter of the phrase
    for (int i = 0, len = strlen(phrase); i < len; i++)
    {
        int upper = 'A';
        int lower = 'a';
        
        // check if the character is a letter
        if (isalpha(phrase[i]))
        {
            // check if it's upper case or not and encrypt using the given key
            if (isupper(phrase[i]))
            {
                printf("%c", ((phrase[i] - upper + k) % 26) + upper); 
            }
            else
            {
                printf("%c", ((phrase[i] - lower + k) % 26) + lower);
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
