#define _CRT_SECURE_NO_WARNINGS 1
#include "free.h"
void resetHighboard(char highBoard[HIGH], int high)
{
	int i = 0;
	for (i = 0 ; i < high ; i++)
	{
		highBoard[i] = '|';
	}
}