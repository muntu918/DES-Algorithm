#include <stdio.h>
#include <string.h>

void xorStrings(char *a, char *b, char *result, int len)
{
    for(int i = 0; i < len; i++)
    {
        result[i] = ((a[i] - '0') ^ (b[i] - '0')) + '0';
    }
    result[len] = '\0';
}

void feistelFunction(char *right, char *key, char *output)
{
    xorStrings(right, key, output, 32);
}

void desEncrypt(char *plaintext, char *key)
{
    char left[33], right[33];
    char temp[33], fOutput[33];

    strncpy(left, plaintext, 32);
    left[32] = '\0';

    strncpy(right, plaintext + 32, 32);
    right[32] = '\0';

    printf("Initial:\n");
    printf("L0 = %s\n", left);
    printf("R0 = %s\n\n", right);

    for(int round = 1; round <= 16; round++)
    {
        strcpy(temp, right);

        feistelFunction(right, key, fOutput);

        xorStrings(left, fOutput, right, 32);

        strcpy(left, temp);

        printf("Round %2d:\n", round);
        printf("L = %s\n", left);
        printf("R = %s\n\n", right);
    }

    printf("Ciphertext:\n");
    printf("%s%s\n", right, left);
}

int main()
{
    char plaintext[65] =
        "00000000000000000000000000000000"
        "11111111111111111111111111111111";

    char key[33] =
        "10101010101010101010101010101010";

    desEncrypt(plaintext, key);

    return 0;
}
