#include <string>
using namespace std;


class StackTest
{
public:

	static StackTest* getInstance();

private:
	
	StackTest();
	~StackTest();
	static void init();
};








