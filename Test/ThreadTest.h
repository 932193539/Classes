#include <string>
using namespace std;

class ThreadTest
{
public:

	static ThreadTest* getInstance();

private:
	ThreadTest();
	~ThreadTest();
	static void init();
};








