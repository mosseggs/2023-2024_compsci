#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define ALPHASIZE 26

int main(void)
{
    string s1 = get_string("Word 1: ");
    string s2 = get_string("Word 2: ");

    if (!strcasecmp(s1, s2))
    {
        printf("EXACT MATCH\n");
        return 0;
    }

    int characters[ALPHASIZE] = {0};
    int len = strlen(s1);
    if(strlen(s1) != strlen(s2))
    {
        printf("NOT ANAGRAM\n");
        return 1;
    }

    for (int i = 0; i < len; i++)
    {
        if (isalpha(s1[i]) && isalpha(s2[i]))
        {
            characters[tolower(s1[i]) - 'a']++;
            characters[tolower(s2[i]) - 'a']--;
            printf("%i,%i\n",characters[tolower(s1[i] - 'a')], characters[tolower(s2[i] - 'a')]);
        }
        else{
            printf("Alpha chars only!\n");
            return 1;
        }
    }
    // Prints Output
    for(int i = 0; i < ALPHASIZE; i++)
    {
        if(characters[i])
        {
            printf("NOT ANAGRAM\n");
            return 0;
        }
    }
    printf("ANAGRAM\n");
}