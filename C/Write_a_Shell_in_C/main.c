#include<stdio.h>
#include<stdlib.h>

#define LSH_RL_BUFSIZE 1024

//������������
void lsh_loop();
//��ȡ�û�����������
char* lsh_read_line();

int main()
{

	//���������ļ�������еĻ���

	//���������������ѭ��
	lsh_loop();

	//ִ�� �ػ������������Perform any shutdown/cleanup��

	return EXIT_SUCCESS;
}

void lsh_loop()
{
	//1.��������

	//2.��������

	//3.ִ�н�����������

	char* line;//���յ�������
	char** args;//�����в����ָ��Ĳ���
	int status;//�Ƿ���������״̬����

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
	int c;//�����ַ�,Ϊ������EOF�����жϣ���Ҫ��int���ͽ����ַ���EOF����������
	
	if (!pbuf) {//���ռ�ʧ�ܾ� ���� Ȼ�� �˳�
		fprintf(stderr, "lsh: mallocation error\n");//���ļ�����������������������stderr��		//https://blog.csdn.net/JDSNYD/article/details/133436052 ��fprintf�÷����
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		//һ���ַ�һ���ַ��ؽ���
		c = getchar();

		//�жϵ�ǰ�������ַ��ǲ��� EOF ���� \n���س���
		if (c == '\n' || c == EOF)
		{
			//���ǣ����Ѷ�ȡ����������ĩβ׷�� \0 ��return��ȥ�����������ȡ
			pbuf[position] = '\n';
			return pbuf;
		}
		else {
			//�����ǣ�β�巨����pbuf���������ַ�
			pbuf[position] = c;
		}

		position++;//λ��ָ�����Ųһλ

		//�ж� position �Ƿ񳬹���������bufSize ���ǣ������·������Ŀռ�
		if (position >= bufSize)
		{
			bufSize += LSH_RL_BUFSIZE;
			pbuf = realloc(pbuf, bufSize);
			//���ռ��Ƿ����ɹ�
			if (!pbuf)
			{
				fprintf(stderr, "lsh: reallocation error\n");
				exit(EXIT_FAILURE);
			}
		}



	}//end if while (1)


	return NULL;
}
