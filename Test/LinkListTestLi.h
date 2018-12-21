#include <string>
using namespace std;


class LinkListTestLi
{
public:

	static LinkListTestLi* getInstance();

private:
	
	LinkListTestLi();
	~LinkListTestLi();
	static void init();
};








