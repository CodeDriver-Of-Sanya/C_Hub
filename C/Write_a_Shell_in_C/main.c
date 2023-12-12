#include<stdio.h>
#include<stdlib.h>

#define LSH_RL_BUFSIZE 1024

//命令行主程序
void lsh_loop();
//读取用户输入的命令函数
char* lsh_read_line();

int main()
{

	//加载配置文件（如果有的话）

	//运行输入命令的主循环
	lsh_loop();

	//执行 关机、清理操作（Perform any shutdown/cleanup）

	return EXIT_SUCCESS;
}

void lsh_loop()
{
	//1.接收命令

	//2.分析命令

	//3.执行解析过的命令

	char* line;//接收的命令行
	char** args;//命令行参数分割后的参数
	int status;//是否继续输入的状态参数

	do
	{
		printf("> ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_excute(args);

		free(line);
		free(args);

	} while (status);
}

char* lsh_read_line()
{
	int bufSize = LSH_RL_BUFSIZE;
	char* pbuf = malloc(bufSize * sizeof(char));
	int position = 0;
	int c;//接收字符,为了能与EOF进行判断，需要用int类型接收字符，EOF是整数类型
	
	if (!pbuf) {//开空间失败就 报错 然后 退出
		fprintf(stderr, "lsh: mallocation error\n");//用文件流输出函数，将错误输出到stderr中		//https://blog.csdn.net/JDSNYD/article/details/133436052 ←fprintf用法详解
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		//一个字符一个字符地接收
		c = getchar();

		//判断当前读到的字符是不是 EOF 或者 \n（回车）
		if (c == '\n' || c == EOF)
		{
			//若是，在已读取的数组中最末尾追加 \0 并return出去，结束输入读取
			pbuf[position] = '\n';
			return pbuf;
		}
		else {
			//若不是，尾插法放入pbuf并继续读字符
			pbuf[position] = c;
		}

		position++;//位置指向向后挪一位

		//判断 position 是否超过（存满）bufSize 若是，则重新分配更大的空间
		if (position >= bufSize)
		{
			bufSize += LSH_RL_BUFSIZE;
			pbuf = realloc(pbuf, bufSize);
			//检测空间是否分配成功
			if (!pbuf)
			{
				fprintf(stderr, "lsh: reallocation error\n");
				exit(EXIT_FAILURE);
			}
		}



	}//end if while (1)


	return NULL;
}
