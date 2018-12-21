/****************************************************************************
在进入一个文件夹时,把当前文件夹作为父节点,进入后的所有文件作为子结点
在进入一个文件时,创建一个新的树并与之前的树设置关联
****************************************************************************/
#include "Trees.h"
#include<iostream>
#include <string>

using namespace std;

static Trees *trees = nullptr;
static struct PTree *pt[MAX_TREE_SIZE];

int treesNum = 0;
int currentTree = 0;	//当前树
int currentNode = 0;	//当前结点

struct PTNode;
struct PTree;

Trees::Trees(){
	currentNode = -1;
	currentTree = -1;
}
Trees::~Trees(){}

//添加
void Trees::AddNode(string data,int treeId,int parentId)
{
	int nodeId = pt[treeId]->nodesNum;
	pt[treeId]->nodes[nodeId].data = data;
	pt[treeId]->nodes[nodeId].nodeId = nodeId;
	pt[treeId]->nodes[nodeId].parentId = parentId;
	pt[treeId]->nodes[nodeId].subNodeCount = 0;
    //父节点的子节点数+1
	pt[treeId]->nodes[parentId].subNodeCount++;
    //所在树的结点总数+1
	pt[treeId]->nodesNum++;
}


void Trees::ADDTree(int parentNodeId,int parentTreeId,string fileDir,bool isSwitchThisTree)
{	
	pt[treesNum] = new PTree;
	pt[treesNum]->treesId = treesNum;
	pt[treesNum]->parentNodeId = parentNodeId;
	pt[treesNum]->parentTreeId = parentTreeId;
	pt[treesNum]->nodesNum = 0;
	pt[treesNum]->fileDir = fileDir;
	//为树创建一个跟结点
	AddNode("",treesNum,-1);

    if(isSwitchThisTree)
	{
	    currentNode = 0;
	    currentTree = treesNum;
	}

	treesNum ++;
}



//判断某结点是否有子结点
bool Trees::isSubNodes(int nodeId,int treeId){

	for (int i = 0; i < pt[treeId]->nodesNum; i++)
	{
        if(pt[treeId]->nodes[i].parentId == nodeId)
		{
            return true;
		}
	}
    return false;
}

PTree* Trees::getTreeById(int treeId)
{
	return pt[treeId];
}

//根据父节点返回想要的结点组, param : refreshPos 是否刷新当前位置
void Trees::getNodesById(PTNode nodes[MAX_TREE_SIZE],int parentId,int treeId,bool refreshPos)
{
    if(refreshPos) 
	{
	    currentNode = parentId;
	    currentTree = treeId;
	}
    int tempCount = 0;
	for (int i = 0; i < pt[treeId]->nodesNum; i++)
	{
		if(pt[treeId]->nodes[i].parentId == parentId)
		{
            nodes[tempCount] = pt[treeId]->nodes[i];
            tempCount ++;
		}
	}

}

//获取子节点数量
int Trees::getSubNodesCountByNodeId(int nodeId,int treeId)
{
	return pt[treeId]->nodes[nodeId].subNodeCount;
}

//获取当前结点的子节点数量
int Trees::getCurrentNodeSubNodeCount()
{
	return pt[currentTree]->nodes[currentNode].subNodeCount;
}

int Trees::getCurrentTreeId()
{
	return currentTree;
}

int Trees::getCurrentNodeId()
{
	return currentNode;
}

void Trees::setCurrentTreeId(int treeId)
{
	currentTree = treeId;
}

void Trees::setCurrentNodeId(int nodeId)
{
	currentNode = nodeId;
}

PTree* Trees::getCurrentTree()
{
    return pt[currentTree];
}

//获取当前结点
PTNode Trees::getCurrentNode()
{
	return pt[currentTree]->nodes[currentNode];
}

//获取空节点,在没有父节点时,填这个返回值就可以
int Trees::getNullNode()
{
	return -1;
}

//获取主节点or主树(所有文件夹都在主树上面)
int Trees::getMainNode()
{
	return 0;
}

//判断是否为空结点或树
bool Trees::isNullNode()
{
    return false;
}


//获取结点信息
PTNode Trees::getNodeById(int nodeId,int treeId)
{
   return pt[treeId]->nodes[nodeId];
}

void Trees::clearData()
{
	currentNode = -1;
	currentTree = -1;
	treesNum = 0;
	memset( pt, 0, sizeof(pt) );
}


Trees* Trees::getInstance()
{
	if (!trees)
    {
        trees = new Trees();
    }

    return trees;
}


