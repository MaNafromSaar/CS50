#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int wordcount(string a);
int lettercount(string a);
int sentencecount(string a);

int main(void)
{
    string a = get_string("Please provide the text that you want to have analyzed for readability: ");
    float L = ((float) lettercount(a) / wordcount(a)) * 100;
    float S = ((float) sentencecount(a) / wordcount(a)) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 1 && index < 16)
        printf("Grade %i\n", index);
    else
        printf("Grade 16+\n");
}

int lettercount(string a)
{
    int l = 0;
    int n = strlen(a);

    for (int i = 0; i < n; i++)
    {
        if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z'))
            l++;
    }
    return l;
}

int wordcount(string a)
{
    int w = 1;
    int n = strlen(a);

    for (int i = 0; i < n; i++)
    {
        if (a[i] == ' ')
            w++;
    }
    return w;
}

int sentencecount(string a)
{
    int s = 0;
    int n = strlen(a);

    for (int i = 0; i < n; i++)
    {
        if (a[i] == '.' || a[i] == '?' || a[i] == '!')
            s++;
    }
    return s;
}
