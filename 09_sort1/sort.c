#include <stdio.h>
#include "sort.h"

/* =============================
        PRINT ARRAY
   ============================= */

void PrintArray(int a[], int n, int prechod){
    for (int j = 1; j <= n; j++)
        printf("%2d ", a[j]);
    printf("\n");
}


/* =============================
          BUBBLE SORT
   ============================= */

void bubbleSort(int a[], int n, int dir)
{
    if (n <= 0) return;

    for (int i = 1; i <= n; i++)
    {
        for (int j = n; j >= i + 1; j--)
        {
            if (dir == ASC)
            {
                if (a[j - 1] > a[j])
                {
                    int tmp = a[j - 1];
                    a[j - 1] = a[j];
                    a[j] = tmp;
                }
            }
            else
            {
                if (a[j - 1] < a[j])
                {
                    int tmp = a[j - 1];
                    a[j - 1] = a[j];
                    a[j] = tmp;
                }
            }
        }
        PrintArray(a, n, i);
    }
}


/* =============================
           INSERT SORT
   ============================= */

void insertSort(int A[], int n, int dir)
{
    if (n <= 0) return;     // Fix empty test

    PrintArray(A, n, 0);    // Initial print

    for (int i = 2; i <= n; i++)
    {
        int value = A[i];
        int j = i - 1;

        if (dir == ASC)
        {
            while (j >= 1 && A[j] > value)
            {
                A[j + 1] = A[j];
                j--;
            }
        }
        else
        {
            while (j >= 1 && A[j] < value)
            {
                A[j + 1] = A[j];
                j--;
            }
        }

        A[j + 1] = value;

        PrintArray(A, n, i - 1);
    }
}


/* =============================
         SELECTION SORT
   ============================= */

void selectionSort(int a[], int n, int dir)
{
    if (n <= 0) return;

    PrintArray(a, n, 0);   // Initial state printed as step 0

    for (int i = 1; i <= n - 1; i++)
    {
        int idx = i;

        // Correct TUKE logic: search minimum in interval [i..n]
        for (int j = i; j <= n; j++)
        {
            if (dir == ASC)
            {
                if (a[j] < a[idx])
                    idx = j;
            }
            else
            {
                if (a[j] > a[idx])
                    idx = j;
            }
        }

        int tmp = a[i];
        a[i] = a[idx];
        a[idx] = tmp;

        PrintArray(a, n, i);  // Print after each swap
    }
}

