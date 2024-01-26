#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// starting alphabet and fixed length
const int N = 26;
char alphabet[N + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    // checking the key
    if (argc != 2)
    {
        printf("Only one command line argument. It must contain 26 distinct characters.\n");
        return 1;
    }
    for (int i = 0; i < N; i++)
    {
        if (strlen(argv[1]) != N)
        {
            printf("Your key must contain 26 characters.\n");
            return 1;
        }

        for (int j = 0; j < i; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("The letters must be unique.\n");
                return 1;
            }
        }

        if (!isalpha(argv[1][i]))
        {
            printf("Your key must only contain letters.\n");
            return 1;
        }

        // generate key
        else
        {
            alphabet[i] = toupper(argv[1][i]);
        }
    }
    // get input
    int c = 0;
    string plain = get_string("Please now enter the text you would want to encode: ");
    int n = strlen(plain);

    // apply alphabet and output encrypted text
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        if (islower(plain[i]))
        {
            c = plain[i] - 'a';
            printf("%c", tolower(alphabet[c]));
        }
        else if (isupper(plain[i]))
        {
            c = plain[i] - 'A';
            printf("%c", toupper(alphabet[c]));
        }
        else
        {
            printf("%c", plain[i]); // ignore any non-letter chars
        }
    }
    printf("\n");
    return 0;
}
