/*
题目描述

　　实现将一个十进制的正整数转化为十六进制的算法。


输入描述

　　输入数据有多组。每组数据第一行输入一个整数N(N<=1000)，然后有N行，每行输入一个十进制正整数。
	当N=0时输入结束。


 输出描述

　　将输入的十进制整数转化为十六进制并输出，每个输出占一行。其中十六进制的字符用0~9，A~F表示。


输入样例

	3
	232
	29
	11
	0


输出样例

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