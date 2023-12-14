#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()
{
	int i= 0; 
	char str1[50] = "Clanguage";
	char str2[50] = { 0 };
	for ( i = 0; i < 50 ; i++)
	{
		char ch = getchar();
		if (ch == '\n')
			break;
		str2[i] = ch;
		
	}
	if (strcmp(str1,str2) == 0)//±È½Ï
	{
		printf("str1 == str2");
	}
	else if (strcmp(str1, str2) > 0)
	{
		printf("str1 < str2");
	}
	else
	{
		printf("ste1 > str2");
	}
	return 0;
}
