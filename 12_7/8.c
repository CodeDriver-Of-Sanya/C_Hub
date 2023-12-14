#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()
{
	char username[50] = "admin";
	char password[50] = "123";
	char passwordCheck[50] = { 0 };
	printf("username:admin\npassword:");
	for (int i = 0 ; i < 50 ; i++)
	{
		passwordCheck[i] = getchar();
		if (passwordCheck[i] == '\n')
			break;
	}
	if (strcmp(password, passwordCheck))
		printf("welcome");
	return 0;
}