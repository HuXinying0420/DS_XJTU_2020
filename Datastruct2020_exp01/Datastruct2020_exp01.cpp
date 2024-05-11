#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define STACK_INIT_SIZE 100//储存空间初始分配
#define STACKINCREMENT 10//储存空间分配增量
#define TRUE 1
#define ERROR -1
typedef struct { //运算符栈 
	char* base;//在栈构造之前和销毁之后，base的值为null
	char* top;//栈顶指针
	int stacksize;
}StackC;

typedef struct {//运算数栈 
	long double* base;//在栈构造之前和销毁之后，base的值为null
	long double* top;//栈顶指针
	int stacksize;
}StackN;

int InitStackC(StackC& S) {//构造一个运算符栈 
	S.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!S.base)
		return ERROR;//储存分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return TRUE;
} //InitStackC

long double InitStackN(StackN& S) {//构造一个运算数栈
	S.base = (long double*)malloc(STACK_INIT_SIZE * sizeof(long double));
	if (!S.base)
		return ERROR;//储存分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return TRUE;
}//InitStackN

int StackLength(StackC S) {//返回S的元素个数，即栈的长度 
	return S.top - S.base;
}//StackLength

char GetTopStackC(StackC S) {//若运算符栈不为空，用e返回栈顶元素
	char e;
	if (S.base == S.top)
		printf("ERROR_02");
	else
		e = *(S.top - 1);
	return e;
} //GetTopStackC

long double GetTopStackN(StackN S) {//若运算数栈不为空，用e返回栈顶元素
	long double e;
	if (S.base == S.top)
		printf("ERROR_02");
	else
		e = *(S.top - 1);
	return e;
}//GetTopStackN

int PushStackC(StackC& S, char e) {//插入运算符，e为新的栈顶元素
	if ((S.top - S.base) >= STACK_INIT_SIZE - 1)//栈满，追加储存空间 
	{
		S.base = (char*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
		if (!S.base)
			return ERROR;//储存分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return TRUE;
} //PushStackC

int PushStackN(StackN& S, long double e) {//插入运算数，e为新的栈顶元素
	if ((S.top - S.base) >= STACK_INIT_SIZE - 1)//栈满，追加储存空间 
	{
		S.base = (long double*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(long double));
		if (!S.base)
			return ERROR;//储存分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return TRUE;
} //PushStackN

int PopStackC(StackC& S, char& e) {//若栈不为空，则删除运算符栈S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return TRUE;
} //PopStackC

int PopStackN(StackN& S, long double& e) {//若栈不为空，则删除运算数栈S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return TRUE;
} //PopStackN

int ChartoInt(char a) {//将表达式的字符转化为数字 
	if (a == '+')
		return 1;
	if (a == '-')
		return 2;
	if (a == '*')
		return 3;
	if (a == '/')
		return 4;
	if (a == '^')
		return 5;
	if (a == '(')
		return 6;
	if (a == '[')
		return 7;
	if (a == '{')
		return 8;
	if (a == ')')
		return 9;
	if (a == ']')
		return 10;
	if (a == '}')
		return 11;
	if (a <= '9' && a >= '0')
		return 13;
	if (a == '#')
		return 12;
	if (a == '.')
		return 14;
	return 0;
}// ChartoInt

int Precede(char a, char b) {//利用优先级矩阵，比较运算符号的优先级 
	int i, j;
	i = ChartoInt(a) - 1;
	j = ChartoInt(b) - 1;
	int table[12][12] = {
	{1,1,-1,-1,-1,-1,-1,-1,1,1,1,1},
	{1,1,-1,-1,-1,-1,-1,-1,1,1,1,1},
	{1,1,1,1,-1,-1,-1,-1,1,1,1,1},
	{1,1,1,1,-1,-1,-1,-1,1,1,1,1},
	{1,1,1,1,1,-1,-1,-1,1,1,1,1},
	{-1,-1,-1,-1,-1,-1,-2,-2,0,-2,-2,-2},
	{-1,-1,-1,-1,-1,-1,-1,-2,-2,0,-2,-2},
	{-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,0,-2},
	{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
	{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
	{-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0}
	};
	return table[i][j];
}//Precede

long double Operate(long double a, char theta, long double b, int& Ver) {//对a,b运用符号theta进行计算
	switch (ChartoInt(theta))
	{
	case 1:
		return a + b;
		break;
	case 2:
		return a - b;
		break;
	case 3:
		return a * b;
		break;
	case 4:
		if (b == 0)
		{//若分母为0，则返回ERROR 
			Ver = 0;//逻辑错误输出字符串ERROR_03
			//printf("ERROR_03");
			return ERROR;
		}
		else return a / b;
		break;
	case 5:
		if (b == 0)
			return 1.0;
		else return pow(a, b);
		break;
	default:
		break;
	}//switch
}//Operate

long double EvaluateExpression(char* expression, int& Ver) {//表达式求值
	StackC OPTR;//运算符栈 
	StackN OPND;//运算数栈 
	int i = 0, ver = 1, z = 0;
	long double a, b, j, k;
	char c, x, theta;
	InitStackC(OPTR);//初始化运算符栈 
	PushStackC(OPTR, '#');//#的优先级最小，便于之后pop第一个运算符进入符栈
	InitStackN(OPND);//初始化运算数栈
	c = expression[i];
	while (c != '#' || GetTopStackC(OPTR) != '#')
	{
		j = 0, k = 1;
		while (ChartoInt(c) == 13)
		{//整数位读取 
			z++;
			j *= 10;
			j += (c - '0');
			c = expression[++i];
			if (c == '.')
			{//小数位读取 
				c = expression[++i];
				while (ChartoInt(c) == 13)
				{
					k /= 10;
					j += (c - '0') * k;
					c = expression[++i];
				}
			}//if
		}//while
		if (z != 0)
			PushStackN(OPND, j);//将读取到的运算数入运算数栈 
		z = 0;
		switch (Precede(GetTopStackC(OPTR), c))
		{
		case -1://栈顶运算符优先级低 
			PushStackC(OPTR, c);
			c = expression[++i];
			break;
		case 0://脱括号并接收下一字符
			PopStackC(OPTR, x);
			c = expression[++i];
			break;
		case 1://栈顶元素优先级高 
			PopStackC(OPTR, theta);
			PopStackN(OPND, b);
			PopStackN(OPND, a);
			PushStackN(OPND, Operate(a, theta, b, ver));
			if (ver == 0) Ver = 0;
			break;
		default:
			break;
		}//switch
	}//while
	return GetTopStackN(OPND);//返回计算结果 
}//EvaluateExpression

int State(char a) {//状态转移设定 
	if (ChartoInt(a) == 13)//将运算数字设为状态1 
		return 1;
	if (ChartoInt(a) > 0 && ChartoInt(a) < 6)//将运算符'+ - * / ^'设为状态2 
		return 2;
	if (ChartoInt(a) > 5 && ChartoInt(a) < 9)//将运算符'( [ {'设为状态3 
		return 3;
	if (ChartoInt(a) > 8 && ChartoInt(a) < 12)//将运算符') ] }'设为状态4 
		return 4;
	if (ChartoInt(a) == 14)//将小数点'.'设为状态5
		return 5;
	return 0;
}//State

int Check(int a, int b) {//字符之间关系检查，正确返回1，错误返回0
	if (a == 1 && (b == 1 || b == 2 || b == 4 || b == 5))
		return 1;
	if (a == 2 && (b == 1 || b == 3))
		return 1;
	if (a == 3 && (b == 1 || b == 3))
		return 1;
	if (a == 4 && (b == 2 || b == 4))
		return 1;
	if (a == 5 && b == 1)
		return 1;
	return 0;
}//Check

int Vertify(char* SString, int Str) {//表达式的正确性检验 正确返回1 错误返回0
	int i, k = 0;
	char e;
	if (State(SString[0]) != 1 && State(SString[0]) != 3)//开头必须为数字或左括号
		return 0;
	StackC(Sym);
	InitStackC(Sym);
	if (State(SString[0]) == 3)
		PushStackC(Sym, SString[0]);
	for (i = 1; i < Str - 1; i++)
	{
		if (SString[i] == '.')
		{
			if (State(SString[i - 1]) != 1 || State(SString[i + 1]) != 1)
				return 0;//小数点前后为数字
			continue;
		}
		if (State(SString[i]) == 3)
			PushStackC(Sym, SString[i]);//左括号入栈
		if (State(SString[i]) == 4) {
			if (ChartoInt(SString[i]) - 3 != ChartoInt(GetTopStackC(Sym)) || !GetTopStackC(Sym))//遇到右括号，符栈栈顶必为左括号
				return 0;
			else {
				if (ChartoInt(SString[i]) - 3 == ChartoInt(GetTopStackC(Sym)))
					PopStackC(Sym, e);
				else return 0;
			}
			if (ChartoInt(SString[i]) == 0 || ChartoInt(SString[i]) == 12)
				return 0;//不可能出现#或其他字符
		}
		if (Check(State(SString[k]), State(SString[i])) == 0)
			return 0;
		k = i;
	}//for
	if (State(SString[i - 1]) != 1 && State(SString[i - 1]) != 4)
		return 0;//数学表达式以数字或右括号结束
	if (SString[i] != '#')
		return 0;
	if (Str == 1)
		return 1;
	return 1;
}//Vertify

int main(int argc, char* argv[])
{
	printf("输入表达式：%s\n", argv[1]);
	int Ver = 1;
	char sstring[STACK_INIT_SIZE];//初始化字符串
	strcpy_s(sstring, (char*)argv[1]);
	int leng = strlen(sstring);
	sstring[leng++] = '#';
	sstring[leng] = '\0';
	if (argc == 0)
	{
		printf("ERROR_01\n");
		getchar();
		return -1;
	}
	long double answer;
	if (Vertify(sstring, leng) == 1){
		answer = EvaluateExpression(sstring, Ver);
		if (Ver == 0){
			printf("ERROR_03");
			return 0;
		}
		else {
			if (answer / 100000000 > 1 || answer / 100000000 < -1)
				printf("%10.0f", answer);
			else
				printf("%g", answer);
		}
	}
	else
	{
		printf("ERROR_02");
	}
	return 0;
}