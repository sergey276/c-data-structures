#include "err.h"
#include "tree_arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeRecord
{
    int MaxLevel;
    int *Array;
};

Tree CreateTree(int MaxLevel)
{
    if(MaxLevel < 1) Error("MaxLevel must be >= 1");

    Tree T = malloc(sizeof(struct TreeRecord));
    if(T == NULL) Error("Out of space!!!");

    int size = (int)pow(2, MaxLevel + 1);
    T->Array = calloc(size, sizeof(int));
    if(T->Array == NULL) {
        free(T);
        Error("Out of space!!!");
    }

    T->MaxLevel = MaxLevel;
    return T;
}

void MakeEmpty(Tree T)
{
    if(T == NULL) { printf("Error\n"); return; }
    if(T->Array == NULL) { printf("Error\n"); return; }

    int size = (int)pow(2, T->MaxLevel + 1);
    for(int i = 0; i < size; i++) T->Array[i] = 0;
}

void Insert(Tree T, int Index, int Elem)
{
    if(T == NULL || T->Array == NULL) { printf("Error\n"); return; }

    int maxIndex = (int)pow(2, T->MaxLevel + 1) - 1;
    if(Index < 1 || Index > maxIndex) { printf("Error\n"); return; }

    T->Array[Index] = Elem;
}

void DisposeTree(Tree T)
{
    if(T != NULL) {
        if(T->Array != NULL) free(T->Array);
        free(T);
    }
}

void PrintSpaces(int Count)
{
    while(Count-- > 0) putchar(' ');
}

void PrintTree(Tree T)
{
    if(T == NULL || T->Array == NULL) { printf("Error\n"); return; }

    int k = 1;
    int maxIndex = (int)pow(2, T->MaxLevel + 1);

    for(int level = 1; level <= T->MaxLevel + 1; level++) {
        int nodes = (int)pow(2, level - 1);
        int spaces = (4 * (int)pow(2, T->MaxLevel) - 2 * nodes) / nodes;

        for(int j = 0; j < nodes && k < maxIndex; j++) {
            if(j == 0) PrintSpaces(spaces - spaces / 2);
            else PrintSpaces(spaces);

            if(T->Array[k] != 0) printf("%02d", T->Array[k]);
            else printf("..");
            k++;
        }
        putchar('\n');
    }
}

void PrintRow(Tree T, int Level)
{
    if(T == NULL || T->Array == NULL) { printf("Error\n"); return; }
    if(Level < 0 || Level > T->MaxLevel) { printf("Error\n"); return; }

    int start = (int)pow(2, Level);
    int end = (int)pow(2, Level + 1);
    int maxIndex = (int)pow(2, T->MaxLevel + 1);

    for(int i = start; i < end && i < maxIndex; i++) {
        if(T->Array[i] != 0) printf("%02d ", T->Array[i]);
    }
    putchar('\n');
}

static void PrintSubtreeRec(Tree T, int Index)
{
    if(T == NULL || T->Array == NULL) return;

    int maxIndex = (int)pow(2, T->MaxLevel + 1);
    if(Index <= 0 || Index >= maxIndex || T->Array[Index] == 0) return;

    printf("%02d ", T->Array[Index]);
    PrintSubtreeRec(T, 2 * Index);     // левый потомок
    PrintSubtreeRec(T, 2 * Index + 1); // правый потомок
}

void PrintSubtree(Tree T, int Index)
{
    if(T == NULL || T->Array == NULL) { printf("Error\n"); return; }

    int maxIndex = (int)pow(2, T->MaxLevel + 1) - 1;
    if(Index <= 0 || Index > maxIndex || T->Array[Index] == 0) { printf("Error\n"); return; }

    PrintSubtreeRec(T, Index);
    putchar('\n');
}

void BuildHeap(Tree T)
{
    if(T == NULL || T->Array == NULL) return;

    int n = (int)pow(2, T->MaxLevel + 1) - 1;

    for(int i = n / 2; i >= 1; i--) {
        int parent = i;
        while(2 * parent <= n) {
            int child = 2 * parent;
            if(child + 1 <= n && T->Array[child + 1] > T->Array[child])
                child++;
            if(T->Array[parent] >= T->Array[child]) break;
            int tmp = T->Array[parent];
            T->Array[parent] = T->Array[child];
            T->Array[child] = tmp;
            parent = child;
        }
    }
}
