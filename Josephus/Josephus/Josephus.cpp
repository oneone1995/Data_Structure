#include<stdio.h>
#include<stdlib.h>

typedef struct LNode
{
	int data;//����
	int num;//���
	struct LNode * next;
}LNode, *LinkList;


LinkList CreateList_L(int length)//����һ��ѭ������ �Ա���Լɪ���е�Χ��һȦ
{
	int i;
	LinkList L = (LinkList)malloc(sizeof(LNode));
	LinkList q = L;
	q->next = NULL;
	for (i = 0; i < length; i++)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);//��ÿ���˵����븳ֵ
		p->num = i + 1;//��ÿ���˵���Ÿ�ֵ
		q->next = p;
		p->next = NULL;
		q = p;
	}
	q->next = L->next;//��β�ڵ��nextָ���׽ڵ㹹��ѭ������

	return L;
}


void JosephusList_L(LinkList L, int m, int num)
{
	LinkList p = L->next;
	LinkList q = L->next;
	int i;
	int count = 1;
	
	while (num != 0)//������Ϊ0ʱ�˳�ѭ��
	{
		for (i = 1; i < m; i++)
		{
			p = p->next;
		}

		printf("%d ", p->num);//���е��˵����
		m = p->data;//�µ�����
	
		while (q->next != p)//ɾ���ڵ� ��֤�����������µ�����
		{
			q = q->next;		//��q��¼ѭ�� ��q����һ���ڵ���pʱ �˳�ѭ�� ������ʱq�ĵ�ַ
		}
		q->next = p->next;	//ɾ��q�ĺ�һ���ڵ� ��ɾ��p����ָ��Ľڵ�
		p = q;				//��q�ĵ�ַ����p p����ָ��ɾ���Ľڵ��ǰһ���ڵ�
		p = p->next;			//pָ��p����һ���ڵ�
		
		num--;//����-1
		
	}

}

void TraverseList_L(LinkList L)//����������� ���ڲ���
{
	LinkList p = L;
	while (p->next != NULL)
	{
		printf("%d ", p->next->data);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	int m = 20;//m��Ϊ��ʼ����20
	int num = 7;
	LinkList L = CreateList_L(num);//7���˵�������3 1 7 2 4 8 4
	JosephusList_L(L, m, num);
	//TraverseList_L(L);

	return 0;
}
