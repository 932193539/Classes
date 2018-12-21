#include "StackTest.h"
using namespace std;

#define stack_size 50

StackTest *test;

typedef struct Stack
{
	int elem[stack_size];
	int top;
}seqStack;

//初始化
void InitStack(seqStack *s)
{
	s->top = -1;
}

//入栈
int Push(seqStack *s,int i)
{
	if(s->top == stack_size - 1) return false;
	s->top ++;
	s->elem[s->top] = i;
	return true;
}

//出栈
int pop(seqStack *s,int *i)
{
	if(s->top == -1)
		return false;
	else
	{
		*i = s->elem[s->top]; 
		s->top --;
		return true;
	}
}

//获取栈顶元素
int getTop(seqStack *s,int *i)
{
	if(s->top == -1)
		return false;
	else{
		*i = s->elem[s->top];
		return true;
	}
}

StackTest::StackTest(){}
StackTest::~StackTest(){}

StackTest* StackTest::getInstance()
{
	if (!test)
    {
        test = new StackTest();
    }
	init();
    return test;
}

void StackTest::init()
{
	//两种开辟空间方式的区别在哪???
	//*l = (LinkList)malloc(sizeof(Node));
	seqStack *stack = new Stack;
	InitStack(stack);
	Push(stack,1);
	Push(stack,2);
	Push(stack,3);
	Push(stack,91);

	int a = 9;
	pop(stack,&a);
	int b = 9;
	getTop(stack,&b);

	int end = 1;
}











