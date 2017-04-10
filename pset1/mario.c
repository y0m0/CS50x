#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height;
    
    // prompt user for a int < 23 and > 0
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);    
    
    
    // print pyramid
    for (int i = 1; i <= height; i++)
    {
        printf("%.*s", height - i, "                         ");
        printf("%.*s", i + 1,      "#########################");
        printf("\n");
    }
}


