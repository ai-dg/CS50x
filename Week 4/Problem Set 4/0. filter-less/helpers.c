#include "helpers.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Float number to get the correct value at the end of the algorithm
    float average;

    int average_rounded;
    // Loop cycle to get average number and for remplacing values in the
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            average = ((float) (image[x][y].rgbtBlue + image[x][y].rgbtGreen + image[x][y].rgbtRed) / 3);
            average_rounded = (int) (average + 0.5);
            image[x][y].rgbtBlue = average_rounded;
            image[x][y].rgbtGreen = average_rounded;
            image[x][y].rgbtRed = average_rounded;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Values searching to get the average number
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            sepiaRed = ((image[x][y].rgbtBlue * 0.189) + (image[x][y].rgbtGreen * 0.769) + (image[x][y].rgbtRed * 0.393) + 0.5);
            sepiaGreen = ((image[x][y].rgbtBlue * 0.168) + (image[x][y].rgbtGreen * 0.686) + (image[x][y].rgbtRed * 0.349) + 0.5);
            sepiaBlue = ((image[x][y].rgbtBlue * 0.131) + (image[x][y].rgbtGreen * 0.534) + (image[x][y].rgbtRed * 0.272) + 0.5);
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;
            image[x][y].rgbtRed = sepiaRed;
            image[x][y].rgbtGreen = sepiaGreen;
            image[x][y].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp;
    int width_temp = 0;

    for (int x = 0; x < height; x++)
    {

        for (int y = 0; y < (width) / 2; y++)
        {
            width_temp = width - 1 - y;

            temp = image[x][y].rgbtRed;
            image[x][y].rgbtRed = image[x][width_temp].rgbtRed;
            image[x][width_temp].rgbtRed = temp;

            temp = image[x][y].rgbtGreen;
            image[x][y].rgbtGreen = image[x][width_temp].rgbtGreen;
            image[x][width_temp].rgbtGreen = temp;

            temp = image[x][y].rgbtBlue;
            image[x][y].rgbtBlue = image[x][width_temp].rgbtBlue;
            image[x][width_temp].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float somme_red = 0;
    float somme_green = 0;
    float somme_blue = 0;

    float somme_red_rounded = 0;
    float somme_green_rounded = 0;
    float somme_blue_rounded = 0;

    int nbr_elements = 0;

    int width_temp = width;
    int height_temp = height;

    RGBTRIPLE imagecpy[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
            imagecpy[x][y] = image[x][y];
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            nbr_elements = 0;
            somme_red = 0;
            somme_green = 0;
            somme_blue = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int dx = a + x;
                    int dy = b + y;

                    if (dx >= 0 && dx < height && dy >= 0 && dy < width)
                    {
                        somme_red += imagecpy[dx][dy].rgbtRed;
                        somme_green += imagecpy[dx][dy].rgbtGreen;
                        somme_blue += imagecpy[dx][dy].rgbtBlue;
                        nbr_elements++;
                    }
                }
            }

            if (nbr_elements > 0)
            {
                somme_red_rounded = (somme_red / (float) nbr_elements);
                somme_green_rounded = (somme_green / (float) nbr_elements);
                somme_blue_rounded = (somme_blue / (float) nbr_elements);

                image[a][b].rgbtRed = (int) (somme_red_rounded + 0.5);
                image[a][b].rgbtGreen = (int) (somme_green_rounded + 0.5);
                image[a][b].rgbtBlue = (int) (somme_blue_rounded + 0.5);
            }
        }
    }

    return;
}
