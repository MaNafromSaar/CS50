#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int grey_val = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = grey_val;
            image[i][j].rgbtBlue = grey_val;
            image[i][j].rgbtGreen = grey_val;
        }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j].rgbtRed = min(255, round(.393 * tmp.rgbtRed + .769 * tmp.rgbtGreen + .189 * tmp.rgbtBlue));
            image[i][j].rgbtGreen = min(255, round(.349 * tmp.rgbtRed + .686 * tmp.rgbtGreen + .168 * tmp.rgbtBlue));
            image[i][j].rgbtBlue = min(255, round(.272 * tmp.rgbtRed + .534 * tmp.rgbtGreen + .131 * tmp.rgbtBlue));
            // coefficients for rgb values were given
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // write to the original image
    // cases:
    // corners
    image[0][0].rgbtRed = round((copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);
    image[0][0].rgbtGreen = round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen + copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtBlue = round((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) / 4.0);

    image[0][width -1].rgbtRed = round((copy[0][width - 1].rgbtRed + copy[0][width - 2].rgbtRed + copy[1][width - 1].rgbtRed + copy[1][width - 2].rgbtRed) / 4.0);
    image[0][width -1].rgbtGreen = round((copy[0][width- 1].rgbtGreen + copy[0][width - 2].rgbtGreen + copy[1][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen) / 4.0);
    image[0][width -1].rgbtBlue = round((copy[0][width - 1].rgbtBlue + copy[0][width - 2].rgbtBlue + copy[1][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue) / 4.0);

    image[height -1][0].rgbtRed = round((copy[height - 1][0].rgbtRed + copy[height - 1][1].rgbtRed + copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed) / 4.0);
    image[height -1][0].rgbtGreen = round((copy[height - 1][0].rgbtGreen + copy[height - 1][1].rgbtGreen + copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen) / 4.0);
    image[height -1][0].rgbtBlue = round((copy[height - 1][0].rgbtBlue + copy[height - 1][1].rgbtBlue + copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue) / 4.0);

    image[height - 1][width - 1].rgbtRed = round((copy[height - 1][width - 1].rgbtRed + copy[height - 1][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed + copy[height - 2][width - 2].rgbtRed) / 4.0);
    image[height - 1][width - 1].rgbtGreen = round((copy[height - 1][width - 1].rgbtGreen + copy[height - 1][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen + copy[height - 2][width - 2].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtBlue = round((copy[height - 1][width - 1].rgbtBlue + copy[height - 1][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue + copy[height - 2][width - 2].rgbtBlue) / 4.0);


    //edges
    // left edge
    for (int i = 1; i < height -1; i++)
    {
        image[i][0].rgbtRed = round((copy[i - 1][0].rgbtRed + copy[i][0].rgbtRed + copy[i + 1][0].rgbtRed +
                                copy[i - 1][1].rgbtRed + copy[i][1].rgbtRed + copy[i + 1][1].rgbtRed) / 6.0);
        image[i][0].rgbtGreen = round((copy[i - 1][0].rgbtGreen + copy[i][0].rgbtGreen + copy[i + 1][0].rgbtGreen +
                                copy[i - 1][1].rgbtGreen + copy[i][1].rgbtGreen + copy[i + 1][1].rgbtGreen) / 6.0);
        image[i][0].rgbtBlue = round((copy[i - 1][0].rgbtBlue + copy[i][0].rgbtBlue + copy[i + 1][0].rgbtBlue +
                                copy[i - 1][1].rgbtBlue + copy[i][1].rgbtBlue + copy[i + 1][1].rgbtBlue) / 6.0);
    }
    // right edge
    for (int i = 1; i < height -1; i++)
    {
        image[i][width - 1].rgbtRed = round((copy[i - 1][width - 1].rgbtRed + copy[i][width - 1].rgbtRed + copy[i + 1][width - 1].rgbtRed +
                                    copy[i - 1][width - 2].rgbtRed + copy[i][width - 2].rgbtRed + copy[i + 1][width - 2].rgbtRed) / 6.0);
        image[i][width - 1].rgbtGreen = round((copy[i - 1][width - 1].rgbtGreen + copy[i][width - 1].rgbtGreen + copy[i + 1][width - 1].rgbtGreen +
                                    copy[i - 1][width - 2].rgbtGreen + copy[i][width - 2].rgbtGreen + copy[i + 1][width - 2].rgbtGreen) / 6.0);
        image[i][width - 1].rgbtBlue = round((copy[i - 1][width - 1].rgbtBlue + copy[i][width - 1].rgbtBlue + copy[i + 1][width - 1].rgbtBlue +
                                    copy[i - 1][width - 2].rgbtBlue + copy[i][width - 2].rgbtBlue + copy[i + 1][width - 2].rgbtBlue) / 6.0);
    }
    //upper edge
    for (int j = 1; j < width -1; j++)
    {
        image[0][j].rgbtRed = round((copy[0][j - 1].rgbtRed + copy[0][j].rgbtRed + copy[0][j + 1].rgbtRed + copy[1][j - 1].rgbtRed + copy[1][j].rgbtRed + copy[1][j + 1].rgbtRed) / 6.0);
        image[0][j].rgbtGreen = round((copy[0][j - 1].rgbtGreen + copy[0][j].rgbtGreen + copy[0][j + 1].rgbtGreen + copy[1][j - 1].rgbtGreen + copy[1][j].rgbtGreen + copy[1][j + 1].rgbtGreen) / 6.0);
        image[0][j].rgbtBlue = round((copy[0][j - 1].rgbtBlue + copy[0][j].rgbtBlue + copy[0][j + 1].rgbtBlue + copy[1][j - 1].rgbtBlue + copy[1][j].rgbtBlue + copy[1][j + 1].rgbtBlue) / 6.0);
    }
    // lower edge
     for (int j = 1; j < width -1; j++)
    {
        image[height - 1][j].rgbtRed = round((copy[height - 1][j - 1].rgbtRed + copy[height - 1][j].rgbtRed + copy[height - 1][j + 1].rgbtRed + copy[height - 2][j - 1].rgbtRed + copy[height - 2][j].rgbtRed + copy[height - 2][j + 1].rgbtRed) / 6.0);
        image[height - 1][j].rgbtGreen = round((copy[height - 1][j - 1].rgbtGreen + copy[height - 1][j].rgbtGreen + copy[height - 1][j + 1].rgbtGreen + copy[height - 2][j - 1].rgbtGreen + copy[height - 2][j].rgbtGreen + copy[height - 2][j + 1].rgbtGreen) / 6.0);
        image[height - 1][j].rgbtBlue = round((copy[height - 1][j - 1].rgbtBlue + copy[height - 1][j].rgbtBlue + copy[height - 1][j + 1].rgbtBlue + copy[height - 2][j - 1].rgbtBlue + copy[height - 2][j].rgbtBlue + copy[height - 2][j + 1].rgbtBlue) / 6.0);
    }

    // midfield
    for (int i = 1; i < height - 2; i++)
    {
        for (int j = 1; j < width - 2; j++)
        {
            image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                        copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                        copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
            image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                        copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                        copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
            image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                        copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                        copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
        }
    }
    return;
}
