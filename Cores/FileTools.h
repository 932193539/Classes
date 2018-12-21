#ifndef __BOOKS_H__
#define __BOOKS_H__

#include <string>

using namespace std;
#define MAX_FILE_SIZE 999

class FileTools
{
public:
    
	int pathDepth;
	string currentPath[MAX_FILE_SIZE];
	int FileTools::getFileCount();
	static FileTools* getInstance();
	string* getCurrentDirSubDir();
	string* getCurrentFileSubContent();
	string getcurrentDir();
	string getcurrentFile();
	string getcurrentPath();
    void intoNextFile(string file);
    void FileTools::setcurrentDir(string dir);
    void FileTools::setcurrentFile(string path);
	void FileTools::goBack();
	void FileTools::addPathDepth(string file);
	bool FileTools::isDir();

private:
	
	string fileList[MAX_FILE_SIZE];
	int fileCount;
	FileTools();
	~FileTools();
	static void init();
};

#endif // __SpVoice_SCENE_H__
