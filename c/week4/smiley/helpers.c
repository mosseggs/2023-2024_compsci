#include "helpers.h"
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            //change all black pixels to a gradient
            if (!pixel.rgbtBlue && !pixel.rgbtGreen && !pixel.rgbtRed)
            {
                pixel.rgbtBlue = ((width * i) + j) * (255 / (2 * (width * height)));
                pixel.rgbtRed = ((width * i) + j) * (255 / (2 * (width * height)));
                pixel.rgbtGreen = ((width * i) + j) * (255 / (2 * (width * height)));
            }
            //change all white pixels to an opposite gradient shifted 90* counter clockwise
            else if (pixel.rgbtBlue == 255 && pixel.rgbtGreen == 255 && pixel.rgbtRed == 255)
            {
                pixel.rgbtBlue = 255 - ((width * j) + i) * (255 / (2 * (width * height)));
                pixel.rgbtRed = 255 - ((width * j) + i) * (255 / (2 * (width * height)));
                pixel.rgbtGreen = 255 - ((width * j) + i) * (255 / (2 * (width * height)));
            }
            //send all the data back
            image[i][j] = pixel;
        }
    }
}
