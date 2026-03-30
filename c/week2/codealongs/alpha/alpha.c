#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Input: ");

   for (int i = 0,length = strlen(text); i < length; i++)
   {
        if(text[i] < text[i-1])
        {
            printf("No\n");
            return 1;
        }
   }
    printf("Yes\n");
}