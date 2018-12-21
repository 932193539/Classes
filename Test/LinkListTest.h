#include <string>
using namespace std;


class LinkListTest
{
public:

	static LinkListTest* getInstance();

private:
	
	LinkListTest();
	~LinkListTest();
	static void init();
};








