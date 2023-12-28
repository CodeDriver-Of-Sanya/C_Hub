#include "BookIndex.h"

BookIndex* createEmptyBookIndex()
{
    BookIndex* bi = calloc(1, sizeof(BookIndex));
    if (!bi)
    {
        printf("createEmptyBookIndex calloc failed!\n");
        return NULL;
    }
    bi->length = 0;
    bi->point = 0;

    return bi;
}

void bookIndex_print(BookIndex* bi)
{
    printf("%-10s %d %d\n", bi->str, bi->point, bi->length);
}
