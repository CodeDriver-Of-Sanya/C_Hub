#ifndef _CIRCULATE_H_
#define _CIRCULATE_H_
#include"Configure.h"

typedef struct Circulate
{
	unsigned long long readerID;//读者号
	int bookNo;//书号
	char borrowData[11];//借书日期
	char returnData[11];//还书日期
	char comment[20];//备注

}Circulate;

Circulate* createEmptyCir();

Circulate* createByStr(const char* str);

void cir_print(Circulate* c);

#endif // !_CIRCULATE_H_
