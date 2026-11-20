

#include "BVS.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct BVSNode
{
    int Item;
    PtrBVSNode Left;
    PtrBVSNode Right;
};

// vytvori BVS vrchol so zadanou polozkou (0-99)
PtrBVSNode BVSCreateNode(int ItemToInsert)
{
    PtrBVSNode BVS;
    BVS = malloc(sizeof(struct BVSNode));
    if(BVS == NULL) { printf("\nOut of memory!"); exit(-1); }
    if(ItemToInsert < 0 || ItemToInsert > 99) {
        printf("\nBVSCreateNode: invalid item (0-99): %d!", ItemToInsert);
        return NULL;
    }
    BVS->Item = ItemToInsert;
    BVS->Left = NULL;
    BVS->Right = NULL;
    return BVS;
}

// vytvori strom BVS
PtrBVSNode BVSCreateTree(int ItemToInsert)
{
    return BVSCreateNode(ItemToInsert);
}

// vlozi polozku do stromu
PtrBVSNode BVSInsert(PtrBVSNode Root, int ItemToInsert)
{
    if(Root == NULL) return BVSCreateNode(ItemToInsert);
    if(ItemToInsert < Root->Item)
        Root->Left = BVSInsert(Root->Left, ItemToInsert);
    else if(ItemToInsert > Root->Item)
        Root->Right = BVSInsert(Root->Right, ItemToInsert);
    return Root;
}

// najde ci polozka existuje
int BVSMember(PtrBVSNode Root, int ItemToFind)
{
    PtrBVSNode current = Root;
    while(current != NULL)
    {
        if(ItemToFind == current->Item)
            return 1;
        else if(ItemToFind < current->Item)
            current = current->Left;
        else
            current = current->Right;
    }
    return 0;
}

// INORDER (L,U,R)
void BVSPrintInOrder(PtrBVSNode Root)
{
    if(Root == NULL) return;
    BVSPrintInOrder(Root->Left);
    MyPrintf("%d ", Root->Item);
    BVSPrintInOrder(Root->Right);
}

// PREORDER (U,L,R)
void BVSPrintPreOrder(PtrBVSNode Root)
{
    if(Root == NULL) return;
    MyPrintf("%d ", Root->Item);
    BVSPrintPreOrder(Root->Left);
    BVSPrintPreOrder(Root->Right);
}

// POSTORDER (L,R,U)
void BVSPrintPostOrder(PtrBVSNode Root)
{
    if(Root == NULL) return;
    BVSPrintPostOrder(Root->Left);
    BVSPrintPostOrder(Root->Right);
    MyPrintf("%d ", Root->Item);
}

// pocet uzlov v strome
int BVSTreeSize(PtrBVSNode Root)
{
    if(Root == NULL) return 0;
    return 1 + BVSTreeSize(Root->Left) + BVSTreeSize(Root->Right);
}

int BVSGetLevel(PtrBVSNode Root, int Level)
{
    int LMax = Level, RMax = Level;
    if(Root->Left != NULL) LMax = BVSGetLevel(Root->Left, Level+1);
    if(Root->Right != NULL) RMax = BVSGetLevel(Root->Right, Level+1);
    return (LMax > RMax) ? LMax : RMax;
}

int BVSGetMaxLevel(PtrBVSNode Root)
{
    if(Root == NULL) return 0;
    return BVSGetLevel(Root, 1);
}

void BVSPrintLevel(PtrBVSNode Root, int LevelToPrint, int StartLevel)
{
    if(Root == NULL) return;
    if(LevelToPrint == StartLevel) printf("%d ", Root->Item);
    if(Root->Left != NULL) BVSPrintLevel(Root->Left, LevelToPrint, StartLevel+1);
    if(Root->Right != NULL) BVSPrintLevel(Root->Right, LevelToPrint, StartLevel+1);
}

void BVSPrintLevelOrder(PtrBVSNode Root)
{
    if(Root == NULL) return;
    int MaxLevel = BVSGetMaxLevel(Root);
    for(int i = 1; i <= MaxLevel; i++)
        BVSPrintLevel(Root, i, 1);
}

int BVSGetMinItem(PtrBVSNode Root)
{
    if(Root == NULL) { printf("\nNo Tree!"); exit(-1); }
    if(Root->Left == NULL) return Root->Item;
    return BVSGetMinItem(Root->Left);
}

int BVSGetMaxItem(PtrBVSNode Root)
{
    if(Root == NULL) { printf("\nNo Tree!"); exit(-1); }
    if(Root->Right == NULL) return Root->Item;
    return BVSGetMaxItem(Root->Right);
}

void BVSDeleteTree(PtrBVSNode* PtrRoot)
{
    PtrBVSNode Root = *PtrRoot;
    if(Root == NULL) return;

    if(Root->Left != NULL) BVSDeleteTree(&Root->Left);
    if(Root->Right != NULL) BVSDeleteTree(&Root->Right);

    printf(" deleting %d", Root->Item);
    free(Root);
    *PtrRoot = NULL;
}

// odstrani prvok zo stromu
int BVSDeleteItem(PtrBVSNode* PtrRoot, int ItemToDelete)
{
    PtrBVSNode Root = *PtrRoot;
    if(Root == NULL) return 0;

    if(ItemToDelete < Root->Item)
        return BVSDeleteItem(&Root->Left, ItemToDelete);

    if(ItemToDelete > Root->Item)
        return BVSDeleteItem(&Root->Right, ItemToDelete);

    // item found
    if(Root->Left == NULL && Root->Right == NULL) {
        free(Root);
        *PtrRoot = NULL;
        return 1;
    }
    if(Root->Left == NULL) {
        *PtrRoot = Root->Right;
        free(Root);
        return 1;
    }
    if(Root->Right == NULL) {
        *PtrRoot = Root->Left;
        free(Root);
        return 1;
    }

    Root->Item = BVSGetMinItem(Root->Right);
    return BVSDeleteItem(&Root->Right, Root->Item);
}

void BVSFillArrLevel(PtrBVSNode Root, int ArrWidth, int Arr[ArrWidth], int LevelToFill,
                     int StartLevel, int Left, int Right)
{
    if(Root == NULL) return;
    if(LevelToFill == StartLevel)
        Arr[ArrWidth/2 - Left + Right] = Root->Item;

    if(Root->Left != NULL)
        BVSFillArrLevel(Root->Left, ArrWidth, Arr, LevelToFill, StartLevel+1,
                        Left + ArrWidth/pow(2,StartLevel+1), Right);

    if(Root->Right != NULL)
        BVSFillArrLevel(Root->Right, ArrWidth, Arr, LevelToFill, StartLevel+1,
                        Left, Right + ArrWidth/pow(2,StartLevel+1));
}

void BVSPrintArrLevel(PtrBVSNode Root, int ArrWidth, int Arr[ArrWidth])
{
    char form[4] = "%d", spc[3] = " ";
    if(BVSGetMaxItem(Root) > 9){
        strcpy(form,"%2d");
        strcpy(spc,"  ");
    }

    for(int i = 1; i < ArrWidth; i++)
        if(Arr[i] != -1) printf(form,Arr[i]);
        else printf("%s", spc);
}

void BVSClearArray(int ArrWidth, int Arr[ArrWidth])
{
    for(int i = 0; i < ArrWidth; i++)
        Arr[i] = -1;
}

// vypise strom v tvare stromu
void BVSPrintTree(PtrBVSNode Root)
{
    if(Root == NULL) return;

    int MaxLevel = BVSGetMaxLevel(Root);
    int ArrWidth = pow(2, MaxLevel);
    int Arr[ArrWidth];

    printf("\n");
    for(int i = 1; i <= MaxLevel; i++){
        BVSClearArray(ArrWidth, Arr);
        BVSFillArrLevel(Root, ArrWidth, Arr, i, 1, 0, 0);
        BVSPrintArrLevel(Root, ArrWidth, Arr);
        if(i != MaxLevel) printf("\n");
    }
}

// ===========================
//   MyPrintf IMPLEMENTATION
// ===========================
#include <stdarg.h>

void MyPrintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
