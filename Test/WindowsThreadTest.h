#include <string>
using namespace std;

class WindowsThreadTest
{
public:

	static WindowsThreadTest* getInstance();

private:
	WindowsThreadTest();
	~WindowsThreadTest();
	static void init();
};








