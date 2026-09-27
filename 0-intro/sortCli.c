#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n = argc - 1;   /* argv[0] is the program name */
    int *nums;
    int i, j, temp;

    if (n < 1)
    {
        printf("Usage: %s num1 num2 num3 ...\n", argv[0]);
        return 1;
    }

    nums = malloc(n * sizeof(int));
    if (nums == NULL)
    {
        printf("Out of memory\n");
        return 1;
    }

    /* Convert each argument from text to an int */
    for (i = 0; i < n; i++)
    {
        char *end;
        nums[i] = (int) strtol(argv[i + 1], &end, 10);
        if (*end != '\0')
        {
            printf("'%s' is not a valid integer\n", argv[i + 1]);
            free(nums);
            return 1;
        }
    }

    /* Bubble sort, ascending */
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    printf("Sorted: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    free(nums);
    return 0;
}