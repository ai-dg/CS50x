#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Variables declaration
    long credit;
    long credit_reduc;
    long digits;
    int i;
    int sum1;
    int sum2;
    int total_sum;
    int tmp;

    // Variables initialization
    i = 0;
    sum1 = 0;
    sum2 = 0;
    total_sum = 0;
    tmp = 0;

    // Inupt data
    do
    {
        credit = get_long("Number: ");
    }
    while (credit < 0);

    // Calculate checksum
    for (credit_reduc = credit; credit_reduc > 0; credit_reduc /= 10)
    {
        i++;
        digits = credit_reduc % 10;
        // Checksum with odd number
        if (i % 2 == 0)
        {
            // If we have nbr > 10 as an answer of digit * 2, we  apply modulo
            if ((digits * 2) >= 10)
            {
                sum1 = sum1 + (digits * 2) / 10;
                sum1 = sum1 + (digits * 2) % 10;
            }
            if ((digits * 2) < 10)
            {
                sum1 = sum1 + (digits * 2);
            }
        }
        // Checksum with pair number
        if (i % 2 != 0)
        {
            sum2 = sum2 + digits;
        }
        // Store the first two numbers of input to check card and starting digits
        if (credit_reduc > 10 && credit_reduc < 100)
        {
            tmp = credit_reduc;
        }
    }

    // Check card and starting digits
    total_sum = sum1 + sum2;
    if (total_sum % 10 != 0 || !(i >= 13 && i <= 16))
    {
        printf("INVALID\n");
    }
    else if ((i >= 13 && i <= 16) && (tmp >= 40 && tmp <= 42))
    {
        printf("VISA\n");
    }
    else if (i == 15 && (tmp == 34 || tmp == 37))
    {
        printf("AMEX\n");
    }
    else if (i == 16 && (tmp >= 51 && tmp <= 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
