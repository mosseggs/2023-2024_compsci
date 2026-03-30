#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text, int length);
float count_words(string text, int length);
int count_sentence(string text, int length);

int main(void)
{
    string text = get_string("Text: ");
    int length = strlen(text);
    float sum = (0.0588 * ((count_letters(text, length) / count_words(text, length)) * 100) -
                 0.296 * ((count_sentence(text, length) / count_words(text, length)) * 100) - 15.8);
    // Grading
    // within range
    if (sum >= 1 && sum <= 16)
    {
        printf("Grade %d\n", (int) round(sum));
    }
    // below
    else if (sum < 1)
    {
        printf("Before Grade 1\n");
    }
    // above
    else
    {
        printf("Grade 16+\n");
    }
}
// functions
// Letters
int count_letters(string text, int length)
{
    int letters = 0;
    for (int i = 0; i < length + 1; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}
// words
float count_words(string text, int length)
{
    int words = 0;
    for (int i = 0; i < length + 1; i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            words++;
        }
    }
    return words;
}
// sentences
int count_sentence(string text, int length)
{
    int sentence = 0;
    for (int i = 0; i < length + 1; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentence++;
        }
    }
    return sentence;
}
// this would be so much easier without a function