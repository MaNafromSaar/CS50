// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef int16_t SAMPLE; // sample size for cd quality - will differ for modern production!!!

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // copy header
    uint8_t header[HEADER_SIZE];

    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) < HEADER_SIZE)
    {
        printf("Failed to read header.\n");
        return 1; // handle error
    }

    if (fwrite(header, sizeof(uint8_t), HEADER_SIZE, output) < HEADER_SIZE)
    {
        printf("Failed to write header.\n");
        return 1; // handle error
    }

    // Read and manipulate samples

    SAMPLE s;

    while (fread(&s, sizeof(SAMPLE), 1, input)) // Use of functions in loops saves a lot of coding work but is not too easy to get.
    // Could be seen as: While this is viable - do it!
    {
        if (ferror(input)) // if anything goes wrong with the previous step (i.e reading from the file)
        {
            printf("Failed to read data.\n");
            return 1; // handle error
        }

        s *= factor; // change the volume

        if (!fwrite(&s, sizeof(SAMPLE), 1, output))
        // Relies on the logical structure of if: only False when antecedens True and consequens False
        // Thus could be read as: If writing is NOT Possible, put out the Error, otherwise, just go on writing
        {
            printf("Failed to write data.\n");
            return 1; // handle error
        }
    }

    // Close files
    fclose(input);
    fclose(output);
}
