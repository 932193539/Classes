#include <string>
using namespace std;

class AutoPtr
{
public:

	static AutoPtr* getInstance();

private:
	AutoPtr();
	~AutoPtr();
	static void init();
};








