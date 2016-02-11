/*
��Ŀ����

��������һ���������У�����һ�Ŷ�����������Ȼ����������������


��������

  �����������ж��顣ÿ�����ݵ�һ������һ������N(N<=10000)���ڶ�������N��������
	������N=0ʱ���������

�������

	�����Ӧ���������������������


��������

	8
	24 49 41 29 64 20 39 56
	0


�������

	24 20 49 41 29 39 64 56
*/
#include<stdio.h>
#include<stdlib.h>

int arr[10000] = { 0 };
int flag = 0;

typedef struct BitNode	//������һ�����νڵ� ��һ������һ���Һ���
{
	int data;
	BitNode * lChild;
	BitNode * rChild;
}BiTree;


void InitTree(BiTree * T)
{
	T->lChild = NULL;
	T->rChild = NULL;
	T->data = 0;
}

void BulidTree(BiTree * T, int length)
{
	int i = 2;
	T->data = arr[1];

	for (i = 2; i <= length; i++)
	{
		BiTree * node = (BiTree *)malloc(sizeof(BitNode));
		node->data = arr[i];
		node->lChild = node->rChild = NULL;


		BiTree * p = T;
		while (p != NULL)
		{
			if (arr[i] <= p->data)
			{
				if (p->lChild == NULL)
				{
					p->lChild = node;
					break;
				}
				else
				{
					p = p->lChild;
				}
			}

			else
			{
				if (arr[i] > p->data)
				{
					if (p->rChild == NULL)
					{
						p->rChild = node;
						break;
					}
					else
					{
						p = p->rChild;
					}
				}
			}
		}
	}
}

void PreOrderTraverse(BiTree * T)
{
	//int flag = 0;
	if (flag == 1)
	{
		printf(" ");
		//flag = 1;
	}
	printf("%d", T->data);
	flag = 1;
	if (T->lChild != NULL)
	{
		PreOrderTraverse(T->lChild);
	}
	if (T->rChild != NULL)
	{
		PreOrderTraverse(T->rChild);
	}
}

int main()
{
	int N;
	int i;

	BiTree * T = (BiTree *)malloc(sizeof(BiTree));

	while (scanf("%d", &N) != EOF && N)
	{
		InitTree(T);

		for (i = 1; i <= N; i++)
		{
			scanf("%d", &arr[i]);
		}

		BulidTree(T, N);
		PreOrderTraverse(T);
		//printf("\n");
	}


	return 0;
}