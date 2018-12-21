/**
多线程功能测试
**/

#include "ThreadTest.h"
#include <thread>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <mutex>
using namespace std;
 
mutex mu;  //线程互斥对象
int totalNum = 100;

void thread01()
{
	for (int i = 0; i < 5; i++)
	{
		Sleep(100);
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"thread01"<<endl;
		f1.close();
	}
}

void thread02()
{
	for (int i = 0; i < 5; i++)
	{
		Sleep(200);	
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"thread02"<<endl;
		f1.close();
	}
}

void thread03(int num)
{
	for (int i = 0; i < num; i++)
	{
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"thread03"<<endl;
		Sleep(100);
	}
}

void thread04(int num)
{
	for (int i = 0; i < num; i++)
	{
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"thread04"<<endl;
		Sleep(200);
	}
}
 
void thread05()
{
	while (totalNum > 0)
	{
		mu.lock(); //同步数据锁
		ofstream f1("D:\\me.txt",ios::app);
		f1<<totalNum--<<endl;
		totalNum--;
		Sleep(100);
		mu.unlock();  //解除锁定
	}
}

void thread06()
{
	while (totalNum > 0)
	{
		mu.lock();
		ofstream f1("D:\\me.txt",ios::app);
		f1<<totalNum--<<endl;
		totalNum--;
		Sleep(100);
		mu.unlock();
	}
}

ThreadTest *test;
ThreadTest::ThreadTest(){}
ThreadTest::~ThreadTest(){}

ThreadTest* ThreadTest::getInstance()
{
	if (!test)
    {
        test = new ThreadTest();
    }
	init();
    return test;
}

void ThreadTest::init()
{
	/*
	thread task01(thread01);
	task01.join();
	thread task02(thread02);
	task02.join();
 
	for (int i = 0; i < 5; i++)
	{
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"Main thread is working1"<<endl;
		f1.close();		
		Sleep(200);
	}


	thread task03(thread03,5);
	thread task04(thread04,5);
	task03.detach();
	task04.detach();
	*/

 	thread task05(thread05);
	task05.join();
	thread task06(thread06);
	task06.join();

	for (int i = 0; i < 5; i++)
	{
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"Main thread is working2"<<endl;
		Sleep(150);
	}
	
	int end = 1;
}









