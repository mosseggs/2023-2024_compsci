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
bool found;
bool bin_search(int value, int values[], int size, int minimum)
{
    int mid = (minimum + size) / 2;
    if (minimum >= size)
    {
        return false;
    }
    else if (value < values[mid])
    {
        size = mid;
        bin_search(value, values, size, minimum);
    }
    else if (value > values[mid])
    {
        minimum = mid + 1;
        bin_search(value, values, size, minimum);
    }
    else if (value == values[mid])
    {
        found = true;
        return true;
    }
    if (found == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
