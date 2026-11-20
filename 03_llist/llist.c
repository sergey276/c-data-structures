// SS 2019, KPI FEI TUKE

#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "err.h"

/* ==== Структуры ==== */

struct Node {
    PNode Next;
    TElem Elem;
};

struct LnkList {
    PNode First;
    PNode Last;
};

/* ==== Основные функции ==== */

LList MakeEmpty(LList L) {
    if (L != NULL) {
        RemoveList(&L);
    }

    LList PL = (LList) malloc(sizeof(struct LnkList));
    if (PL == NULL) {
        Error("MakeEmpty: out of memory!");
    }

    PL->First = NULL;
    PL->Last  = NULL;
    return PL;
}

void RemoveList(LList *PL) {
    if (PL == NULL) {
        Error("RemoveList: incorrect pointer!");
    }

    LList L = *PL;
    if (L == NULL) return;

    PNode P = L->First;
    while (P != NULL) {
        PNode T = P->Next;
        free(P);
        P = T;
    }

    free(L);
    *PL = NULL;
}

void Delete(TElem X, LList L) {
    if (L == NULL) {
        Error("Delete: incorrect list!");
    }

    if (!Member(X, L)) return;

    PNode P = L->First;
    PNode C = L->First;

    while (C != NULL) {
        if (C->Elem == X) {
            if (C->Next == NULL)
                L->Last = P;
            if (C->Next == NULL && P == C)
                L->Last = NULL;
            if (P == C)
                L->First = C->Next;
            else
                P->Next = C->Next;

            free(C);
            break;
        }
        P = C;
        C = C->Next;
    }
}

int IsEmpty(LList L) {
    if (L == NULL) {
        Error("IsEmpty: incorrect list!");
    }
    return L->First == NULL;
}

int IsLast(PNode P) {
    if (P == NULL) {
        Error("IsLast: incorrect pointer on input!");
    }
    return P->Next == NULL;
}

PNode Member(TElem X, LList L) {
    if (L == NULL) {
        Error("Member: incorrect list!");
    }

    PNode P = L->First;
    while (P != NULL) {
        if (P->Elem == X) break;
        P = P->Next;
    }
    return P;
}

void InsertBeg(TElem X, LList L) {
    if (L == NULL) {
        Error("InsertBeg: incorrect list!");
    }

    PNode T = (PNode) malloc(sizeof(struct Node));
    if (T == NULL) {
        Error("InsertBeg: out of memory!");
    }

    T->Elem = X;
    T->Next = L->First;

    if (IsEmpty(L))
        L->Last = T;

    L->First = T;
}

void InsertEnd(TElem X, LList L) {
    if (L == NULL) {
        Error("InsertEnd: incorrect list!");
    }

    PNode T = (PNode) malloc(sizeof(struct Node));
    if (T == NULL) {
        Error("InsertEnd: out of memory!");
    }

    T->Elem = X;
    T->Next = NULL;

    if (IsEmpty(L)) {
        L->First = T;
        L->Last  = T;
    } else {
        L->Last->Next = T;
        L->Last = T;
    }
}

/* ==== Дополнительные функции ==== */

PNode First(LList L) {
    if (L == NULL) {
        Error("First: incorrect list!");
    }
    return L->First;
}

PNode Next(PNode P) {
    if (P == NULL) {
        Error("Next: incorrect pointer on input!");
    }
    return P->Next;
}

LList Head(LList L) {
    return L;
}

TElem Get(PNode P) {
    if (P == NULL) {
        Error("Get: incorrect pointer on input!");
    }
    return P->Elem;
}

void PrintList(LList L) {
    if (L == NULL) {
        printf("PrintList: incorrect list!\n");
        return;
    }

    if (IsEmpty(L)) {
        printf("Empty list");
        return;
    }

    PNode P = First(L);
    while (P != NULL) {
        printf("%d ", Get(P));
        P = Next(P);
    }
}

/* ==== Реализация дополнительных операций ==== */

void InsertPos(TElem X, PNode P, LList L) {
    if (L == NULL) {
        Error("InsertPos: incorrect list!");
    }
    if (P == NULL) {
        Error("InsertPos: incorrect position!");
    }

    PNode T = (PNode) malloc(sizeof(struct Node));
    if (T == NULL) {
        Error("InsertPos: out of memory!");
    }

    T->Elem = X;
    T->Next = P->Next;
    P->Next = T;

    if (L->Last == P)
        L->Last = T;
}

int ListSize(LList L) {
    if (L == NULL) {
        Error("ListSize: incorrect list!");
    }

    int count = 0;
    PNode P = L->First;
    while (P != NULL) {
        count++;
        P = P->Next;
    }
    return count;
}void FastCat(LList L1, LList L2) {
    if (L1 == NULL || L2 == NULL) {
        Error("FastCat: incorrect list!");
    }

    /* Если L2 пуст — ничего не делаем */
    if (IsEmpty(L2)) return;

    /* Если L1 пуст — просто переназначаем ссылки */
    if (IsEmpty(L1)) {
        L1->First = L2->First;
        L1->Last  = L2->Last;
    } else {
        /* иначе прицепляем L2 к концу L1 */
        L1->Last->Next = L2->First;
        L1->Last = L2->Last;
    }

    /* L2 становится пустым */
    L2->First = NULL;
    L2->Last  = NULL;
}

LList FreshCat(LList L1, LList L2) {
    if (L1 == NULL || L2 == NULL) {
        Error("FreshCat: incorrect list!");
    }

    LList NewList = MakeEmpty(NULL);

    PNode P = First(L1);
    while (P != NULL) {
        InsertEnd(Get(P), NewList);
        P = Next(P);
    }

    P = First(L2);
    while (P != NULL) {
        InsertEnd(Get(P), NewList);
        P = Next(P);
    }

    return NewList;
}

LList Cut(LList L, PNode P) {
    if (L == NULL) {
        Error("Cut: incorrect list!");
    }
    if (P == NULL) {
        Error("Cut: incorrect node!");
    }

    LList NewList = MakeEmpty(NULL);

    /* если после P нет элементов — возвращаем пустой список */
    if (P->Next == NULL) return NewList;

    NewList->First = P->Next;
    NewList->Last  = L->Last;

    P->Next = NULL;
    L->Last = P;

    return NewList;
}