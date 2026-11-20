#include <stdio.h>
#include "lqueue.h"

int main(void) {
    printf("=== ADT Queue Test ===\n");

    // Vytvorenie dvoch frontov
    LQueue Q1 = CreateQueue();
    LQueue Q2 = CreateQueue();

    printf("\nVkladanie prvkov do frontov...\n");
    for (int i = 1; i <= 5; i++) {
        Enqueue(i, Q1);
        Enqueue(i * 10, Q2);
    }

    printf("\nObsah Q1:\n");
    PrintQueue(Q1);
    printf("\nObsah Q2:\n");
    PrintQueue(Q2);

    printf("\nPredný prvok Q1: %d\n", Front(Q1));
    printf("Predný prvok Q2: %d\n", Front(Q2));

    printf("\nOdoberanie prvkov z Q1 pomocou FrontAndDequeue:\n");
    while (!IsEmptyQueue(Q1)) {
        printf("Odobrané: %d\n", FrontAndDequeue(Q1));
    }

    printf("\nPo vyprázdnení Q1:\n");
    PrintQueue(Q1);

    printf("\nVyprázdňujeme Q2 pomocou MakeEmptyQueue...\n");
    MakeEmptyQueue(Q2);
    PrintQueue(Q2);

    printf("\nOdstraňujeme fronty...\n");
    RemoveQueue(&Q1);
    RemoveQueue(&Q2);

    printf("\n=== Test úspešne dokončený ===\n");
    return 0;
}


