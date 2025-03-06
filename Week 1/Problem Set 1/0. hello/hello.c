#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Declaration and initialization of the variable type string
    string name = get_string("What is your name?\n");
    // Printf function with library stdio.h
    printf("hello, %s\n", name);
}
