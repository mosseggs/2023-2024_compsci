#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Blur, edge
int max(int var, int maxim);
int min(int var, int minim);

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
            // min finds the lower bound of k/l while max finds the upper bound of k/l
            int minh = min(i - 1, 0);
            int maxh = max(i + 1, height - 1);
            int minw = min(j - 1, 0);
            int maxw = max(j + 1, width - 1);
            // counter for total # of R,G,B respectivley in a box.
            int TRed = 0;
            int TBlue = 0;
            int TGreen = 0;
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
// min finds the lower bound of k/l while max finds the upper bound of k/l
int max(int var, int maxim)
{
    return var > maxim ? maxim : var;
}
// min finds the lower bound of k/l while max finds the upper bound of k/l
int min(int var, int minim)
{
    return var < minim ? minim : var;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // x and y components of G, each with RGB components
    int GxRed[height][width], GxGreen[height][width], GxBlue[height][width];
    int GyRed[height][width], GyGreen[height][width], GyBlue[height][width];

    int kernelx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // -1,0,1
    // -2,0,2
    // -1,0,1

    int kernely[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // -1,-2,-1
    // 0,0,0
    // 1,2,1

    // height
    for (int i = 0; i < height; i++)
    {
        // width
        for (int j = 0; j < width; j++)
        {
            // initalize
            GxRed[i][j] = GxGreen[i][j] = GxBlue[i][j] = 0;
            GyRed[i][j] = GyGreen[i][j] = GyBlue[i][j] = 0;

            // min finds the lower bound of k/l while max finds the upper bound of k/l
            int minh = min(i - 1, 0);
            int maxh = max(i + 1, height - 1);
            int minw = min(j - 1, 0);
            int maxw = max(j + 1, width - 1);
            // height in box
            for (int k = minh; k <= maxh; k++)
            {
                // width in box
                for (int l = minw; l <= maxw; l++)
                {
                    // Check for edges using Sobel Operators in x and y directions
                    GxRed[i][j] += kernelx[k - i + 1][l - j + 1] * image[k][l].rgbtRed;
                    GxGreen[i][j] += kernelx[k - i + 1][l - j + 1] * image[k][l].rgbtGreen;
                    GxBlue[i][j] += kernelx[k - i + 1][l - j + 1] * image[k][l].rgbtBlue;

                    GyRed[i][j] += kernely[k - i + 1][l - j + 1] * image[k][l].rgbtRed;
                    GyGreen[i][j] += kernely[k - i + 1][l - j + 1] * image[k][l].rgbtGreen;
                    GyBlue[i][j] += kernely[k - i + 1][l - j + 1] * image[k][l].rgbtBlue;
                }
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // combine x and y directions using pythagorean theorem, then round and find the max
            image[i][j].rgbtRed = max(round((float) sqrt(pow(GxRed[i][j], 2) + pow(GyRed[i][j], 2))), 255);
            image[i][j].rgbtGreen = max(round((float) sqrt(pow(GxGreen[i][j], 2) + pow(GyGreen[i][j], 2))), 255);
            image[i][j].rgbtBlue = max(round((float) sqrt(pow(GxBlue[i][j], 2) + pow(GyBlue[i][j], 2))), 255);
        }
    }
    return;
}
