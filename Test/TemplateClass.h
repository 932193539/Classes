#include <string>
using namespace std;

class TemplateClass
{
public:

	static TemplateClass* getInstance();

private:
	TemplateClass();
	~TemplateClass();
	static void init();
};








