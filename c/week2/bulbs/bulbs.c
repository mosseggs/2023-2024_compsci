#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    // Get the message to encode
    string message = get_string("Message: ");
    int binary[strlen(message)][BITS_IN_BYTE];
    int ascii[strlen(message)];
    // translate the message into ASCII code
    for (int i = 0; i < strlen(message); i++)
    {
        ascii[i] = (int) message[i];
    }
    // i holds the letter, j holds the bit location
    for (int i = 0; i < strlen(message); i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            binary[i][j] = ascii[i] - (int) pow(2, BITS_IN_BYTE - (j + 1));
            // if the current bit(starts at 128) can be subtracted from the ascii letter, then do so and give it an "on" signal.
            // else give it an "off" signal.
            if (binary[i][j] >= 0)
            {
                binary[i][j] = 1;
                ascii[i] -= (int) pow(2, BITS_IN_BYTE - (j + 1));
            }
            else
            {
                binary[i][j] = 0;
            }
        }
    }
    // i holds the letter, j holds the bit location
    // prints the bulbs, go to next line after every character.
    for (int i = 0; i < strlen(message); i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(binary[i][j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
