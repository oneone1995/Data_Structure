/*
	1 ���������� ע��ѭ�������Է�ֹ���ڵ������� 
	2 ��������� ÿ�θ��µĽڵ㸳ֵ����ַ�����ʱ��ע���ʼ��
	3 ���� ��Ϊ�ڴ���100010���������� �����ܳ���1000��10001֮��ı��� ��������������в��ص����������
	4 ��������� �������ַ�����һ����Ч����ֵ�Ժ�ע��Ҫ���������¿�ʼѭ�� ע���ʼ��
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct //������һ�����νڵ� ��һ������һ���Һ���
{
	char data;//�ַ�
	unsigned int weight;//Ȩֵ
	unsigned int parent;//˫��
	unsigned int lChild;//����
	unsigned int rChild;//�Һ���
}HTNode, *HuffmanTree;

//typedef char ** HuffmanCode;//HuffmanCode�൱��char ** �һ���֪������������ĵ���

typedef struct //������һ���ṹ�� �������˹���������ֵ���ַ���
{
	char code[100];
	int end;//ÿһ���ڵ�ı����ַ��������λ�� �������ʱ�Ŀ�ʼѭ����λ��
}HuffmanCode;

void Select(HuffmanTree * HT, int length, int * x1, int * x2)  //���ҳ�2��Ȩֵ��С�Ľڵ���±�  
{
	int  k1, k2;
	k1 = -1;
	k2 = -1;

	for (int i = 1; i <= length; i++)    //�ҳ����е�ǰ����Ԫ�ز�ΪNULL���±�  
	{
		if ((*HT)[i].parent == 0 && k1 == -1)
		{
			k1 = i;     //��һ���±�  
			continue;
		}
		if ((*HT)[i].parent == 0)
		{
			k2 = i;
			break;//�ҵ��ڶ����±��˳�ѭ��  
		}
	}

	////// ��СȨ��2���±������ʵ��//////////     
	for (int i = k2; i <= length; i++) //�������Ȼ�ȡk1  ���ȡk2����һ��ʼ һ���Ǵ�k2��ʼѭ����   
	{
		if ((*HT)[i].parent == 0)
		{
			if ((*HT)[i].weight < (*HT)[k1].weight)  //����±�k1��Ȩ С�ڵ�ǰ�±��Ԫ�ص�Ȩ   
			{
				k2 = k1;  //��ʱ����k1 < k2�������Ƿ��صĽ��  
				k1 = i;
			}
			else if ((*HT)[i].weight < (*HT)[k2].weight)
			{
				k2 = i;
			}

		}
	}
	*x1 = k1;
	*x2 = k2;
}


void CreatHuffman(HuffmanTree * HT, int n, int * w, char * s)//����������Ĺ��� ����һ��HTNode����������Ź������ڵ� ��n����Ҫ����Ľڵ� //w�Ǵ����n���ַ���Ȩֵ������
{
	int i;
	int x1, x2;//x1,x2ΪȨֵ��С�������ڵ���±�
	int m = 2 * n - 1;//n��Ҷ�ӽڵ�Ĺ�����������2n-1���ڵ� ����m���ڵ�
	int end;

	HuffmanTree p;
	*HT = (HuffmanTree)malloc((m + 2) *sizeof(HTNode));//����m + 2�����������ڵ� ����HTָ��������ڴ���׵�ַ �����HTNode��������׵�ַָ������ַ���׵�ַ
	p = *HT;//����pָ��HT���׵�ַ ���ڲ���
	p++;

	for (i = 1; i <= n; i++, w++, p++, s++)//��һ��ѭ����pָ�������ڴ��ǰn���ڵ㶼�ȳ�ʼ��ΪȨֵΪw��������е�ֵ ˫�� ���Һ��Ӷ�Ϊ0
	{
		(*p).data = *s;
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lChild = 0;
		(*p).rChild = 0;
	}

	for (; i <= m + 1; i++, p++)//i��n+1��ʼ //��ʣ�µĽڵ��ʼ��Ϊ0
	{
		(*p).weight = 0;
		(*p).parent = 0;
		(*p).lChild = 0;
		(*p).rChild = 0;
		
	}

	for (i = n + 1; i <= m; i++)//����
	{
		Select(HT, i - 1, &x1, &x2);
		(*HT)[x1].parent = i;
		(*HT)[x2].parent = i;
		(*HT)[i].lChild = x1;
		(*HT)[i].rChild = x2;
		(*HT)[i].weight = (*HT)[x1].weight + (*HT)[x2].weight;
	}
	//(*HT)[m].parent = 0;

}

void CodingHuffmanTree(HuffmanTree  HT, HuffmanCode ** HC, int length)//���������
{
	int i = 1;
	int father;//��f��¼�ڵ��˫�׽ڵ���±� ���ڲ���
	int tempFather = i;

	(*HC) = (HuffmanCode *)malloc((length + 1) * sizeof(HuffmanCode));

	(*HC)[i].end = length - 1;

	for (i = 1; i <= length; i++)//Ϊ���HT�е�ÿ��Ҷ�ӽڵ���� һֱ�����ҵ��� 
	{
		(*HC)[i].end = length - 1;
		father = HT[i].parent;
		tempFather = i;//ÿ�θ�tempFather��ʼ�� ��ΪHC��������ĵ�i�ڵ㸳ֵ
		while (father != 0)//
		{
			if (HT[father].lChild == tempFather)//�����ǰ����˫�׽ڵ�����ӽڵ��±���ڵ�ǰ�Ľڵ��±� ����HC�ĵ�ǰ����е��ַ����з�һ��0
			{
				(*HC)[i].code[(*HC)[i].end--] = '0';//��ΪҶ�ӽڵ������������ ��˱���Ӧ����������е�
			}
			else								//�����ǰ����˫�׽ڵ�����ӽڵ��±���ڵ�ǰ�Ľڵ��±� ����HC�ĵ�ǰ����е��ַ����з�һ��1
			{
				(*HC)[i].code[(*HC)[i].end--] = '1';//����ͬ����������е�
			}
			tempFather = father;//��tempFather��ֵ���ڵ�ǰ����˫�׽ڵ��±�
			father = HT[father].parent;
		}
	}
}
void Encoding(char * str, int length, HuffmanTree HT, HuffmanCode * HC)//����
{
	int i, j;
	int k;

	printf("������Ϊ:");

	for (i = 0; *str != '\0'; i++, str++)                  //�س�Ϊ��ֹ��־
	{
		for (j = 1; j <= length; j++)
		{
			if (*str == HT[j].data)            //ѭ�������������ַ���ͬ�ı�ţ���ͬ�ľ��������ַ��ı���
			{
				printf("%c:", HT[j].data);
				for (k = HC[j].end + 1; k < length; k++)
				{
					printf("%c", HC[j].code[k]);
				}
				break;                      //�����ɺ�������ǰforѭ��
			}
		}
		printf(" ");
	}
	printf("\n");
}

void Decoding(HuffmanTree HT, int length, char * strToEng)//����
{
	int m = 2 * length - 1;
	int i = 0;
	int temp = m;

	printf("������Ϊ:");
	while (strToEng[i] != '\0')//�ַ���û����֮ǰѭ�������ַ���
	{
		temp = m;//���³�ʼ��tempΪ2n - 1 �Ա��������ʼ������������
		while (HT[temp].lChild != 0 && HT[temp].rChild != 0)
		{
			if (strToEng[i] == '0')//����ַ����е��ַ���0 ��ô�Ͱѵ�ǰ�������ӽڵ��±긳ֵ��temp
			{
				temp = HT[temp].lChild;
			}
			else				//����ַ����е��ַ���1 ��ô�Ͱѵ�ǰ�����Һ��ӽڵ��±긳ֵ��temp
			{
				temp = HT[temp].rChild;
			}

			i++;//i���������� �����ַ����е�ǰ�ַ�����һ���ַ�
		}//���ѭ�������Ժ� �����Ѿ�����һ��Ҷ�ӽڵ��� ���Ҷ�ӽڵ��data��ֵ��һ����ĸ
		printf("%c", HT[temp].data);//һ����ĸ��������Ժ� ������Ҷ�ӽڵ��data
	}
	printf("\n");
}

int main()
{
	char judge;//�˵��ж��ַ�
	char str[] = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0' };
	int num[] = { 186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 2, 32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1 };
	//char str[] = { ' ', 'A', 'B', 'C', 'D', '\0' };//��������
	//int num[] = { 186, 64, 13, 22, 32 };//��������
	char toBeTran[10000];//��Ҫ������ַ���
	char toEnglish[10000];//������ַ���

	HuffmanTree HT = NULL;
	HuffmanCode * HC = NULL;

	CreatHuffman(&HT, strlen(str), num, str);//����
	CodingHuffmanTree(HT, &HC, strlen(str));//��HuffmanTree �����
	///������� ��������������Ҫִ�е� ��˶���˵��ж��ַ�Ӧ������������///
	//gets(toBeTran);
	//Encoding(toBeTran, strlen(str), HT, HC);
	printf("����EΪ���� ����DΪ���� ����QΪ�˳�\n");
	scanf("%c", &judge);
	getchar();
	if (judge == 'E')
	{
		printf("��������Ҫ������ַ�:\n");
		gets(toBeTran);//������Ҫ������ַ�
		Encoding(toBeTran, strlen(str), HT, HC);
	}
	else if (judge == 'D')
	{
		gets(toEnglish);
		Decoding(HT, strlen(str), toEnglish);
	}
	else if (judge == 'Q')
	{
		exit(-1);
	}
	else
	{
		printf("�������");
	}
	system("pause");
	return 0;
}