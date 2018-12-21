/****************************************************************************
在进入一个文件夹时,把当前文件夹作为父节点,进入后的所有文件作为子结点
在进入一个文件时,创建一个新的树并与之前的树设置关联
****************************************************************************/
#include "FileTools.h"
#include<iostream>
#include <string>
#include <io.h>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

static FileTools *ft = nullptr;

FileTools::FileTools()
{
	pathDepth = 0;
	fileCount = 0;
	memset(&currentPath, 0, sizeof(currentPath));
}
FileTools::~FileTools(){}

FileTools* FileTools::getInstance()
{
	if (!ft)
    {
        ft = new FileTools();
        ft->init();
    }

    return ft;
}

void FileTools::init()
{
}

//获取当前文件内容
string* FileTools::getCurrentFileSubContent()
{
	fileCount = 0;
    string path = getcurrentPath();

    char szTest[1000] = {0};  
    int len = 0;  
  
	FILE *fp = fopen(path.c_str(), "r");  
    if(NULL == fp)  
    {  
        printf("failed to open dos.txt\n");  
    }  
  
	int i = 0;
    while(!feof(fp))  
    {  
        fgets(szTest, sizeof(szTest) - 1, fp); // 包含了\n  
		fileList[i] = szTest;
		auto t = fileList[i].find("\n");
		if(fileList[i].find("\n") < 999)
		{
			fileList[i] = fileList[i].replace(fileList[i].find("\n"), fileList[i].length(), ""); 
		}
		i++;
    }  
  
	fileCount = i;
    fclose(fp);  
	return fileList;
}

//获取当前目录的子目录
string* FileTools::getCurrentDirSubDir()
{
	//清空结构体数组
	//memset(&fileList, 0, sizeof(fileList));
	fileCount = 0;
    string path = getcurrentPath();
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;
	// \\* 代表要遍历所有的类型
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) 
	{

	}
	do{
		if (fileInfo.name[0] != (char)'.')
		{
			//判断文件的属性是文件夹还是文件
			CCLOG(fileInfo.name);
			fileList[fileCount] = fileInfo.name;
			fileCount ++;
		}

	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return fileList;
}

//判断当前位置是文件还是路径
bool FileTools::isDir()
{
	return GetFileAttributesA(getcurrentPath().c_str())&FILE_ATTRIBUTE_DIRECTORY;
}

//进入当前文件的指定下级文件
void FileTools::intoNextFile(string file)
{
	//currentDir.append("\\").append(currentFile);
    //currentFile = file;
}

int FileTools::getFileCount()
{
	return fileCount;
}

string FileTools::getcurrentPath()
{

    string path = "";
	for (int i = 0; i < pathDepth; i++)
	{
		if(i == pathDepth - 1)
		{
			path.append(currentPath[i]);
		}else
		{
			path.append(currentPath[i]).append("\\");
		}
	}
    return path;
}

//后退
void FileTools::goBack()
{
	currentPath[pathDepth] = "";
	pathDepth--;
}

void FileTools::addPathDepth(string file)
{
	currentPath[pathDepth] = file;
	pathDepth++;
}

