#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 200
#define MAXSIZE 500
//初始化变量，判断malloc是否成功，free指针前判断指针是否为空，之后是否free成功
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree;//动态分配数组储存赫夫曼树
typedef char** HuffmanCode;//动态分配数组储存赫夫曼编码表

//str：输入，字符串
//n：输出，权重非零字符数
//count：输出，权重数组
void frequency(char str[],int *n,int *count) {//统计各字符权重，n为权重非0字符个数，权重储存在数组count中
	int i;
	for (i = 0; i < strlen(str); i++) {
		count[(int)str[i]]++;
	}
	for (i = 0; i < LENGTH; i++) {
		if (count[i] != 0) {
			(*n)++;
		}
	}
}//frequency

//HT：输入，正在构造的赫夫曼树
//i：输入，i为目前已构造结点个数
//s1，s2：输出，最小根节点，且s1对应权重小于s2
//作用：找到两个最小根节点作为左右子树
void Select(HuffmanTree HT, int i, int* s1, int* s2) {//选择两个最小根节点作为左右子树，且左子树小于右子树
	int min1, min2, k, j = 0;//若s1未被赋值，j为0，若s1赋值、s2未赋值，j为1
	for (k = 0; k <= i - 1; ++k) {
		if (HT[k].parent == 0){
			if (j == 0){
				min1 = HT[k].weight;
				*s1 = k;
			}
			else if (j == 1){
				if (HT[k].weight < min1) {
					min2 = min1;
					*s2 = *s1;
					min1 = HT[k].weight;
					*s1 = k;
				}
				else {
					min2 = HT[k].weight;
					*s2 = k;
				}
			}
			else {
				if (HT[k].weight < min1) {
					min2 = min1;
					*s2 = *s1;
					min1 = HT[k].weight;
					*s1 = k;
				}
				else if (HT[k].weight >= min1 && HT[k].weight < min2) {
					min2 = HT[k].weight;
					*s2 = k;
				}
			}
			++j;
		}//if
	}//for
}//Select

//n：输入，权重非零字符数
//HT：输出，赫夫曼树
//HC：输出，赫夫曼树对应的赫夫曼编码
//w：输出，字符对应权值（>0）组成的数组
//作用：生成赫夫曼树和赫夫曼编码
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, int* w, int n) {//w存放n个字符权值（>0）构造赫夫曼树HT并求出对应赫夫曼编码HC
	if (n <= 0)return;
	int m = 2 * n - 1;//赫夫曼树结点个数
	(*HT) = (HuffmanTree)malloc(m * sizeof(HTNode));
	HuffmanTree p = (*HT);
	int i;
	for (i = 0; i < n; ++i, ++p, ++w) {//初始化p，且每个节点的左右孩子为-1
		p->weight = *w;
		p->parent = 0;
		p->lchild = p->rchild = -1;
	}
	for (; i < m; ++i, ++p) {//初始化p，生成节点的左右孩子为0
		p->weight = p->parent = p->lchild = p->rchild = 0;
	}
	for (i = n; i < m; ++i) {//构建赫夫曼树
		unsigned int s1, s2;
		Select((*HT), i, &s1, &s2);
		(*HT)[s1].parent = i; (*HT)[s2].parent = i; (*HT)[i].lchild = s1; (*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	(*HC) = (char**)malloc(n * sizeof(char*));//分配n个字符编码的头指针向量
	char* cd = (char*)malloc(n * sizeof(char));//分配求编码的工作空间
	cd[n - 1] = '\0';//编码结束符
	int start, f, c;
	for (i = 0; i < n; ++i) {//逐个字符求赫夫曼编码
		start = n - 1;
		for (c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent) {//逆向求编码
			if ((*HT)[f].lchild == c) cd[--start] = '0';//左右子树分别为0和1
			else cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));//为第i个字符分配空间
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);//释放工作空间
}//HuffmanCoding

//HT：输入，构建完成的赫夫曼树
//n：输入，权重非零字符数
//w：输入，字符对应的权值（>0）组成的数组
//c：输入，非零权值的字符组成的数组
//作用：先序遍历赫夫曼树
void preorder(HuffmanTree HT,int n,int w[],char c[]) {//先序遍历赫夫曼树HT
	int ccount1[LENGTH] = { 0 };//统计每个结点在遍历中访问次数
	int ccount2 = 0;//统计结点输出次数
	int i = 2 * n - 2;//初始位置为HT的根
	while (ccount2 < 2 * n - 1) {
		if (HT[i].lchild != -1) {//该结点为生成结点
			if (ccount1[i] == 0) {//未访问
				printf("结点：%3c\t权重：%3d\t度：2\n", c[i], w[i]);
				ccount1[i]++;
				ccount2++;
				i = HT[i].lchild;
			}
			else if (ccount1[i] == 1) {//已访问该结点左子树
				ccount1[i]++;
				i = HT[i].rchild;
			}
			else if (ccount1[i] == 2){//已访问该结点左右子树
				i = HT[i].parent;
			}
		}
		else {
			printf("结点：%3c\t权重：%3d\t度：0\n", c[i], w[i]);
			i = HT[i].parent;
			ccount2++;
		}
	}//while
}//preorder

//参数数量错误
//argc：输入，命令行参数的个数
//argv：输入：命令行参数的内容
//返回值：程序运行的表示状态
int main(int argc ,char *argv[]) {
	//参数数量错误
	if (argc != 3){
		printf("ERROR_01"); 
		return 0;
	}
	if (strlen(argv[1]) < 20){//字符串长度小于20
		printf("ERROR_02");
		return 0;
	}
	int w[MAXSIZE] = { 0 }, n = 0;//初始化
	char str[MAXSIZE] = "0123";
	strcpy_s(str, MAXSIZE,argv[1]);
	str[strlen(str)] = '\0';
	int count[LENGTH] = { 0 };
	char* c = (char*)malloc(n * sizeof(char));
	int i;
	frequency(str, &n, count);
	//编码失败
	if (n <= 1) {//编码失败，输出ERROR_02
		printf("ERROR_02");
		return 0;
	}
	int j = 0;
	for (i = 0; i <= n - 1; i++) {//计算权重和相应字符，结果分别存入数组w（权重均>0）和c中
		for (; j < LENGTH; j++) {
			if (count[j] != 0) {
				w[i] = count[j];
				c[i] = (char)j;
				j++;
				break;
			}
		}
	}//for
	HuffmanTree HT;//定义赫夫曼树HT和赫夫曼编码HC
	HuffmanCode HC;
	HuffmanCoding(&HT, &HC, w, n);
	for (i = n; i <= 2*n - 2; i++)//数组c的n至2*n-2位结点定义为‘#’
		c[i] = '#';
	c[i] = '\0';
	for (i = n; i <= 2 * n - 2; i++)//计算赫夫曼树各结点的权重
		w[i] = w[HT[i].lchild] + w[HT[i].rchild];
	w[i] = '\0';
	preorder(HT, n, w, c);//先序遍历
	char res[LENGTH][MAXSIZE] = {'0'};//赫夫曼编码HC转换为二维字符数组res
	int k = 0;
	for (i = 0; i < n; i++) {
		for (; k < LENGTH; k++) {
			if (count[k] != 0) {
				for (j = 0; j < strlen(HC[i]); j++) {
					res[k][j] = HC[i][j];}
				res[k][j] = '\0';
				k++;
				break;
			}
		}
	}
	for (int ptr = 0; ptr < strlen(str); ptr++) {//输出赫夫曼编码结果
		printf("%s", res[((int)str[ptr])]);
	}
	printf(" ");
	char dec[MAXSIZE] = {0};//解码字符串初始化
	strcpy_s(dec, MAXSIZE, argv[2]);
	dec[strlen(dec)] = '\0';
	char* s = dec;
	int p;
	while (*s != '\0') {
		//解码失败
		if (*s != '0' && *s != '1'){
			printf("\nERROR_03");//解码失败，输出ERROR_03
			return 0;
		}
		p = 2 * n - 2;
		while (HT[p].lchild != -1 || HT[p].rchild != -1) {
			if (*s == '0') p = HT[p].lchild;
			else p = HT[p].rchild;
			++s;
		}
		printf("%c", c[p]);//输出计算结果：解码结果
	}
	//解码失败
	if (HT[p].lchild != -1 || HT[p].rchild != -1) {//解码失败，输出ERROR_03
		printf("\nERROR_03");
		return 0;
	}
	free(HT);//free前需判定是否为空
	free(HC);
	return 0;
}