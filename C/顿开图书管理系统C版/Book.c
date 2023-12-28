#include "Book.h"

Book* createEmptyBook()
{
    Book* newBook = calloc(1, sizeof(Book));
    if (!newBook)
    {
        printf("createEmptyBook calloc failed!\n");
        system("pause");
        return NULL;
    }
    return newBook;
}

Book* book_byString(const char* s)
{
    Book* newBook = createEmptyBook();
    int ret = sscanf(s, "%d %d %s %s %s %d %d %d %d %d", &newBook->recordNo, &newBook->bookNo, newBook->name, newBook->author, newBook->publish, &newBook->bookNum, &newBook->lendNum, &newBook->p1, &newBook->p2, &newBook->p3);
    if (ret <= 0)
    {
        printf("book_byString sscanf failed!\n");
        system("pause");
        return NULL;
    }

    return newBook;
}

void book_print(Book* b)
{
    printf("%-8d %-5d %-10s %-10s %-10s %-6d %d | %d %d %d |\n", b->recordNo, b->bookNo, b->name, b->author, b->publish, b->bookNum, b->lendNum,b->p1,b->p2,b->p3);
}
