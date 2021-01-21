#include <stdio.h>
#include "list.h"

typedef struct
{
    const char* name;
    int id;
}employe_t;

void printEmploye(const void* data)
{
    printf("\n\t Name: %s, Id: %i", ((employe_t*)data)->name, 
            ((employe_t*)data)->id);
}

int main(void)
{
    employe_t ivan = { "Ivan", 152 };

    list_t* list = NULL;
    printf("\nAfter listInit;");
    listInit(&list, &ivan, sizeof(employe_t));
    listPrintAll(list, printEmploye);

    printf("\nAfter listPushBack:");
    employe_t dima = { "Dima", 136 };
    listPushBack(list, &dima);
    listPrintAll(list, printEmploye);

    printf("\nAfter listPushFront");
    employe_t mark = { "Mark", 431 };
    listPushFront(list, &mark);
    listPrintAll(list, printEmploye);

    printf("\nAfter listMoveIter & listInsert");
    employe_t oleg = { "Oleg", 312 };
    node_t* iter = listMoveIter(list->front, 1, false);
    listInsert(list, iter, &oleg);
    listPrintAll(list, printEmploye);

    printf("\nAfter listPopBack");
    employe_t dimapop = { " ", 0 };
    listPopBack(list, &dimapop);
    listPrintAll(list, printEmploye);
    printf("\n\tPopped employe:");
    printEmploye(&dimapop);

    printf("\nAfter listTruncate");
    listTruncate(list, list->front);
    listPrintAll(list, printEmploye);

    printf("\n");
    listFree(list);
}
/* Output
mironov-aa@arch ~/Development/prosoft :( $ make
gcc -g3 -Wall -Wextra -Wpedantic main.c list.c
mironov-aa@arch ~/Development/prosoft $ ./a.out 

After listInit;
	 Name: Ivan, Id: 152
After listPushBack:
	 Name: Ivan, Id: 152
	 Name: Dima, Id: 136
After listPushFront
	 Name: Mark, Id: 431
	 Name: Ivan, Id: 152
	 Name: Dima, Id: 136
After listMoveIter & listInsert
	 Name: Mark, Id: 431
	 Name: Ivan, Id: 152
	 Name: Oleg, Id: 312
	 Name: Dima, Id: 136
After listPopBack
	 Name: Mark, Id: 431
	 Name: Ivan, Id: 152
	 Name: Oleg, Id: 312
	Popped employe:
	 Name: Dima, Id: 136
After listTruncate
	 Name: Mark, Id: 431
*/