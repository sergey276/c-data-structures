// SS 2019, KPI FEI TUKE

#include "lqueue.h"
#include "err.h"
#include <stdlib.h>
#include <stdio.h>

// ==== Štruktúry ====
struct Node {
    PNode Next;
    TElem Elem;
};

struct LnkQueue {
    PNode Front;
    PNode Rear;
};

// ==== Implementácia funkcií ====

int IsEmptyQueue(LQueue Q) {
    return (!Q || !Q->Front) ? 1 : 0;
}

LQueue CreateQueue(void) {
    LQueue Q = malloc(sizeof(struct LnkQueue));
    if (!Q) {
        Error("CreateQueue: out of memory!");
    }
    Q->Front = Q->Rear = NULL;
    return Q;
}

void MakeEmptyQueue(LQueue Q) {
    if (!Q) return;
    for (; Q->Front;) {
        PNode t = Q->Front;
        Q->Front = Q->Front->Next;
        free(t);
    }
    Q->Rear = NULL;
}

void RemoveQueue(LQueue *PQ) {
    if (!PQ || !*PQ) return;
    MakeEmptyQueue(*PQ);
    free(*PQ);
    *PQ = NULL;
}

void Enqueue(TElem X, LQueue Q) {
    if (!Q) return;
    PNode N = malloc(sizeof(struct Node));
    if (!N) Error("Enqueue: out of memory!");
    N->Elem = X;
    N->Next = NULL;

    Q->Rear ? (Q->Rear->Next = N) : (Q->Front = N);
    Q->Rear = N;
}

TElem Front(LQueue Q) {
    // bezpečná verzia - neukončuje program
    return (Q && Q->Front) ? Q->Front->Elem : 0;
}

void Dequeue(LQueue Q) {
    if (!Q || !Q->Front) return;
    PNode T = Q->Front;
    Q->Front = Q->Front->Next;
    if (!Q->Front) Q->Rear = NULL;
    free(T);
}

TElem FrontAndDequeue(LQueue Q) {
    TElem X = Front(Q);
    Dequeue(Q);
    return X;
}

void PrintQueue(LQueue Q) {
    if (!Q || !Q->Front) {
        printf("Empty queue");
        return;
    }
    for (PNode p = Q->Front; p; p = p->Next)
        printf("%d ", p->Elem);
}
