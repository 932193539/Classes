/**
多线程功能测试
**/

#include "WindowsThreadTest.h"
#include <iostream>   
#include <windows.h>   
#include <fstream>
using namespace std;

WindowsThreadTest *test;
WindowsThreadTest::WindowsThreadTest(){}
WindowsThreadTest::~WindowsThreadTest(){}

WindowsThreadTest* WindowsThreadTest::getInstance()
{
	if (!test)
    {
        test = new WindowsThreadTest();
    }
	init();
    return test;
}

HANDLE hMutex = NULL;//互斥量

DWORD WINAPI Fun(LPVOID lpParamter)
{
    for (int i = 0; i < 10; i++)
	{
		//请求一个互斥量锁
		WaitForSingleObject(hMutex, INFINITE);
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"A Thread Fun Display!"<<endl;
		Sleep(100);
		//释放互斥量锁
		ReleaseMutex(hMutex);
	}
    return 0L;
}

void WindowsThreadTest::init()
{
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	hMutex = CreateMutex(NULL, FALSE,(LPCWSTR)"screen");
    CloseHandle(hThread);
    for (int i = 0; i < 10; i++)
	{
		//请求一个互斥量锁
		WaitForSingleObject(hMutex, INFINITE);
		ofstream f1("D:\\me.txt",ios::app);
		f1<<"Main Thread Display!"<<endl;
		Sleep(100);
		//释放互斥量锁
		ReleaseMutex(hMutex);
	}

	int end = 1;
}









