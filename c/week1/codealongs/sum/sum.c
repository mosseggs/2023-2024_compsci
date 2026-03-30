#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, string argv[])
{
     if (argc < 1)
    {
        printf("Usage: ./sum <num1> <num2>...<num n>\n");
        return 1;
    }
    int sum=0;
    int n=0;
    do{
        n=n+1;
    }
    while(argv[n] != NULL);
    for(int i = 1; i < n; i++)
    {
        sum+=atoi(argv[i]);
    }
    printf("%i\n",sum);
}