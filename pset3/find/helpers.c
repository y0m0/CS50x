/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
#include <stdio.h>      
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{    
    if ( n < 0)
    {
        return false;
    }

    int start = 0;
    int end = n - 1;
        
    while (start <= end)
    {
        int middle = (start + end) / 2;
        
        if (values[middle] == value)
        {
            return true;
        }
        else if (values[middle] < value)
        {
            start = middle + 1;
        }
        else if (values[middle] > value)
        {
            end = middle - 1;
        } 
    }
    
    return false;    

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool sorted;
    
    do
    { 
        sorted = false;
                
        for (int k = 0; k < n - 1; k++)
        {
            if (values[k] > values[k+1])
            {
                int temp = values[k];
                values[k] = values[k+1];
                values[k+1] = temp;
                sorted = true;
            }
        }
    }
    while (sorted);
}
