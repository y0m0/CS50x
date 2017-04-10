/**
 * Returns true if value is in array of n values, else false.
 */
 
 
bool search(int value, int values[], int n)
{
    // set values for the top and the bottom search
    int lower = 0;
    int upper = n - 1;
    
    // Binary Search
    while (lower <= upper)
    {   
        // find the middle
        int middle = (upper + lower)/2;         
       
        // compare middle to value
        if (values[middle] ==  value)
        {
            return true;
        }
        else if (values[middle] < value)
        {
            lower = middle + 1;
        }
        else if (values[middle] > value)
        {
            upper = middle - 1;
        }
    
    }
    return false;
}
    
    
