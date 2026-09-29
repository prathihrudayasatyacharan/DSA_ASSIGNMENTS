#include <stdio.h>

void display(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int a[100], n;
    int i, j, key;
    int shifts = 0;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("Enter student marks:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nOriginal array:\n");
    display(a, n);

    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            shifts++;
            j--;
        }

        a[j + 1] = key;

        printf("After pass %d: ", i);
        display(a, n);
    }

    printf("\nFinal sorted array: ");
    display(a, n);

    printf("Total number of element shifts: %d\n", shifts);

    return 0;
}
