#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

typedef struct node {
    struct node *next;
    char *key;
} NODE, *PNODE;

typedef struct hash_table {
    PNODE *table;
    int size;
} HASHTABLE, *PHASHTABLE;

PHASHTABLE HTinit(int size);
void HTinsert(PHASHTABLE t, char *key);
int HTmember(PHASHTABLE t, char *key);
void HTdelete(PHASHTABLE t, char *key);
void HTprint(PHASHTABLE t);

// Utility printer (used by tests)
void MyPrintf(const char *format, ...);

#endif // HASHTABLE_H_INCLUDED
