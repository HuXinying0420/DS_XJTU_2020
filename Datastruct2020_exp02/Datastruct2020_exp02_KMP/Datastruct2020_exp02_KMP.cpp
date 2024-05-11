// hxy_exp02_KMP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iosTream>

#define MAXSTRING 10000 
#define INIT_LENGTH 100
#define TRUE 1
#define ERROR 0 
#define FALSE -1

typedef struct {//串的堆分配存储表示
	char *ch = NULL;
	int length;
}HString;

int StrAssign(HString &t, char *chars) {//生成一个值等于常量chars的串t
	int i = 0, j = 0;
	char* CHAR;
	CHAR = chars;
	if (t.ch)
		free(t.ch);
	for (i = 0, CHAR = chars; *CHAR; ++i, ++CHAR);//计算chars的长度
	if (!i){
		t.ch = NULL;
		t.length = 0;
	}
	else {
		int size = 1 + i;
		if (!(t.ch = (char*)malloc(size * sizeof(char))))
			return FALSE;
		for (j = 0; j < i; j++){//将串char的值赋给t.ch
			t.ch[j + 1] = chars[j];
		}
		t.length = i;
		t.ch[0] = i;//首位存放t的长度
	}
	return TRUE;
}//StrAssign
	
int ClearString(HString &s) {//将s清为空串
	if (s.ch){
		free(s.ch);
		s.ch = NULL;
	}
	s.length = 0;
	return TRUE;
}//ClearString

int Strcompare(HString S, HString T) {//若S>T，则返回值>0,若S=T，则返回值=0,若S<T，则返回值<0
	int i = 0;
	for (i = 0; i < S.length && i < T.length; ++i)
		if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return T.ch[i] - S.ch[i];
}//Strcompare

void Getnext(HString t, int next[]) {//得到next数组
	int i=1, j=0;
	next[1] = 0;
	while (i < t.length) {
		if (j == 0 || t.ch[i] == t.ch[j]){
			++i; ++j;
			if (t.ch[i] != t.ch[j])
				next[i] = j;
			else next[i] = next[j];
		}//if
		else j = next[j];
	}//while
}// Getnext

int Index_KMP(HString S, HString T, int pos) {//用模式串T的NEXT函数求主串中与模式串相对应的位置
	int i = 0, j = 1;
	i = pos;
	int next[INIT_LENGTH];
	memset(next,0, sizeof(next));
	Getnext(T, next);
	while (i <= S.length && j <= T.length){
		if (j == 0 || S.ch[i] == T.ch[j]){
			++i; ++j;
		}
		else j = next[j];
	}
	if (j > T.length)
		return i - T.length;
	else return FALSE;
}//Index_KMP
	
int main(int argc, char* argv[]) {
	int pos = 1, result = 0;
	if (argc != 3){
		printf("ERROR_01");
		return ERROR;
	}
	HString patternstring, mainstring;//mainstring为主串，patternstring为模式串
	patternstring.ch = NULL;
	patternstring.length = 0;
	mainstring.ch = NULL;
	mainstring.length = 0;
	StrAssign(mainstring, argv[1]);
	StrAssign(patternstring, argv[2]);
	result = Index_KMP(mainstring, patternstring, pos);
	printf("%d", result);
	ClearString(mainstring);
	ClearString(patternstring);
	return TRUE;
}
