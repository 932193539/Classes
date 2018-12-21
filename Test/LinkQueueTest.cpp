#include "LinkQueueTest.h"
using namespace std;

LinkQueueTest *test;

typedef struct NodeTest
{
	int data;
	struct NodeTest *next;
}LinkQueueNode;

typedef struct
{
	LinkQueueNode * front;
	LinkQueueNode * rear;
}LinkQueue;

int LinkQueueInit(LinkQueue *Q)
{
	Q->front = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	if(Q->front != NULL)
	{
		Q->rear = Q->front;
		Q->front->next = NULL;
		return true;
	}
	return false;
}

int EnterQueue(LinkQueue *Q,int i)
{
	LinkQueueNode * newNode;
	newNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	if(newNode != NULL)
	{
		newNode->data = i;
		newNode->next = NULL;
		Q->rear->next = newNode;
		Q->rear = newNode;
	}
	return true;
}

int DeleteQueue(LinkQueue *Q,int *i)
{
	LinkQueueNode *p;
	p = Q->front->next;
	Q->front->next = p->next;
	*i = p->data;
	return true;
}

LinkQueueTest::LinkQueueTest(){}
LinkQueueTest::~LinkQueueTest(){}

LinkQueueTest* LinkQueueTest::getInstance()
{
	if (!test)
    {
        test = new LinkQueueTest();
    }
	init();
    return test;
}

void LinkQueueTest::init()
{
	//为什么 LinkQueueTest q = new LinkQueueTest;报错，这里new到底干什么用的
	LinkQueue *q = new LinkQueue;
	LinkQueueInit(q);
	EnterQueue(q,1);
	EnterQueue(q,2);
	EnterQueue(q,3);

	int a = 9;
	DeleteQueue(q,&a);

	int end = 1;
}

