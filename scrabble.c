#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int scrabblevalue(string a);

int main(void)
{
    string a = get_string("Player 1: ");
    string b = get_string("Player 2: ");
    int x = scrabblevalue(a);
    int y = scrabblevalue(b);

    if (x > y)
        printf("Player 1 wins!\n");
    else if (y > x)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
    return 0;
}

int scrabblevalue(string a)
{
    int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int na = strlen(a);

    int x = 0;
    for (int i = 0; i < na; i++)
    {
        if (isupper(a[i]))
            x += POINTS[a[i] - 'A'];
        if (islower(a[i]))
            x += POINTS[a[i] - 'a'];
    }
    return x;
}
