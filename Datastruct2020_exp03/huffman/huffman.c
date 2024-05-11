#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 200
#define MAXSIZE 500
//��ʼ���������ж�malloc�Ƿ�ɹ���freeָ��ǰ�ж�ָ���Ƿ�Ϊ�գ�֮���Ƿ�free�ɹ�
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree;//��̬�������鴢��շ�����
typedef char** HuffmanCode;//��̬�������鴢��շ��������

//str�����룬�ַ���
//n�������Ȩ�ط����ַ���
//count�������Ȩ������
void frequency(char str[],int *n,int *count) {//ͳ�Ƹ��ַ�Ȩ�أ�nΪȨ�ط�0�ַ�������Ȩ�ش���������count��
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

//HT�����룬���ڹ���ĺշ�����
//i�����룬iΪĿǰ�ѹ��������
//s1��s2���������С���ڵ㣬��s1��ӦȨ��С��s2
//���ã��ҵ�������С���ڵ���Ϊ��������
void Select(HuffmanTree HT, int i, int* s1, int* s2) {//ѡ��������С���ڵ���Ϊ������������������С��������
	int min1, min2, k, j = 0;//��s1δ����ֵ��jΪ0����s1��ֵ��s2δ��ֵ��jΪ1
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

//n�����룬Ȩ�ط����ַ���
//HT��������շ�����
//HC��������շ�������Ӧ�ĺշ�������
//w��������ַ���ӦȨֵ��>0����ɵ�����
//���ã����ɺշ������ͺշ�������
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, int* w, int n) {//w���n���ַ�Ȩֵ��>0������շ�����HT�������Ӧ�շ�������HC
	if (n <= 0)return;
	int m = 2 * n - 1;//�շ�����������
	(*HT) = (HuffmanTree)malloc(m * sizeof(HTNode));
	HuffmanTree p = (*HT);
	int i;
	for (i = 0; i < n; ++i, ++p, ++w) {//��ʼ��p����ÿ���ڵ�����Һ���Ϊ-1
		p->weight = *w;
		p->parent = 0;
		p->lchild = p->rchild = -1;
	}
	for (; i < m; ++i, ++p) {//��ʼ��p�����ɽڵ�����Һ���Ϊ0
		p->weight = p->parent = p->lchild = p->rchild = 0;
	}
	for (i = n; i < m; ++i) {//�����շ�����
		unsigned int s1, s2;
		Select((*HT), i, &s1, &s2);
		(*HT)[s1].parent = i; (*HT)[s2].parent = i; (*HT)[i].lchild = s1; (*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	(*HC) = (char**)malloc(n * sizeof(char*));//����n���ַ������ͷָ������
	char* cd = (char*)malloc(n * sizeof(char));//���������Ĺ����ռ�
	cd[n - 1] = '\0';//���������
	int start, f, c;
	for (i = 0; i < n; ++i) {//����ַ���շ�������
		start = n - 1;
		for (c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent) {//���������
			if ((*HT)[f].lchild == c) cd[--start] = '0';//���������ֱ�Ϊ0��1
			else cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));//Ϊ��i���ַ�����ռ�
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);//�ͷŹ����ռ�
}//HuffmanCoding

//HT�����룬������ɵĺշ�����
//n�����룬Ȩ�ط����ַ���
//w�����룬�ַ���Ӧ��Ȩֵ��>0����ɵ�����
//c�����룬����Ȩֵ���ַ���ɵ�����
//���ã���������շ�����
void preorder(HuffmanTree HT,int n,int w[],char c[]) {//��������շ�����HT
	int ccount1[LENGTH] = { 0 };//ͳ��ÿ������ڱ����з��ʴ���
	int ccount2 = 0;//ͳ�ƽ���������
	int i = 2 * n - 2;//��ʼλ��ΪHT�ĸ�
	while (ccount2 < 2 * n - 1) {
		if (HT[i].lchild != -1) {//�ý��Ϊ���ɽ��
			if (ccount1[i] == 0) {//δ����
				printf("��㣺%3c\tȨ�أ�%3d\t�ȣ�2\n", c[i], w[i]);
				ccount1[i]++;
				ccount2++;
				i = HT[i].lchild;
			}
			else if (ccount1[i] == 1) {//�ѷ��ʸý��������
				ccount1[i]++;
				i = HT[i].rchild;
			}
			else if (ccount1[i] == 2){//�ѷ��ʸý����������
				i = HT[i].parent;
			}
		}
		else {
			printf("��㣺%3c\tȨ�أ�%3d\t�ȣ�0\n", c[i], w[i]);
			i = HT[i].parent;
			ccount2++;
		}
	}//while
}//preorder

//������������
//argc�����룬�����в����ĸ���
//argv�����룺�����в���������
//����ֵ���������еı�ʾ״̬
int main(int argc ,char *argv[]) {
	//������������
	if (argc != 3){
		printf("ERROR_01"); 
		return 0;
	}
	if (strlen(argv[1]) < 20){//�ַ�������С��20
		printf("ERROR_02");
		return 0;
	}
	int w[MAXSIZE] = { 0 }, n = 0;//��ʼ��
	char str[MAXSIZE] = "0123";
	strcpy_s(str, MAXSIZE,argv[1]);
	str[strlen(str)] = '\0';
	int count[LENGTH] = { 0 };
	char* c = (char*)malloc(n * sizeof(char));
	int i;
	frequency(str, &n, count);
	//����ʧ��
	if (n <= 1) {//����ʧ�ܣ����ERROR_02
		printf("ERROR_02");
		return 0;
	}
	int j = 0;
	for (i = 0; i <= n - 1; i++) {//����Ȩ�غ���Ӧ�ַ�������ֱ��������w��Ȩ�ؾ�>0����c��
		for (; j < LENGTH; j++) {
			if (count[j] != 0) {
				w[i] = count[j];
				c[i] = (char)j;
				j++;
				break;
			}
		}
	}//for
	HuffmanTree HT;//����շ�����HT�ͺշ�������HC
	HuffmanCode HC;
	HuffmanCoding(&HT, &HC, w, n);
	for (i = n; i <= 2*n - 2; i++)//����c��n��2*n-2λ��㶨��Ϊ��#��
		c[i] = '#';
	c[i] = '\0';
	for (i = n; i <= 2 * n - 2; i++)//����շ�����������Ȩ��
		w[i] = w[HT[i].lchild] + w[HT[i].rchild];
	w[i] = '\0';
	preorder(HT, n, w, c);//�������
	char res[LENGTH][MAXSIZE] = {'0'};//�շ�������HCת��Ϊ��ά�ַ�����res
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
	for (int ptr = 0; ptr < strlen(str); ptr++) {//����շ���������
		printf("%s", res[((int)str[ptr])]);
	}
	printf(" ");
	char dec[MAXSIZE] = {0};//�����ַ�����ʼ��
	strcpy_s(dec, MAXSIZE, argv[2]);
	dec[strlen(dec)] = '\0';
	char* s = dec;
	int p;
	while (*s != '\0') {
		//����ʧ��
		if (*s != '0' && *s != '1'){
			printf("\nERROR_03");//����ʧ�ܣ����ERROR_03
			return 0;
		}
		p = 2 * n - 2;
		while (HT[p].lchild != -1 || HT[p].rchild != -1) {
			if (*s == '0') p = HT[p].lchild;
			else p = HT[p].rchild;
			++s;
		}
		printf("%c", c[p]);//�����������������
	}
	//����ʧ��
	if (HT[p].lchild != -1 || HT[p].rchild != -1) {//����ʧ�ܣ����ERROR_03
		printf("\nERROR_03");
		return 0;
	}
	free(HT);//freeǰ���ж��Ƿ�Ϊ��
	free(HC);
	return 0;
}