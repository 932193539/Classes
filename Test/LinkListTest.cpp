#include "LinkListTest.h"
using namespace std;

LinkListTest *test;

typedef struct Node{
	char data;
	struct Node *next;

}Node,* LinkList;

//初始化单链表
void initList(LinkList* l)
{
	*l = (LinkList)malloc(sizeof(Node));
	(*l)->next = NULL;
}

//头插法设置数据
void CreateFromHead(LinkList* l,char *a)
{
	auto length = strlen(a);
	for (int i = 0; i < length; i++)
	{
		Node *n = (Node *)malloc(sizeof(Node));
		n->data = a[i];
		n->next = (*l)->next;
		(*l)->next = n;
	}
}

//尾插法设置数据
void CreateFromTail(LinkList* l,char *a)
{
	auto length = strlen(a);
	Node *temp = *l;
	for (int i = 0; i < length; i++)
	{
		Node *n = (Node *)malloc(sizeof(Node));
		n->data = a[i];
		n->next = temp->next;
		temp->next = n;
		temp = n;
	}
}

//在单链表L中查找第i个结点
Node * Get(LinkList* l,int i)
{
	int j = 0;
	Node *temp = *l;

	while(j < i)
	{
		temp = temp->next;
		j++;
	}
	return temp;
}

//根据value查找结点
Node * Locate(LinkList L,char key)
{
	Node *p = L->next;
	while (p->next != NULL)
	{
		if(p->data == key)
		{
			return p;
			break;
		}else
		{
			p = p->next;
		}
	}

	return NULL;
}

//链表长度
int ListLength(LinkList l)
{
	Node *p;
	p = l->next;
	int i = 0;
	while (p->next != NULL)
	{
		p = p->next;
		i++;
	}
	return i;
}

//在指定位置插入元素
void InsList(LinkList l,int i,char key)
{
	Node *p;
	p = l;
	int id = 0;
	while(p->next != NULL)
	{
		if(id++ == i)
		{
			Node *n = new Node;
			Node *temp;
			temp = p->next;
			n->data = key;
			p->next = n;
			n->next = temp;
			break;
		}
		p = p->next;
	}

}

LinkListTest::LinkListTest(){}
LinkListTest::~LinkListTest(){}

LinkListTest* LinkListTest::getInstance()
{
	if (!test)
    {
        test = new LinkListTest();
    }
	init();
    return test;
}

void LinkListTest::init()
{
	LinkList l = nullptr;
	initList(&l);
	CreateFromHead(&l,"65321");
	//auto a = Get(&l,3);
	//auto b = Locate(l,'3');
	//auto c = ListLength(l);
	InsList(l,3,'4');

	int end = 1;
}













