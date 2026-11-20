// SS 2019, KPI FEI TUKE

#include "lstack.h"
#include "err.h"
#include <stdlib.h>
#include <stdio.h>

struct Node {
    PNode Next;
    TElem Elem;
};

struct LnkStack {
    PNode First;
    PNode Last;
};

int IsEmptyStack(LStack S)
{
    if (S == NULL) return 1; // NULL считаем пустым стеком
    return S->First == NULL;
}

LStack CreateStack(void)
{
    LStack S = malloc(sizeof(struct LnkStack));
    if (S == NULL) {
        printf("CreateStack: out of memory!\n");
        return NULL;
    }
    S->First = NULL;
    S->Last = NULL;
    return S;
}

void RemoveStack(LStack *PS)
{
    if (PS == NULL) {
        printf("RemoveStack: incorrect pointer!\n");
        return;
    }
    if (*PS == NULL) return;
    LStack S = *PS;
    MakeEmptyStack(S);
    free(S);
    *PS = NULL;
}

void MakeEmptyStack(LStack S)
{
    if (S == NULL) return;

    for (PNode PTop = S->First; !IsEmptyStack(S); )
    {
        PTop = S->First;
        if (S->First == S->Last)
            S->Last = NULL;
        S->First = S->First->Next;
        free(PTop);
    }
}

void Push(TElem X, LStack S)
{
    if (S == NULL) {
        printf("Push: incorrect stack!\n");
        return;
    }

    PNode PNew = malloc(sizeof(struct Node));
    if (PNew == NULL) {
        printf("Push: out of memory!\n");
        return;
    }

    PNew->Elem = X;
    PNew->Next = S->First;

    if (IsEmptyStack(S))
        S->Last = PNew;
    S->First = PNew;
}

TElem Top(LStack S)
{
    if (S == NULL || IsEmptyStack(S)) {
        printf("Top: empty stack with LStack size = 0\n");
        return 0; // безопасное значение
    }
    return S->First->Elem;
}

void Pop(LStack S)
{
    if (S == NULL || IsEmptyStack(S)) {
        printf("Pop: empty stack with LStack size = 0\n");
        return;
    }

    PNode PTop = S->First;
    if (S->First == S->Last) {
        S->First = S->Last = NULL;
    } else {
        S->First = PTop->Next;
    }
    free(PTop);
}

TElem TopAndPop(LStack S)
{
    TElem X = Top(S);
    Pop(S);
    return X;
}

void PrintStack(LStack S)
{
    if (S == NULL) {
        printf("PrintStack: incorrect stack!\n");
        return;
    }

    if (IsEmptyStack(S)) {
        printf("Empty stack");
        return;
    }

    printf("Top> ");
    for (PNode PTmp = S->First; PTmp != NULL; PTmp = PTmp->Next)
        printf("%d ", PTmp->Elem);
}
