/**
多线程功能测试
**/

#include "TemplateClass.h"
#include <thread>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <mutex>
using namespace std;
 
TemplateClass *test;
TemplateClass::TemplateClass(){}
TemplateClass::~TemplateClass(){}

TemplateClass* TemplateClass::getInstance()
{
	if (!test)
    {
        test = new TemplateClass();
    }
	init();
    return test;
}

template <typename T>
class Complex{
    
public:
    //构造函数
    Complex(T a, T b):a(a),b(b)
    {}
    
    //运算符重载
    Complex<T> operator+(Complex &c)
    {
        Complex<T> tmp(a+c.a, b+c.b);
        return tmp;
    }

	int GetSummation()
	{
		return a+b;
	}
        
private:
    T a;
    T b;
};

void TemplateClass::init()
{
	//对象的定义，必须声明模板类型，因为要分配内容
    Complex<int> a(10,20);  
    Complex<int> b(20,30);
    Complex<int> c = a + b;
	int d = c.GetSummation();
	
	ofstream f1("D:\\me.txt",ios::app);
	f1<<d<<endl;

	int end = 1;
}
