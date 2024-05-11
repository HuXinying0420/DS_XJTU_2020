#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable : 4996)
#define MaxStrlen       27				//最大串长  
#define STACK_INIT_SIZE 100				//存储空间初始分配量 
#define STACKINCREMENT  10				//存储空间分配增量 
#define OK 				1               //函数执行正常
#define ERROR 			0               //函数执行出现错误
#define OVERFLOW 		-1              //存储分配失败
typedef struct {
	int arcs;							//结点权重 
	int parent;							//双亲结点 
	int lchild;							//左孩子结点 
	int rchild;							//右孩子结点 
}HTNode, * HuffmanTree;					//定义哈夫曼树
typedef char** HuffmanCode;				//定义哈夫曼表
typedef struct {
	int* base;							//栈底指针 
	int* top;							//栈顶指针
	int stacksize;						//初始分配空间大小 
}SqStack;								//定义栈结构体
int InitStack(SqStack& S)
{
	S.base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
	if (!S.base) return OVERFLOW;		//存储分配失败 
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}										//栈初始化
int StackEmpty(SqStack S)
{
	if (S.base == S.top) return OK;
	else return ERROR;
}										//判空
int Pop(SqStack& S)
{
	int element;
	if (S.top == S.base) return ERROR;
	element = *--S.top;
	return element;
}										//删除栈顶元素并返回其值
int Push(SqStack& S, int element)
{
	if (S.top - S.base >= S.stacksize)  //栈满，追加存储空间
	{
		S.base = (int*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(int));
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = element;
	return OK;
}										//element入栈，作为栈顶元素
int DestoryStack(SqStack& S)
{
	free(S.base);
	S.base = NULL;
	S.top = NULL;
	S.stacksize = 0;
	return OK;
}										//销毁栈,释放内存空间

void Select(HuffmanTree HT, int Size, int* s1, int* s2, int MAX)
{										//查找到两个权值最小的结点
	int i = 0;
	int Min = MAX;
	for (i = 1; i <= Size; i++)
		if (HT[i].arcs < Min && HT[i].parent == 0)
		{
			*s1 = i;
			Min = HT[i].arcs;
		}
	HT[*s1].parent = 1;
	Min = MAX;
	for (i = 1; i <= Size; i++)
		if (HT[i].arcs < Min && HT[i].parent == 0)
		{
			*s2 = i;
			Min = HT[i].arcs;
		}
	HT[*s2].parent = 1;
}
void Preorder_Traversal(HuffmanTree HT, int n, char* t) //遍历树，并且打印结点信息，n为节点数，t为字符表
{
	SqStack S;
	InitStack(S);
	int i = 2 * n - 1;
	int j = 0;									//防止i的改变对后续操作造成影响，用j代替i循环计算层数
	int count = 0;								//count用于计算结点的层数
	while (i != NULL || !StackEmpty(S))
	{
		if (i)
		{
			if (i <= n) printf("叶子结点：%c	", t[i - 1]);
			else printf("中间节点	");
			printf("权重为:%d	", HT[i].arcs);
			if (HT[i].rchild)
				printf("节点的度为:2	");
			else if (HT[i].lchild)
				printf("节点的度为:1	");
			else
				printf("节点的度为:0	");
			j = i;
			for (count = 1; HT[j].parent; j = HT[j].parent, count++);
			printf("节点的层数为:%d\n", count);
			Push(S, i);
			i = HT[i].lchild; 					//移动到左孩子 
		}
		else									//该条树枝左节点遍历完了，返回上一个结点，从而遍历右节点
		{
			i = Pop(S);
			i = HT[i].rchild;					//处理右结点 
		}
	}//while
	DestoryStack(S);
}

int HuffmanDecoding(HuffmanTree HT, char* HFM, int n, char* Sort)//解码，HFM为代译码
{
	int m = 2 * n - 1;                 //n为节点个数
	int i = m;                         //初始化
	int j = 0;
	if (strlen(HFM) == 1)              //对译码只有1位数字的特殊情况给出判断
	{
		if (strlen(Sort) != 2)
		{
			printf("\nERROR_03"); return ERROR;
		}
		if (strlen(Sort) == 2)
		{
			if (HFM[0] == '0') printf("%c", Sort[0]);
			else if (HFM[0] == '1') printf("%c", Sort[1]);
			else printf("\nERROR_03"); return ERROR;
		}//if
	}//if只有一位
	for (j = 0; j < strlen(HFM); j++) //遍历除最后一个节点所有节点
	{
		if (HFM[j] == '0')                //走向左孩子
		{
			i = HT[i].lchild;
			if (HT[i].lchild == 0)        //判断是否为叶子节点
			{
				if (i > n)
				{
					printf("\nERROR_03"); return ERROR;
				}
				printf("%c", Sort[i - 1]);
				i = m;//置回最初
			}
		}
		else if (HFM[j] == '1')       //走向右孩子
		{
			i = HT[i].rchild;
			if (HT[i].lchild == 0)    //判断是否为叶子节点
			{
				if (i > n)
				{
					printf("\nERROR_03"); return ERROR;
				}
				printf("%c", Sort[i - 1]);
				i = m;//置回最初
			}
		}
		else
		{
			printf("\nERROR_03"); return ERROR;
		}
	}//for
	return OK;
}

int Huffmancodeing(HuffmanTree HT, HuffmanCode HC, int* weight, int n, char* Sort, char* str, char* Decode, int MAX)//weight为权值，n为不同字符个数，即节点数，sort为不同字符表，str为原输入串，decode为01串,max为原串长度
{
	int i, j, s1, s2;                          //s1，s2为节点序号
	char* cd;                                  //cd数组用于从叶子到根逆向求每个字符的哈夫曼编码
	if (n <= 1)                                //节点数量不够则编码失败
	{
		printf("ERROR_03");
		return ERROR;
	}
	int m = 2 * n - 1;                         //初始化
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//分配存储空间，0号单元未用
	if (!HT) return OVERFLOW;		//存储分配失败 
	for (i = 1; i <= n; i++)
	{//初始化
		HT[i].arcs = weight[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{//初始化
		HT[i].arcs = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{//建哈夫曼树，在HT[1..i-1]选择parent为0且权重最小的两个节点，其序号分别为s1和s2
		Select(HT, i - 1, &s1, &s2, MAX);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].arcs = HT[s1].arcs + HT[s2].arcs;
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));//初始化哈夫曼表
	if (!HC) return OVERFLOW;		                  //存储分配失败 
	cd = (char*)malloc(n * sizeof(char));             //分配求编码的工作空间 
	if (!HC) return OVERFLOW;	                      //存储分配失败 
	cd[n - 1] = '\0';                                 //添加结束符
	for (i = 1; i <= n; i++)
	{
		int start = n - 1;                            //编码结束符位置 
		int child, father;							  //循环变量
		for (child = i, father = HT[i].parent; father != 0; child = father, father = HT[father].parent)//从叶子到根逆向求编码
		{
			if (HT[father].lchild == child) cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);                                         //释放工作空间
	//哈夫曼表完成
	Preorder_Traversal(HT, n, Sort);							  //遍历哈夫曼树，输出节点……
	for (i = 0; i < strlen(str); i++)
	{
		for (j = 0; j < strlen(Sort); j++)
		{
			if (str[i] == Sort[j])
			{
				printf("%s", HC[j + 1]);//输出原字符串的哈夫曼码
				break;
			}
		}
	}
	printf(" ");
	HuffmanDecoding(HT, Decode, strlen(Sort), Sort);//输出代译码的字符
	free(HT);//释放工作空间
	free(HC);
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 3)                            //命令行参数错误则返回ERROR
	{
		printf("ERROR_01"); return ERROR;
	}
	int Weight[MaxStrlen];
	int MAX = strlen(argv[1]);//待编码长度
	int n;
	int i, j, k;                              //循环变量
	HuffmanTree HT;
	HuffmanCode HC;
	HT = (HuffmanTree)malloc(sizeof(HTNode)); //初始化哈夫曼树
	HC = (HuffmanCode)malloc(sizeof(char*));  //初始化哈夫曼表
	for (i = 0; i < MaxStrlen; i++)     //初始化权值数组
		Weight[i] = 1;
	char* str = (char*)malloc(strlen(argv[1]) * sizeof(char));
	strcpy(str, argv[1]);                     //str接收命令行输入的待编码字符串
	char* str_decoding = (char*)malloc(strlen(argv[2]) * sizeof(char));
	strcpy(str_decoding, argv[2]);            //str_decoding用于接收命令行输入的待译码字符串
	if (strlen(str) < 20)                     //字符串长度小于20则返回ERROR
	{
		printf("ERROR_02"); return -1;
	}
	char sorting[MaxStrlen] = { '\0' }; //定义sorting接收字符串中不同元素并初始化
	sorting[0] = str[0];
	for (i = 1; i < strlen(str); i++)
	{
		k = 0;//k标志str[i]中元素是否已经存入sorting
		for (j = 0; sorting[j]; j++)
		{
			if (str[i] == sorting[j])
			{
				Weight[j]++;//记录每个元素数量，即权值
				k = 1;
			}
		}
		if (k == 0) sorting[j] = str[i];
	}
	int temp = 0;						    //用作排序交换的中间变量
	for (i = 0; i < strlen(sorting); i++)//冒泡排序 按ASCII码重排权值和sorting
	{
		for (j = i + 1; j < strlen(sorting); j++)
		{
			if (sorting[j] < sorting[i])
			{
				temp = sorting[i];
				sorting[i] = sorting[j];
				sorting[j] = temp;
				temp = Weight[i];
				Weight[i] = Weight[j];
				Weight[j] = temp;
			}
		}
	}
	//进行哈夫曼编码并按照格式输出编码
	Huffmancodeing(HT, HC, Weight, strlen(sorting), sorting, str, str_decoding, MAX);
	return OK;
}
