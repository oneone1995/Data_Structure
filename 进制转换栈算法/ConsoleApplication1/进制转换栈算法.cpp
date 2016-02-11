/*
��Ŀ����

����ʵ�ֽ�һ��ʮ���Ƶ�������ת��Ϊʮ�����Ƶ��㷨��


��������

�������������ж��顣ÿ�����ݵ�һ������һ������N(N<=1000)��Ȼ����N�У�ÿ������һ��ʮ������������
	��N=0ʱ���������


 �������

�����������ʮ��������ת��Ϊʮ�����Ʋ������ÿ�����ռһ�С�����ʮ�����Ƶ��ַ���0~9��A~F��ʾ��


��������

	3
	232
	29
	11
	0


�������

	E8
	1D
	B
*/

#define STACK_INIT_SIZE 100
#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
	char * base;
	char * top;
	int stacksize;
}SqStack;

void InitStack(SqStack * S)
{
	S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}

void PushStack(SqStack * S, char ch)
{
	*S->top = ch;
	S->top++;
	//printf("%c\n", *(S->top - 1));
}

void PopStack(SqStack * S, char * ch)
{
	S->top--;
	*ch = * (S->top);
}

int StackEmpty(SqStack * S)
{
	if (S->base == S->top)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
{
	int N;
	int num;
	int result;
	char chIn, chOut;
	char conver[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };

	SqStack S;

	while (scanf("%d",&N) != EOF && N)
	{
		InitStack(&S);

		while (N--)
		{
			scanf("%d", &num);
			while (num)
			{
				result = num % 16;
				if (result <= 9)
				{
					chIn = result + '0';
				}
				else
				{
					chIn = conver[result - 10];
				}
				PushStack(&S, chIn);
				num = num / 16;
			}
			
			while (StackEmpty(&S))
			{
				PopStack(&S, &chOut);
				printf("%c", chOut);
			}
			printf("\n");
		}
	}

	return 0;
}