/**
 * Sorts array in plce using bubble sort
 */

void sort(int array[], int size)
{
    // cycle through array
    for (int k = 0; k < size - 1; k++)
    {
        // optimize; check if there are no swap
        int swaps = 0;
        
        // swap adjacent elements if out of order
        
        
            // iterate through the array
            for (int i = 0; i < size - 1 - k; i++)    
            {
                // check if array[] and array[size+1] are in order
                if (array[size] > array[size+1])
                {
                    int temp = array[i+1];
                    array[i+1] = array[i];
                    array[i] = temp;
                    swaps++;
                }
            }
            
        if (!swaps)
            break;
    }
}
