#ifndef _READER_H_
#define _READER_H_
#include"Configure.h"

typedef struct Reader
{
	unsigned long long readerID;//读者号
	char name[10];//读者姓名
	char unit[20];//单位
	char tel[20];//联系方式
	int borrowNum;//可借书数量
	int borrowedNum;//已借书数量
}Reader;

//创建空读者
Reader* createEmptyReader();

//打印读者信息
void reader_print(Reader* r);

//对比读者ID
bool reader_cmpID(Reader* r, unsigned long long _ID);

#endif // !_READER_H_
