for i = 0 to n -1
    element = array[i]
    j = i
    
    while (j > 0 and array[j-1] > element)
        array[j] = array [j-1]
        j=j-1
    
    array[j] = element
