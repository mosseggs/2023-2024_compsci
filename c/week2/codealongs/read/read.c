#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int count_letters(string text);

int main(void)
{
    string text = get_string("text");
    printf("letters: %i\n"), count_letters(text);
}

int count_letters(string text)
{
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            n++;
        }
    }
    return n;
}
