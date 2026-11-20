#ifndef LQUEUE_H_INCLUDED
#define LQUEUE_H_INCLUDED

// ==== Definícia údajových typov pre ADT Queue ====

typedef int TElem;   // typ prvku vo fronte

struct Node;
struct LnkQueue;

// smerníky na štruktúry
typedef struct Node *PNode;
typedef struct LnkQueue *LQueue;

// ==== Prototypy operácií pre ADT Queue ====

int IsEmptyQueue(LQueue Q);
LQueue CreateQueue(void);
void RemoveQueue(LQueue *PQ);
void MakeEmptyQueue(LQueue Q);

void Enqueue(TElem X, LQueue Q);
TElem Front(LQueue Q);
void Dequeue(LQueue Q);
TElem FrontAndDequeue(LQueue Q);

void PrintQueue(LQueue Q);

#endif // LQUEUE_H_INCLUDED
