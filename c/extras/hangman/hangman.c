#include "phrases.c"
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool guessed[26];
bool win = false;
// You get a max of 4 wrong guesses in hangman, 5th ends the game
// the wrongGuesses holds the wrong letters, tries holds how many wrong answers.
char wrongGuesses[5];
int tries = 5;

void play(int len, string answer, string guesses);

int main(void)
{
    // Generates a random number from 0-925, and grabs the "phrase" corrosponding to that answer
    // for phrases see phrases.c
    srand(time(NULL));
    int key = rand() % 926;
    string answer = phrasesSpaced[key];
    int len = strlen(answer);
    // guesses holds the answer box, the placeholder lines.
    char guesses[len + 1];

    // populate guesses based on the phrase. only non-space and non-letter characters are punctuation(&,.,?,!)
    for (int i = 0; i < len; i++)
    {
        if (ispunct(answer[i]))
        {
            char str[1] = {answer[i]};
            strcat(guesses, str);
        }
        else if (!isblank(answer[i]))
        {
            strcat(guesses, "_");
        }
        else
        {
            strcat(guesses, " ");
        }
    }
    printf("%s\n", guesses);

    // sometimes, the first character of "guesses" is automatically made into a SOH(Start of Header),
    //  so this counteracts that by removing it if it is there.
    if (guesses[0] == 1)
    {
        play(len, answer, guesses + 1);
    }
    else
    {
        play(len, answer, guesses);
    }

    // If they win, they win, and if they lose, tell them the correct answer.
    if (win == true)
    {
        printf("You Won!\n");
    }
    else
    {
        printf("You Lose! The answer was “%s”\n", phrases[key]);
    }

    return 0;
}

void play(int len, string answer, string guesses)
{
    if (tries == 0)
    {
        return;
    }
    char guess = get_char("Guess a letter! ");
    bool wrong = true;
    for (int i = 0; i < len; i++)
    {
        if (tolower(guess) == answer[i] && !guessed[tolower(guess) - 97])
        {
            wrong = false;
            guesses[i] = answer[i];
        }
    }
    if (wrong == true && !guessed[tolower(guess) - 97] && isalpha(guess))
    {
        guessed[tolower(guess) - 97] = true;
        char str[3] = {tolower(guess), ','};
        strcat(wrongGuesses, str);
        printf("Wrong guesses: %s\n", wrongGuesses);
        tries--;
    }
    if (!guessed[tolower(guess) - 97] && isalpha(guess))
    {
        printf("%s\n", guesses);
    }
    guessed[tolower(guess) - 97] = true;
    if (!strcmp(guesses, answer))
    {
        win = true;
        return;
    }
    else
    {
        play(len, answer, guesses);
    }
    return;
}