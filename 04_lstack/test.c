#include <stdio.h>
#include "lstack.h"

int main(void) {
    LStack stackA = CreateStack();
    LStack stackB = CreateStack();

    printf("=== Linked stack test ===\n");

    printf("\nPushing elements to stack A and stack B...\n");
    for (int i = 10; i <= 60; i += 10) {
        Push(i, stackA);
        Push(i + 1, stackB);
        printf("Pushed: %d and %d\n", i, i + 1);
    }

    printf("\nStack A: ");
    PrintStack(stackA);
    printf("\nStack B: ");
    PrintStack(stackB);

    printf("\n\nTop of A = %d\n", Top(stackA));
    printf("Top of B = %d\n", Top(stackB));

    printf("\nPopping everything from A...\n");
    while (!IsEmptyStack(stackA)) {
        printf("Popped: %d\n", TopAndPop(stackA));
    }

    printf("\nAfter popping:\n");
    printf("Stack A: ");
    PrintStack(stackA);
    printf("\nStack B: ");
    PrintStack(stackB);

    printf("\n\nEmptying stack B with MakeEmptyStack...\n");
    MakeEmptyStack(stackB);
    printf("Stack B: ");
    PrintStack(stackB);

    printf("\n\nRemoving both stacks...\n");
    RemoveStack(&stackA);
    RemoveStack(&stackB);

    printf("=== Test finished ===\n");
    return 0;
}
