#ifndef _BOOKINDEX_H_
#define _BOOKINDEX_H_
#include"Configure.h"

typedef struct BookIndex
{
	char str[20];//书名，作者，出版社
	int point;//指针(保存idx
	int length;//数量

}BookIndex;

BookIndex* createEmptyBookIndex();

void bookIndex_print(BookIndex* bi);

#endif // !_BOOKINDEX_H_
