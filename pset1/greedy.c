#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int coins = 0;
    
    // ask for how much change is owed
    do
    {
        printf("O hai! How much change is owed?\n");
        change = GetFloat();
    }
    while (change <= 0);
    
    // convert change owed into cents
    int cents = round(change * 100);
    
    // calculate the amount of coins needed by subtractions
    while(cents > 0)
    {
        if (cents > 25)
        {
            cents -= 25;
            coins++;
        }
        
        else if (cents > 10)
        {
            cents -= 10;
            coins++;
        }
        
        else if (cents > 5)
        {
            cents -= 5;
            coins++;
        }
        
        else
        {
            cents -= 1;
            coins++;
        }
     }
      
    printf("%d\n", coins);

}
