#include <cs50.h>
#include <stdio.h>

void print_row(int i);

int main(void)
{
    // ask for heights
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);
    // reverse it
    for (int i = 1; i <= height; i++)
    {
        // print the spaces beforehand
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");
        }
        // print the hashtags
        print_row(i);
        // the gap
        printf("  ");
        // the reciprocating hashtags
        print_row(i);
        printf("\n");
    }
}

void print_row(int i)
{
    for (int j = 1; j <= i; j++)
    {
        printf("#");
    }
}