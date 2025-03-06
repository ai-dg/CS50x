#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    int end;
    int years;
    int gain;
    int lose;
    int total_llamas;

    years = 0;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    total_llamas = start;
    while (total_llamas < end)
    {
        gain = (total_llamas / 3);
        lose = (total_llamas / 4);
        total_llamas = total_llamas + gain - lose;
        years++;
    }
    printf("Years: %i\n", years);
}
