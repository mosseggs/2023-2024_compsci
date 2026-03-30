// complete the bubble_sort function

#include <cs50.h>
#include <stdio.h>

// function prototypes
void bubble_sort(int arr[], int size);
void print_array(int arr[], int size);

// size of array
#define SIZE 10

int main(void)
{
    // initialize array
    int arr[] = {1, 8, 4, 6, 0, 3, 5, 2, 7, 9};

    // sort array
    bubble_sort(arr, SIZE);

    // print out the array
    print_array(arr, SIZE);

    // done
    return 0;
}

// Function to print an array
void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

// bubble sort
void bubble_sort(int arr[], int size)
{
    // TODO
    int end = 1;
    bool swap = true;
    // repeat until no swaps
    while (swap == true)
    {
        // assume no swaps are going to occur
        swap = false;
        for (int i = 0; i < size - end; i++)
        {
            // if they are out of place, store the fact they swapped, and swap.
            if (arr[i] > arr[i + 1])
            {
                int store = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = store;
                swap = true;
            }
        }
        // since the end is already sorted, you don't need to check it.
        end++;
    }
}
