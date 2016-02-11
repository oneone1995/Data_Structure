/*
	1 建树过程中 注意循环次数以防止最后节点有问题 
	2 编码过程中 每次给新的节点赋值存放字符串的时候注意初始化
	3 例如 因为在存在100010编码的情况下 不可能出现1000或10001之类的编码 所以在译码过程中不必担心这个问题
	4 译码过程中 处理完字符串中一个有效编码值以后注意要从树根重新开始循环 注意初始化
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct //构造了一个树形节点 有一个左孩子一个右孩子
{
	char data;//字符
	unsigned int weight;//权值
	unsigned int parent;//双亲
	unsigned int lChild;//左孩子
	unsigned int rChild;//右孩子
}HTNode, *HuffmanTree;

//typedef char ** HuffmanCode;//HuffmanCode相当于char ** 我还不知道是拿来干嘛的但是

typedef struct //构造了一个结构体 里面存放了哈夫曼编码值的字符串
{
	char code[100];
	int end;//每一个节点的编码字符串的最后位置 输出编码时的开始循环的位置
}HuffmanCode;

void Select(HuffmanTree * HT, int length, int * x1, int * x2)  //查找出2个权值最小的节点的下标  
{
	int  k1, k2;
	k1 = -1;
	k2 = -1;

	for (int i = 1; i <= length; i++)    //找出其中的前两个元素不为NULL的下标  
	{
		if ((*HT)[i].parent == 0 && k1 == -1)
		{
			k1 = i;     //第一个下标  
			continue;
		}
		if ((*HT)[i].parent == 0)
		{
			k2 = i;
			break;//找到第二个下标退出循环  
		}
	}

	////// 最小权的2个下标的搜索实现//////////     
	for (int i = k2; i <= length; i++) //我们是先获取k1  后获取k2所以一开始 一定是从k2开始循环的   
	{
		if ((*HT)[i].parent == 0)
		{
			if ((*HT)[i].weight < (*HT)[k1].weight)  //如果下标k1的权 小于当前下标的元素的权   
			{
				k2 = k1;  //此时还是k1 < k2满足我们返回的结果  
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


void CreatHuffman(HuffmanTree * HT, int n, int * w, char * s)//哈夫曼树打的构造 构造一个HTNode的数组来存放哈夫曼节点 有n个需要编码的节点 //w是存放着n个字符的权值的数组
{
	int i;
	int x1, x2;//x1,x2为权值最小的两个节点的下标
	int m = 2 * n - 1;//n个叶子节点的哈夫曼树共有2n-1个节点 即有m个节点
	int end;

	HuffmanTree p;
	*HT = (HuffmanTree)malloc((m + 2) *sizeof(HTNode));//分配m + 2个哈夫曼树节点 并让HT指向这个块内存的首地址 即存放HTNode的数组的首地址指向这块地址的首地址
	p = *HT;//先用p指向HT的首地址 便于操作
	p++;

	for (i = 1; i <= n; i++, w++, p++, s++)//用一个循环把p指向的这块内存的前n个节点都先初始化为权值为w这个数组中的值 双亲 左右孩子都为0
	{
		(*p).data = *s;
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lChild = 0;
		(*p).rChild = 0;
	}

	for (; i <= m + 1; i++, p++)//i从n+1开始 //把剩下的节点初始化为0
	{
		(*p).weight = 0;
		(*p).parent = 0;
		(*p).lChild = 0;
		(*p).rChild = 0;
		
	}

	for (i = n + 1; i <= m; i++)//建树
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

void CodingHuffmanTree(HuffmanTree  HT, HuffmanCode ** HC, int length)//建立编码表
{
	int i = 1;
	int father;//用f记录节点的双亲节点的下标 便于操作
	int tempFather = i;

	(*HC) = (HuffmanCode *)malloc((length + 1) * sizeof(HuffmanCode));

	(*HC)[i].end = length - 1;

	for (i = 1; i <= length; i++)//为存进HT中的每个叶子节点编码 一直向上找到根 
	{
		(*HC)[i].end = length - 1;
		father = HT[i].parent;
		tempFather = i;//每次给tempFather初始化 即为HC这个编码表的第i节点赋值
		while (father != 0)//
		{
			if (HT[father].lChild == tempFather)//如果当前结点的双亲节点的左孩子节点下标等于当前的节点下标 就在HC的当前结点中的字符串中放一个0
			{
				(*HC)[i].code[(*HC)[i].end--] = '0';//因为叶子节点是在最下面的 因此编码应该是逆序进行的
			}
			else								//如果当前结点的双亲节点的左孩子节点下标等于当前的节点下标 就在HC的当前结点中的字符串中放一个1
			{
				(*HC)[i].code[(*HC)[i].end--] = '1';//编码同样是逆序进行的
			}
			tempFather = father;//让tempFather的值等于当前结点的双亲节点下标
			father = HT[father].parent;
		}
	}
}
void Encoding(char * str, int length, HuffmanTree HT, HuffmanCode * HC)//编码
{
	int i, j;
	int k;

	printf("编码结果为:");

	for (i = 0; *str != '\0'; i++, str++)                  //回车为终止标志
	{
		for (j = 1; j <= length; j++)
		{
			if (*str == HT[j].data)            //循环查找与输入字符相同的编号，相同的就输出这个字符的编码
			{
				printf("%c:", HT[j].data);
				for (k = HC[j].end + 1; k < length; k++)
				{
					printf("%c", HC[j].code[k]);
				}
				break;                      //输出完成后跳出当前for循环
			}
		}
		printf(" ");
	}
	printf("\n");
}

void Decoding(HuffmanTree HT, int length, char * strToEng)//译码
{
	int m = 2 * length - 1;
	int i = 0;
	int temp = m;

	printf("译码结果为:");
	while (strToEng[i] != '\0')//字符串没结束之前循环遍历字符串
	{
		temp = m;//重新初始化temp为2n - 1 以便从树根开始遍历哈夫曼树
		while (HT[temp].lChild != 0 && HT[temp].rChild != 0)
		{
			if (strToEng[i] == '0')//如果字符串中的字符是0 那么就把当前结点的左孩子节点下标赋值给temp
			{
				temp = HT[temp].lChild;
			}
			else				//如果字符串中的字符是1 那么就把当前结点的右孩子节点下标赋值给temp
			{
				temp = HT[temp].rChild;
			}

			i++;//i别忘了自增 处理字符串中当前字符的下一个字符
		}//这个循环结束以后 我们已经到了一个叶子节点了 这个叶子节点的data的值是一个字母
		printf("%c", HT[temp].data);//一个字母译码结束以后 输出这个叶子节点的data
	}
	printf("\n");
}

int main()
{
	char judge;//菜单判断字符
	char str[] = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0' };
	int num[] = { 186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 2, 32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1 };
	//char str[] = { ' ', 'A', 'B', 'C', 'D', '\0' };//测试数据
	//int num[] = { 186, 64, 13, 22, 32 };//测试数据
	char toBeTran[10000];//需要编码的字符串
	char toEnglish[10000];//译码的字符串

	HuffmanTree HT = NULL;
	HuffmanCode * HC = NULL;

	CreatHuffman(&HT, strlen(str), num, str);//建树
	CodingHuffmanTree(HT, &HC, strlen(str));//建HuffmanTree 编码表
	///无论如何 以上两步都是需要执行的 因此读入菜单判断字符应在这两步后面///
	//gets(toBeTran);
	//Encoding(toBeTran, strlen(str), HT, HC);
	printf("输入E为编码 输入D为译码 输入Q为退出\n");
	scanf("%c", &judge);
	getchar();
	if (judge == 'E')
	{
		printf("请输入需要编码的字符:\n");
		gets(toBeTran);//输入需要编码的字符
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
		printf("输入出错");
	}
	system("pause");
	return 0;
}