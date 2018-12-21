/**
多线程功能测试
**/

#include "AutoPtr.h"
#include <thread>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <mutex>
using namespace std;
 
AutoPtr *test;
AutoPtr::AutoPtr(){}
AutoPtr::~AutoPtr(){}

AutoPtr* AutoPtr::getInstance()
{
	if (!test)
    {
        test = new AutoPtr();
    }
	init();
    return test;
}


//模拟实现auto_ptr
template<class T>
class Auto_ptr
{
public:

	//:_ptr(ptr)的意思是初始化类成员值 _ptr = ptr
	Auto_ptr(T*ptr):_ptr(ptr)//构造函数
	{}
	Auto_ptr(Auto_ptr<T>&ap)//拷贝构造
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}
	Auto_ptr<T>&operator=(Auto_ptr<T>&ap)//赋值运算符的重载
	{
		if (this != &ap)
		{
			if (_ptr)
			{
				delete _ptr;
			}
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}
	~Auto_ptr()//析构函数
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}

	T&operator*()
	{
		return *_ptr;
	}
	T*operator->()
	{
		return _ptr;
	}

private:
	T*_ptr;
};

struct AA
{
	int _a;
	int _b;
};


void AutoPtr::init()
{
	Auto_ptr<int> ap(new int(3));
	Auto_ptr<int> ap1(ap);
	Auto_ptr<int> ap2(ap);//一个Auto_ptr被拷贝或赋值后，其已经失去了对原对象的所有权，指为NULL

	Auto_ptr<AA>ap3(new AA);
	ap3->_a = 2;
	ap3->_b = 3;

	ofstream f1("D:\\me.txt",ios::app);
	f1<<&ap<<endl;
	f1<<&ap1<<endl;
	f1<<&ap2<<endl;


	int end = 1;
}
