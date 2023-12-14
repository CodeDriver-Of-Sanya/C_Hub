#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main()//在49个字符以内的筛检
{
	char s[50] = { 0 };
	int j = 0;
	for (int i = 0; i < 50; i++)
	{
		char ch = getchar();
		if (i == 0 || i % 2 == 0)
		{
			s[j] = ch;
			j++;
		}
		else
		{
			int tmp = ch;
			if (tmp % 2 == 0)
			{
				s[j] = ch;
				j++;
			}
		}
		if (ch == '\n')
			break;
	}
	for (int i = 0 ; i < 50; i++)
	{
		if (s[i] == '\n')
			break;
		printf("%c",s[i]);
	}
	return 0;
}