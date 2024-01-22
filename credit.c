#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // as I use it for different operations, this number will be passed on to several variables, leaving this origianl one untouched
    long x = get_long("Please enter your credit card number for checking: ");

    // get digits
    int i = 0;
    long y = x;

    while (y > 0)
    {
        y = y / 10;
        i++;
    }

    // Luhn's test pt1 - multiply every 2nd digit starting from right by 2 and add the products
    long t1 = x;
    int sum1 = 0;
    int r1;
    int r2;

    while (t1 != 0)
    {
        r2 = 2 * ((t1 % 100) / 10); // picks the 2nd last digit and multiplies it by 2
        r1 = r2 % 10 + (r2 / 10);
        sum1 = sum1 + r1;
        t1 = t1 / 100; // shortens by 2 digits
    }

    // pt2 - get the other digits that weren't used
    long t2 = x;
    int sum2 = 0;
    int r3;
    while (t2 != 0)
    {
        r3 = t2 % 10; // picks the last digit
        sum2 = sum2 + r3;
        t2 = t2 / 100; // shortens by 2 digits
    }

    // pt3 - build the checksum
    int sum3 = sum1 + sum2;

    // check and provide output respectively
    if (sum3 % 10 == 0 && (i == 13 || i == 15 || i == 16))
    {
        if ((x / 100000000000000) >= 51 && (x / 100000000000000) <= 55)
            printf("MASTERCARD\n");
        else if ((x / 10000000000000) == 37 || (x / 10000000000000) == 34)
            printf("AMEX\n");
        else if ((x / 1000000000000) == 4 || (x / 1000000000000000) == 4)
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
}
