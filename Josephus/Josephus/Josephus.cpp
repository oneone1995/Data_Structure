#include<stdio.h>
#include<stdlib.h>

typedef struct LNode
{
	int data;//密码
	int num;//序号
	struct LNode * next;
}LNode, *LinkList;


LinkList CreateList_L(int length)//创建一个循环链表 对比于约瑟夫环中的围成一圈
{
	int i;
	LinkList L = (LinkList)malloc(sizeof(LNode));
	LinkList q = L;
	q->next = NULL;
	for (i = 0; i < length; i++)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);//给每个人的密码赋值
		p->num = i + 1;//给每个人的序号赋值
		q->next = p;
		p->next = NULL;
		q = p;
	}
	q->next = L->next;//让尾节点的next指向首节点构成循环链表

	return L;
}


void JosephusList_L(LinkList L, int m, int num)
{
	LinkList p = L->next;
	LinkList q = L->next;
	int i;
	int count = 1;
	
	while (num != 0)//当人数为0时退出循环
	{
		for (i = 1; i < m; i++)
		{
			p = p->next;
		}

		printf("%d ", p->num);//出列的人的序号
		m = p->data;//新的密码
	
		while (q->next != p)//删除节点 保证接下来操作新的链表
		{
			q = q->next;		//用q记录循环 当q的下一个节点是p时 退出循环 保存这时q的地址
		}
		q->next = p->next;	//删除q的后一个节点 即删除p现在指向的节点
		p = q;				//把q的地址赋给p p现在指向被删除的节点的前一个节点
		p = p->next;			//p指向p的下一个节点
		
		num--;//人数-1
		
	}

}

void TraverseList_L(LinkList L)//遍历链表输出 用于测试
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
	int m = 20;//m作为初始密码20
	int num = 7;
	LinkList L = CreateList_L(num);//7个人的密码是3 1 7 2 4 8 4
	JosephusList_L(L, m, num);
	//TraverseList_L(L);

	return 0;
}
