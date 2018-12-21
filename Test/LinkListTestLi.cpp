#include "LinkListTestLi.h"
#include <thread>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <mutex>
using namespace std;

LinkListTestLi *test;

typedef struct NodeLi
{
	char data;
	NodeLi *next;
}* structLinkList;


void initList(structLinkList* l)
{
	*l = (structLinkList)malloc(sizeof(NodeLi));
	(*l)->next = NULL;
}

//头插法设置数据
void CreateFromHead(structLinkList* l,char *a)
{
	for (int i = 0; i < strlen(a); i++)
	{
		structLinkList temp = (structLinkList)malloc(sizeof(NodeLi));
		temp->data = a[i];
		temp->next = (*l)->next;
		(*l)->next = temp;
	}
}

//尾插法设置数据
void CreateFromTail(structLinkList* l,char *a)
{
	auto temp = *l;
	for (int i = 0; i < strlen(a); i++)
	{
		structLinkList n = (structLinkList)malloc(sizeof(NodeLi));
		n->data = a[i];
		n->next = temp->next;
		temp->next = n;
		temp = n;
	}
}

//在单链表L中查找第i个结点
NodeLi * Get(structLinkList* l,int i)
{
	auto num = 0;
	auto temp = (*l);
	while (temp->next != NULL)
	{
		temp = temp->next;
		if(num++ == i)
			return temp;
	}
	return NULL;
}

//根据value查找结点
NodeLi* Locate(structLinkList l,char key)
{
	auto temp = l;
	while (temp->next != NULL)
	{
		temp = temp->next;
		if(temp->data == key)
			return temp;
	}
	return NULL;
}


//链表长度
int ListLength(structLinkList l)
{
	auto sum = 0;
	auto temp = l;
	while (temp->next != NULL)
	{
		temp = temp->next;
		sum ++;
	}
	return sum;
}

//在指定位置插入元素
void InsList(structLinkList l,int i,char key)
{
	auto sum = 0;
	auto temp = l;
	while (temp->next != NULL)
	{
		sum++;
		temp = temp->next;
		
		if(sum == i)
		{
			structLinkList n = (structLinkList)malloc(sizeof(NodeLi));
			n->data = key;
			n->next = temp->next;
			temp->next = n;
			break;
		}
	}
}

LinkListTestLi::LinkListTestLi(){}
LinkListTestLi::~LinkListTestLi(){}

LinkListTestLi* LinkListTestLi::getInstance()
{
	if (!test)
    {
        test = new LinkListTestLi();
    }
	init();
    return test;
}

void LinkListTestLi::init()
{
	structLinkList l = nullptr;
	initList(&l);
	CreateFromHead(&l,"65321");
	auto a = Get(&l,3);
	auto b = Locate(l,'3');
	auto c = ListLength(l);
	InsList(l,3,'4');


	/*
		(*(&l))->next;
		(*l).next;
		l->next;
	*/

	int end = 1;
}









