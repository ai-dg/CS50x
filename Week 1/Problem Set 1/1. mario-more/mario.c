#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // List of variables
    int n;
    int x;
    int y;
    int z;

    x = 0;
    y = 0;

    // Declaration of n, limited beetwen 1 and 8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Initialization of z to be modified in the loop
    z = n;

    // Mario loop !
    for (int i = 0; i < n; i++)
    {
        x = y;

        for (int j = z - 2; j >= 0; j--)
        {
            printf(" ");
        }
        for (x = y; x >= 0; x--)
        {
            printf("#");
        }
        printf("  ");
        for (x = y; x >= 0; x--)
        {
            printf("#");
        }
        printf("\n");
        z--;
        y++;
    }
}
