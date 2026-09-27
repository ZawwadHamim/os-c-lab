#include <stdio.h>

int main(int argc, char *argv[])
{
    char filename[256];
    FILE *fp;
    int ch;   /* int, not char, so it can hold EOF */

    /* Use filename from command line, or ask for one */
    if (argc > 1)
    {
        fp = fopen(argv[1], "r");
    }
    else
    {
        printf("Enter file name: ");
        if (scanf("%255s", filename) != 1)
        {
            return 1;
        }
        fp = fopen(filename, "r");
    }

    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    /* Read one character at a time until End Of File */
    while ((ch = fgetc(fp)) != EOF)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            putchar(ch);
        }
    }
    putchar('\n');

    fclose(fp);
    return 0;
}