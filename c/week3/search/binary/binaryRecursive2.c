// implement binary search function

#include <cs50.h>
#include <stdio.h>

#define NUMBERS 9

bool bin_search(int value, int values[], int size, int minimum);

int main(void)
{
    int arr[] = {2, 4, 6, 7, 8, 11, 14, 18, 20};

    int target = get_int("Enter a number: ");

    if (bin_search(target, arr, NUMBERS, 0))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not found!\n");
    }
}
bool bin_search(int value, int values[], int size, int minimum)
{
    //Set middle
    int mid = (minimum + size) / 2;
    //If the smallest value is bigger or equal to the biggest, something went wrong and the value isnt in the array
    if (minimum >= size)
    {
        return false;
    }
    //If value is smaller than the middle value, check left half
    else if (value < values[mid])
    {
        //if you found it, return true
        if(bin_search(value, values, mid, minimum))
        {
            return true;
        }
    }
    //else check right half
    else if (value > values[mid])
    {
        //if you found it, return true
        if(bin_search(value, values, size, mid + 1))
        {
            return true;
        }
    }
    //else its the middle value, so that means you found it
    else
    {
        return true;
    }
    return false;
}
