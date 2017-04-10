#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    string name = GetString();
    
    // print the first charcter of the given name in uppercase
    if (name[0] >= 'a' && name[0] <= 'z')
    {
        printf("%c", name[0] - 32);
    }
    else
    {
        printf("%c", name[0]);
    }
    
    
    // search for spaces in the name and print the char after it in uppercase
    for(int i = 1; i < strlen(name); i++)
    {
        if (name[i - 1] == ' ')
        {
            // check to see if the char is already uppercase
            if (name[i] >= 'a' && name[i] <= 'z')
            {
                printf("%c", name[i] - 32);
            }
            else
            {
                printf("%c", name[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
