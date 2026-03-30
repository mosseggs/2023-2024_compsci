#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Blur
int min(int var, int minim);
int max(int var, int maxim);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find the average of every value in the pixel, then set all pixels to this "average"
            float avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // find the rounded value of the equation, but if it overflows cap it at 255
            RGBTRIPLE pixel = image[i][j];
            image[i][j].rgbtRed = max(round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue), 255);
            image[i][j].rgbtGreen = max(round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue), 255);
            image[i][j].rgbtBlue = max(round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue), 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // swap the front and back pixels with a intermediary of a filler variable
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE copy = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = copy;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // height
    for (int i = 0; i < height; i++)
    {
        // width
        for (int j = 0; j < width; j++)
        {
            // context: min finds the MINIMUM VALUE of k/l and max finds the MAXIMUM VALUE of k/l, hence their names
            // despite min being a max fucntion and vice versa. Appologies but its too late to change it.
            int minh = min(i - 1, 0);
            int maxh = max(i + 1, height - 1);
            int minw = min(j - 1, 0);
            int maxw = max(j + 1, width - 1);
            // counter for total # of R,G,B respectivley in a box.
            int TRed = 0, TBlue = 0,TGreen = 0;
            // height in box
            for (int k = minh; k <= maxh; k++)
            {
                // width in box
                for (int l = minw; l <= maxw; l++)
                {
                    TRed += image[k][l].rgbtRed;
                    TGreen += image[k][l].rgbtGreen;
                    TBlue += image[k][l].rgbtBlue;
                }
            }
            // finds total # of boxes
            int total = ((maxh + 1) - (minh)) * ((maxw + 1) - (minw));
            // If TRed / total isn't a float, it auto rounds down here, giving errors of -1.
            copy[i][j].rgbtRed = round((float) TRed / total);
            copy[i][j].rgbtBlue = round((float) TBlue / total);
            copy[i][j].rgbtGreen = round((float) TGreen / total);
        }
    }
    // If it isn't outside, it just uses the new values in the calcs for next pixel which we dont want.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
// context: min finds the MINIMUM VALUE of k/l and max finds the MAXIMUM VALUE of k/l, hence their names
// despite min being a max fucntion and vice versa. Appologies but its too late to change it.
int max(int var, int maxim)
{
    if (maxim < var)
    {
        return maxim;
    }
    return var;
}
// context: min finds the MINIMUM VALUE of k/l and max finds the MAXIMUM VALUE of k/l, hence their names
// despite min being a max fucntion and vice versa. Appologies but its too late to change it.
int min(int var, int minim)
{
    if (var < minim)
    {
        return minim;
    }
    return var;
}