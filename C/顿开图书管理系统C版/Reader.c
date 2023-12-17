#include "Reader.h"

Reader* createEmptyReader()
{
    Reader* r = calloc(1, sizeof(Reader));
    if (!r)
    {
        printf("Reader calloc failed!\n");
        return NULL;
    }
}

void reader_print(Reader* r)
{
    printf("%-10llu %-10s %-15s %-15s %d %d\n", r->readerID, r->name, r->unit, r->tel, r->borrowNum, r->borrowedNum);
}
