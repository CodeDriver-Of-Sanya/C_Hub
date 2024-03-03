#include<stdio.h>
#include<stdbool.h>
#define BUFSIZE 128

void openAndClose() {
	//r read 只读，不能写，若文件不存在则会失败
	//w write 只写，不能读，若文件不存在则会创建文件，若存在则会清空内容
	//a append 追加只写，不能读，如果文件不存在则创建文件，若存在则会在内容末尾追加内容
	
	FILE* fp = fopen("1.txt", "r");
	if (!fp) {
		perror("open failed");
		return;
	}

	fclose(fp);
}

//字符读
void charRead() {
	FILE* fp = fopen("charRead.txt", "r");
	if (!fp) {
		perror("open failed");
		return;
	}
	int ch = fgetc(fp);
	if (ch == EOF) {
		perror("read failed");
	}
	else {
		printf("%c", ch);
	}

	//接下来的全部读出来
	//1，
	//while (true) {
	//	ch = fgetc(fp);
	//	if (ch == EOF) {
	//		break;
	//	}
	//	putchar(ch);
	//}

	//2.
	while ((ch = fgetc(fp)) != EOF) {
		putchar(ch);
	}

	fclose(fp);
}

//字符写
void charWrite() {
	FILE* fp = fopen("charRead.txt", "w");
	if (!fp) {
		perror("open failed");
		return;
	}
	
	//写一个字符
	fputc('#', fp);

	//写多个字符
	for (int i = 0; i < 26; i++)
	{
		fputc('A' + i, fp);
	}

	fclose(fp);
}

//又要写，又要读(最好不要这样)
void charReadWrite() {
	FILE* fp = fopen("charRead.txt", "w+");
	if (!fp) {
		perror("open failed");
		return;
	}
	int ch;
	//写点东西
	fputc('A', fp);
	//重置文件位置指针到文件的开头
	rewind(fp);
	//读出来
	if ((ch = fgetc(fp)) != EOF) {
		printf("succeed  %c", ch);
	}
	else {
		printf("read failed");
	}

	fclose(fp);
}

//字符串读
void strRead() {
	FILE* fp = fopen("strRead.txt", "r");
	if (!fp) {
		perror("open failed");
		return;
	}

	char buf[BUFSIZE] = { 0 };
	if (!fgets(buf, BUFSIZ, fp)) {
		printf("str read failed!\n");
	}
	else {
		puts(buf);
	}

	fclose(fp);

}

//字符串写
void strRead() {
	FILE* fp = fopen("strRead.txt", "w");
	if (!fp) {
		perror("open failed");
		return;
	}

	if (0 != fputs("hello World!", fp)) {
		perror("write error");
	}

	fclose(fp);

}

int main() {

	//openAndClose();
	//charRead();
	//charWrite();
	//charReadWrite();
	strRead();

	return 0;
}