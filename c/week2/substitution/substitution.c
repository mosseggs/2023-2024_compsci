#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int cipherer(int uorl, char plain, int cipher, string substitution);

int main(int argc, string argv[])
{
    // if wrong number of command line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string substitution;
    substitution = argv[1];
    int check = 0;
    int cipher = 0;
    int key = 0;
    int num = 0;
    // calulate cipher length + if the cipher is a number
    while (substitution[cipher] != '\0')
    {
        if (islower(substitution[cipher]))
        {
            key = substitution[cipher] - 97;
            substitution[cipher] -= 97;
        }
        else if (isupper(substitution[cipher]))
        {
            key = substitution[cipher] - 65;
            substitution[cipher] -= 65;
        }
        check += pow(key,2);
        cipher++;
    }
    // check if cipher is 26 letters long, and has only 1 of every letter of the alphabet
    if (cipher != 26 || check != 5525)
    {
        printf("Key must contain the 26 letters of the alphabet, each only once\n");
        return 1;
    }
    // get plaintext, and grab it's length
    string plain = get_string("plaintext: ");
    cipher = 0;
    // cipher the plaintext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        cipher = 0;
        // if lowercase
        if (islower(plain[i]))
        {
            cipherer(97, plain[i], cipher, substitution);
        }
        // if uppercase
        else if (isupper(plain[i]))
        {
            cipherer(65, plain[i], cipher, substitution);
        }
        // if a symbol
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}

int cipherer(int uorl, char plain, int cipher, string substitution)
{
    // turn the letter into a number, 0-25. if it doesnt already match to it's designated cipher placeholder, find the cipher
    // placeholder.
    int convert = 0;
    plain = plain - uorl;
    if (cipher != plain)
    {
        while (cipher < 26 && (cipher != plain))
        {
            cipher++;
        }
    }
    else
    {
        convert = plain;
    }
    // print the ciphered text
    printf("%c", ((convert + (substitution[cipher])) % 26) + uorl);
    return 0;
}