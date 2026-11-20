#ifndef ERR_H_INCLUDED
#define ERR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Makro pre hlásenie chýb
#define Error(msg) (printf("\nError - %s\n", msg), exit(1))

#endif // ERR_H_INCLUDED
