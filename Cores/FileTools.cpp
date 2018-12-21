/****************************************************************************
�ڽ���һ���ļ���ʱ,�ѵ�ǰ�ļ�����Ϊ���ڵ�,�����������ļ���Ϊ�ӽ��
�ڽ���һ���ļ�ʱ,����һ���µ�������֮ǰ�������ù���
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

//��ȡ��ǰ�ļ�����
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
        fgets(szTest, sizeof(szTest) - 1, fp); // ������\n  
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

//��ȡ��ǰĿ¼����Ŀ¼
string* FileTools::getCurrentDirSubDir()
{
	//��սṹ������
	//memset(&fileList, 0, sizeof(fileList));
	fileCount = 0;
    string path = getcurrentPath();
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;
	// \\* ����Ҫ�������е�����
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) 
	{

	}
	do{
		if (fileInfo.name[0] != (char)'.')
		{
			//�ж��ļ����������ļ��л����ļ�
			CCLOG(fileInfo.name);
			fileList[fileCount] = fileInfo.name;
			fileCount ++;
		}

	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return fileList;
}

//�жϵ�ǰλ�����ļ�����·��
bool FileTools::isDir()
{
	return GetFileAttributesA(getcurrentPath().c_str())&FILE_ATTRIBUTE_DIRECTORY;
}

//���뵱ǰ�ļ���ָ���¼��ļ�
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

//����
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

