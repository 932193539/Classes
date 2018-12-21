#include <string>

#define MAX_TREE_SIZE 999
#define MAX_Node_SIZE 999
using namespace std;


typedef struct PTNode {    //结点结构
	string data;
	int parentId;
	int nodeId;
    int subNodeCount;
};

typedef struct PTree{		//树结构
	PTNode nodes[MAX_TREE_SIZE];
	string fileDir;
	int parentNodeId,parentTreeId,treesId,nodesNum;	//父结点ID,父节点所在树ID,编号和结点数
};


class Trees
{
public:
	void AddNode(string data,int treeId,int parentId);
	void ADDTree(int parentId,int parentNode,string fileDir,bool isSwitchThisTree);
	static Trees* getInstance();
	static PTree* getTreeById(int treeId);
	int getCurrentTreeId();
	int getCurrentNodeId();
	bool isSubNodes(int nodeId,int treesId);
	int currentNode;
	int currentTree;
    static int getNullNode();
    bool isNullNode();
    int getSubNodesCountByNodeId(int nodeId,int treeId);
    PTree* getCurrentTree();
    PTNode getCurrentNode();
    int getCurrentNodeSubNodeCount();
    void getNodesById(PTNode nodes[MAX_TREE_SIZE],int parentId,int treeId,bool refreshPos);
    void setCurrentNodeId(int nodeId);
    void setCurrentTreeId(int treeId);
	int getMainNode();
	void clearData();
	PTNode getNodeById(int nodeId,int treeId);


private:
	
	Trees();
	~Trees();
	static void init(string path);
	static void dir(string path);
};








