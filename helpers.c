/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

#define MAX 65536

/**
 * Returns true if value is in array of n values, else false.
 * Binary search
 */
bool search(int value, int values[], int low, int n)
{
    if (n < 0)
        return false;
    
    // Find the middle of array   
    int middle = (low + n) / 2;
    
    // If the value is less than the value of the middle of the array
    if (values[middle] < value)
        return search(value, values, low + 1, n);
        
    // If the value is greater than the value of the middle of the array
    else if (values[middle] > value)
        return search(value, values, low, n - 1);
        
    // Desired value is found
    else
        return true;
    
    // Desired value isn't found
    return false;
}

/**
 * Sorts array of n values.
 * Counting sort
 */
void sort(int values[], int n)
{
    int tmp_array[MAX] = {0};
    // Counting how many times each number appears
    for (int i = 0; i < n; i++)
         tmp_array[values[i]]++;
    // Counting amount of elements
    for (int j = 1; j <= MAX; j++)
         tmp_array[j] += tmp_array[j - 1];
    // Rewriting in order
    for (int i = 0; i < n; i++) 
      values[--tmp_array[values[i]]] = values[i];
}
