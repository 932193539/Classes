#include <string>
using namespace std;


class LinkQueueTest
{
public:

	static LinkQueueTest* getInstance();

private:
	
	LinkQueueTest();
	~LinkQueueTest();
	static void init();
};








