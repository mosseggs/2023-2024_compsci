//Detect if a file is a GIF
//Execute a ./gif kagepro.gif

#include <stdbool.h>
#include <stdio.h>

const char signiture[6] = {'G','I','F','8','9','a'};

bool is_gif(FILE *f);

int main (int argc, char *argv[]){
    if( argc != 2)
    {
        printf("Usage: ./gif filename\n");
        return 1;
    }

    //Open file
    FILE *f = fopen(argv[1], "r");

    if(!f)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //Check for gif signature;
    if(is_gif(f))
    {
        printf("GIF\n");
        return 0;
    }
    else
    {
        printf("NOT GIF\n");
    }

    //Close file
    fclose(f);
}

bool is_gif(FILE *f)
{
    //Read bytes into a buffer
    unsigned char buffer[6];
    //fread(where it goes, how many bytes each item is, how many it reads, where it reads from);
    int bytes = fread(buffer, 1, 6, f);

    //Check # of bytes read
    if(bytes!=6)
    {
        return false;
    }

    //Check each bytes
    for(int i = 0; i < 6; i++)
    {
        if(buffer[i] != signiture[i])
        {
            return false;
        }
    }
    return true;
}