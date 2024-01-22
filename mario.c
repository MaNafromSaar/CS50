#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    do
    {
        n = get_int("Height: "); // get input in a reasonable range
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < (n - (i + 1)); k++) // number of blanks before hashs start
        {
            printf(" ");
        }
        for (int l = 0; l <= i; l++) // increasing number of #
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l <= i; l++) // static blank
        {
            printf("#");
        }
        printf("\n");
    }
}