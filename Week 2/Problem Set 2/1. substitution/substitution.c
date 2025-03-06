#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    char alph1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char alph2[] = "abcdefghijklmnopqrstuvwxyz";
    int x;
    int y;
    char *plaintext;
    char *ciphertext;
    char *cipher;
    char tmp;

    x = 0;
    y = 0;
    // Input check
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    while (argv[1][x])
    {
        y = 0;
        if (!(argv[1][x] >= 'A' && argv[1][x] <= 'Z') && !(argv[1][x] >= 'a' && argv[1][x] <= 'z'))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        x++;
    }
    if (x != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    x = 0;
    while (argv[1][x])
    {
        y = x + 1;
        tmp = argv[1][x];
        while (argv[1][y])
        {
            if (tmp == argv[1][y + 1])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
            y++;
        }
        x++;
    }

    plaintext = get_string("plaintext: ");
    ciphertext = plaintext;
    cipher = argv[1];
    x = 0;
    y = 0;

    // Loop of word
    while (ciphertext[x] != '\0')
    {
        y = 0;
        if (ciphertext[x] >= 'A' && ciphertext[x] <= 'Z')
        {
            // alph1 check
            while (alph1[y])
            {
                if (alph1[y] == ciphertext[x])
                {
                    // New alpha index modification
                    if (cipher[y] >= 'A' && cipher[y] <= 'Z')
                        ciphertext[x] = cipher[y] + 32;
                    else if (cipher[y] >= 'a' && cipher[y] <= 'z')
                        ciphertext[x] = cipher[y];
                }
                y++;
            }
        }
        else if (ciphertext[x] >= 'a' && ciphertext[x] <= 'z')
        {
            // alph2 check
            while (alph2[y])
            {
                if (alph2[y] == ciphertext[x])
                {
                    // New alpha index modification
                    if (cipher[y] >= 'A' && cipher[y] <= 'Z')
                        ciphertext[x] = cipher[y];
                    else if (cipher[y] >= 'a' && cipher[y] <= 'z')
                        ciphertext[x] = cipher[y] - 32;
                }
                y++;
            }
        }
        x++;
    }

    x = 0;
    // Upperalpha loweralpha
    while (ciphertext[x])
    {
        if (ciphertext[x] >= 'A' && ciphertext[x] <= 'Z')
        {
            ciphertext[x] += 32;
        }
        else if (ciphertext[x] >= 'a' && ciphertext[x] <= 'z')
        {
            ciphertext[x] -= 32;
        }
        x++;
    }
    printf("ciphertext: %s\n", ciphertext);
    return (0);
}
