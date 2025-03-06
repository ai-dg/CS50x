#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 512
#define BOOL bool

typedef uint8_t BYTE;

BOOL is_jpeg(BYTE buffer[BLOCK_SIZE])
{
    // Conditions to detect the JPEG header
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        return (true);
    return (false);
}

int main(int argc, char *argv[])
{
    // Openning of .raw file and condition if in case of error
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("File not found\n");
        return (1);
    }

    // Initialize and declaration of BUFFER
    BYTE buffer[BLOCK_SIZE];

    // Filename, count and FILE *img pointer declaration
    FILE *img = NULL;
    char filename[8];
    int count = 0;

    while (fread(buffer, BLOCK_SIZE, 1, raw_file))
    {
        // Check JPEG header
        if (is_jpeg(buffer))
        {
            // Close IMG to create new one
            if (img != NULL)
                fclose(img);
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }
        // Writing img content by the buffer
        if (img != NULL)
            fwrite(buffer, BLOCK_SIZE, 1, img);
    }
    fclose(img);
    fclose(raw_file);
    return (0);
}
