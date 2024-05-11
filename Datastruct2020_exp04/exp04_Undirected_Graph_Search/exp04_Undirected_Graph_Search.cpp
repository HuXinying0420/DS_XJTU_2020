// exp04_Undirected_Graph_Search.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#define MAX         13			    // 矩阵最大容量
#define INF        100000 // 无穷大(((unsigned int)(-1)) >> 1)
#define FALSE -1
#define TRUE 1
typedef struct {			// 邻接矩阵
	int vexnum;				// 顶点数
	int arcs[MAX][MAX];   //带权邻接矩阵
}MGraph;

int name_to_int(char place[]) {//当v0==-1时输入地点不正确
	int v0 = -1;
	if (strcmp(place, "北门") == 0) {
		v0 = 0;
	}
	if (strcmp(place, "饮水思源") == 0) {
		v0 = 1;
	}
	if (strcmp(place, "腾飞塔") == 0) {
		v0 = 2;
	}
	if (strcmp(place, "图书馆") == 0) {
		v0 = 3;
	}
	if (strcmp(place, "教学主楼") == 0) {
		v0 = 4;
	}
	if (strcmp(place, "活动中心") == 0) {
		v0 = 5;
	}
	if (strcmp(place, "南门") == 0) {
		v0 = 6;
	}
	if (strcmp(place, "宪梓堂") == 0) {
		v0 = 7;
	}
	if (strcmp(place, "西迁馆") == 0) {
		v0 = 8;
	}
	if (strcmp(place, "传送门1") == 0) {
		v0 = 9;
	}
	if (strcmp(place, "传送门2") == 0) {
		v0 = 10;
	}
	if (strcmp(place, "传送门3") == 0) {
		v0 = 11;
	}
	if (strcmp(place, "传送门4") == 0) {
		v0 = 12;
	}
	return v0;
}

void ShortestPath_DIJ(MGraph G, int v0, int vd) {//v0为初始点，vd为目的地
	int v = 0, w = 0, i = 0;
	int final[MAX] = { 0 };		//final[i]=TRUE表示已经求得v0到i的最短路径
	int Path[MAX][MAX] = { 0 };	//Path[i][j]=TRUE表示从"顶点v0"到i的当前最短路径包含顶点j
	int D[MAX] = { INF };      // D[i]表示当前从"顶点v0"到i的最短路径长度
	// 初始化
	for (v = 0; v < G.vexnum; ++v) {
		final[v] = FALSE;// 顶点v的最短路径还没获取到
		for (w = 0; w < G.vexnum; ++w) Path[v][w] = FALSE; //设空最短路径
		D[v] = G.arcs[v0][v];// 顶点v的最短路径为"顶点v0"到"顶点i"的权
		if (D[v] < INF) {
			Path[v][v0] = TRUE;
			Path[v][v] = TRUE;
		}//if
	}//for
	D[v0] = 0;
	final[v0] = TRUE;//初始化v0,属于S集
	//开始主循环，每次求得v0到某个顶点的最短路径并加v到S集
	int min = INF;
	int s = 0;//s作为标记
	int m = 0;
	for (i = 1; i < G.vexnum; ++i) {// 遍历G.vexnum-1次,在未获取最短路径的顶点中，找到离v0最近的顶点(k)。
		min = INF;
		for (w = 0; w < G.vexnum; ++w)
			if (final[w] != 1)//w在V-S中
				if (min > D[w]) {//w离v0更近
					s = w;
					min = D[w];
				}
		final[s] = TRUE;//离v0最近的v加入S			
		for (w = 0; w < G.vexnum; ++w)//更新当前最短路径及距离
			if (final[w] != 1 && (min + G.arcs[s][w] < D[w])) {
				D[w] = min + G.arcs[s][w];
				for (m = 0; m < G.vexnum; m++) Path[w][m] = Path[s][m];
				Path[w][w] = TRUE;
			}//if		
	}//for
	//地名字符串数组
	char name[MAX][MAX] = { "北门","饮水思源","腾飞塔","图书馆","教学主楼","活动中心","南门","宪梓堂","西迁馆","传送门1","传送门2","传送门3","传送门4" };
	// 打印dijkstra最短路径的结果
	if (D[vd] != INF) {//有最短路径
		int k = 1;
		int j = 0;
		int min = INF;
		int tmp = v0;
		if (v0 == vd) {
			printf("%s->%s", name[v0], name[vd]);
		}
		else {
			while (k == 1) {
				if (tmp != vd) {
					printf("%s->", name[tmp]);
				}
				else {
					printf("%s", name[tmp]);
				}
				Path[vd][tmp] = 0;//已输出该路径，删除
				k = 0;
				for (j = 0; j < MAX; j++) {//求中间经过地点tmp
					if (Path[vd][j] == 1 && D[j] != INF && D[j] < min) {
						min = D[j];
						tmp = j;
						k = 1;
					}
				}
				min = INF;
			}//while
		}
		printf("\n%d", D[vd]);
	}
}//ShortestPath_DIJ

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR_01");
		return -1;
	}
	char start[MAX] = { '0' }, destination[MAX] = { '0' };
	strcpy_s(start, MAX, argv[1]);
	strcpy_s(destination, MAX, argv[2]);
	int c1 = name_to_int(start);
	int c2 = name_to_int(destination);
	MGraph G = {
	MAX,//顶点数
	{
			//             北门   饮水思源     腾飞塔     图书馆     教学主楼    活动中心    南门    宪梓堂    西迁馆    传送门1    传送门2    传送门3    传送门4
			/*北门*/     {   0,		  18, 	      INF,   	INF, 		INF,  		INF,  	   INF,	   INF,	    INF,	   INF,		  INF,		  22,		INF},
			/*饮水思源*/ {  18,        0,		   19, 		INF, 		INF,   		INF, 	   INF,    INF,		INF,	    27,		  INF,		 INF,		INF},
			/*腾飞塔*/   { INF,       19,		    0, 		 23, 		INF,   		INF, 	   INF,    INF,		INF,	   INF,		  INF,		   4,		 32},
			/*图书馆*/   { INF,      INF,		   23, 		  0, 	     15,   		INF, 	   INF,    INF,		INF,	     4,		    4,		 INF,		INF},
			/*教学主楼*/ { INF,      INF,		  INF, 		 15, 		  0,   		 21, 	   INF,      8,		INF,	   INF,		  INF,		 INF,		INF},
			/*活动中心*/ { INF,      INF,		  INF, 		INF, 		 21,   		  0, 	    30,    INF,		INF,	   INF,		  INF,		 INF,		INF},
			/*南门*/     { INF,      INF,		  INF, 		INF, 		INF,   		 30, 	     0,     14,		 20,	   INF,		   21,		 INF,		INF},
			/*宪梓堂*/   { INF,      INF,		  INF, 		INF, 		  8,   		INF, 	    14,      0,		INF,	   INF,		  INF,		 INF,		  4},
			/*西迁馆*/   { INF,      INF,		  INF, 		INF, 		INF,   		INF, 	    20,    INF,		  0,	   INF,		   43,		 INF,		INF},
			/*传送门1*/  { INF,       27,		  INF, 		  4, 		INF,   		INF, 	   INF,    INF,		INF,		 0,		  INF,		 INF,		INF},
			/*传送门2*/  { INF,      INF,		  INF, 		  4, 		INF,   		INF, 	    21,    INF,		 43,	   INF,		    0,		 INF,		INF},
			/*传送门3*/  {  22,      INF,		    4, 		INF, 		INF,   		INF, 	   INF,    INF,		INF,	   INF,		  INF,		  0,		INF},
			/*传送门4*/  { INF,      INF,		   32, 		INF, 		INF,   		INF, 	   INF,      4,		INF,	   INF,		  INF,		 INF,		  0}
				}//邻接矩阵
	};//G
	if (c1 != -1 && c2 != -1) {
		ShortestPath_DIJ(G, c1, c2);
	}
	else
		printf("ERROR_02");
	return 0;
}

