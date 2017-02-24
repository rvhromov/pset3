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
bool search(int value, int values[], int n)
{
    if(n < 0)
        return false;
    
    int middle = 0;
    int left_side = 0;
    int right_side = n;
    
    while (left_side <= right_side)
    {
        // Находим половину
        middle = (left_side + right_side) / 2;
        // Если искомый элемент меньше половины, то ищем в левой части
        if (value < values[middle])
            right_side = middle - 1;
        // Если искомый элемент больше половины, то ищем в правой части
        else if (value > values[middle])
            left_side = middle + 1;
        // Искомый элемент равняется половине
        else 
            return true;
    }
    
    return false;
}

/**
 * Sorts array of n values.
 * Counting sort
 */
void sort(int values[], int n)
{
    int tmp_array[MAX] = {0};
    // Считаем сколько раз встречается каждое число
    for (int i = 0; i < n; i++)
         tmp_array[values[i]]++;
    // Подсчитываем количество элементов
    for (int j = 1; j <= MAX; j++)
         tmp_array[j] += tmp_array[j - 1];
    // Переписываем по порядку
    for (int i = 0; i < n; i++) 
      values[--tmp_array[values[i]]] = values[i];
}
