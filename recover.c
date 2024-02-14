#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 1 Argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Open memcard
    FILE *card = fopen(argv[1], "r");
    if (card == 0)
    {
        printf("Could not open medium.\n");
        return 3;
    }

    // create a buffer for a block (fat32)
    uint8_t buffer[512];

    // as long there is mem left to read, do so
    FILE *img = 0;
    char *filename = 0;
    int i = 0;
    while (fread(buffer, 1, 512, card) == 512)
    {
        // if you run into the header: (jump to line 54)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // Bitwise eliminating the last 4 bytes, then compare
        {
            if (img != 0) //close the file if you were already working on a *.jpg
            {
                fclose(img);
                free(filename);
            }

            // alloc mem for the filename
            filename = malloc(9 * sizeof(char));
            sprintf(filename, "%03i.jpg", i); // format of the filename, increments with i

            // open the new file in write mode
            img = fopen(filename, "w");
            if (img == 0)
            {
                printf("Could not open %s.\n", filename);
                free(filename);
                return 2;
            }
            i++;
        }
        // go on writing
        if (img != 0)
            fwrite(buffer, 512, 1, img);
    }

    if (img != 0) // close the very last *.jpg (you won't return to the while loop and find another jpg header)
    {
        fclose(img);
        free(filename);
    }
    // close mem card!!!
    fclose(card);
    return 0;
    // remember to free and fclose everything in all possible cases!
}
