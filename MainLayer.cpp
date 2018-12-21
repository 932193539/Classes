#include "MainLayer.h"
#include "AppMacros.h"
#include "Cores/SpVoice.h"
#include "Cores/FileTools.h"
#include <string>
#include "Cores/Trees.h"
#include "cocos2d.h"
#include "Test/LinkListTestLi.h"
#include <iostream>

using namespace std;
USING_NS_CC;

//每次阅读十行
const int READ_COUNT = 10;
/*	
	wchar_t* p = L"这个是宽字节转窄字节";
	char* buf = cctryWideCharToAnsi(p);
*/
char *cctryWideCharToAnsi(wchar_t *pWideChar)
{
	if (!pWideChar) return NULL;
	char *pszBuf = NULL;
	int needBytes = WideCharToMultiByte(CP_ACP, 0, pWideChar, -1, NULL, 0, NULL, NULL);
	if (needBytes > 0){
		pszBuf = new char[needBytes+1];
		ZeroMemory(pszBuf, (needBytes+1)*sizeof(char));
		WideCharToMultiByte(CP_ACP, 0, pWideChar, -1, pszBuf, needBytes, NULL, NULL);
	}

	return pszBuf;
}

/*
	char* p = "窄字节转宽字节";
	wchar_t* result;
	result = cctryAnsiCharToWide(p);
*/
wchar_t *cctryAnsiCharToWide(char *pChar)
{
	if (!pChar) return NULL;
	wchar_t *pszBuf = NULL;
	int needWChar = MultiByteToWideChar(CP_ACP, 0, pChar, -1, NULL, 0);
	if (needWChar > 0){
		pszBuf = new wchar_t[needWChar+1];
		ZeroMemory(pszBuf, (needWChar+1)*sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, pChar, -1, pszBuf, needWChar);
	}

	return pszBuf;
}

//通过vs在电脑上显示中文,需要转为utf-8格式的才可以。
char *FontToUTF8(const char* font){
    int len = MultiByteToWideChar(CP_ACP,0,font,-1,NULL,0);
    wchar_t *wstr = new wchar_t[len+1];
    memset(wstr,0,len+1);
    MultiByteToWideChar(CP_ACP,0,font,-1,wstr,len);
    len = WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
    char *str = new char[len+1];
    memset(str,0,len+1);
    WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
    if(wstr)delete[] wstr;
    return str;
}

//中文ANSI字符截取
vector<string> getContentList(char* str ,int itemCount)
{
	vector<string> strList;
	string lines;
	auto count = 0;
	auto sum = strlen(str);
	itemCount = itemCount * 2;

	for(int i = 0;i<sum;)
	{      
		if(str[i] < 0){
			//一个中文算占一格
			lines = lines + str[i] + str[i+1];
			count += 2;
			i += 2;
		}else{
			//一个英文只算半个中文
			lines = lines + str[i];
			count ++;
			i++;
		}

		if(i == sum)
		{
			string tempStr = (char *)lines.c_str(); //分割得到的字符串转换为string类型
			strList.push_back(tempStr); //存入结果数组
		}else if(count >= itemCount) 
		{
			string tempStr = (char *)lines.c_str(); //分割得到的字符串转换为string类型
			strList.push_back(tempStr); //存入结果数组
			lines = "";
			count = 0;
		}
	}

	return strList;
}

Scene* MainLayer::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    MainLayer *layer = MainLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


//如果没有结点数据,则调到该函数设置当前结点数据
void MainLayer::setCurrentPathData()
{
	//初始化文件树
	auto ft = FileTools::getInstance();
	auto treeObj = Trees::getInstance(); 

	if(ft->isDir())
	{
		string* fileList = ft->getCurrentDirSubDir();
		for (int i = 0; i < ft->getFileCount(); i++)
		{
			//为当前结点添加子节点
			treeObj->AddNode(fileList[i],treeObj->getCurrentTreeId(),treeObj->getCurrentNodeId());
		}
	}else
	{
		string* fileList = ft->getCurrentFileSubContent();
		//如果是文件,创建新树,并在新树中添加结点
		treeObj->ADDTree(treeObj->getCurrentNodeId(),treeObj->getCurrentTreeId(),ft->getcurrentPath(),true);
		for (int i = 0; i < ft->getFileCount(); i++)
		{
			//为当前结点添加子节点
			treeObj->AddNode(fileList[i],treeObj->getCurrentTreeId(),treeObj->getCurrentNodeId());
		}
	}
}

//根据当前文件数据重置菜单
void MainLayer::resetMenuByCurrentFile()
{
	menu->removeAllChildren();
    auto winSize = Director::getInstance()->getVisibleSize();
	auto treeObj = Trees::getInstance(); 
	auto height = 0;
	PTNode nodes[MAX_TREE_SIZE];
	treeObj->getNodesById(nodes,treeObj->getCurrentNodeId(),treeObj->getCurrentTreeId(),true);
	for (int i = 0; i < treeObj->getCurrentNodeSubNodeCount(); i++)
	{
		char ** contentList = new char* [100]; 
		auto conCount = 0;
		auto strList = getContentList((char *)nodes[i].data.c_str(),38);

		if(strList.size() == 0)
		{
			strList.push_back(" ");
		}

		for (int j = 0; j<strList.size(); ++j)
		{
			if(strList[j] == "")
			{
				strList[j] = " ";
			}
			auto item = MenuItemFont::create(FontToUTF8(strList[j].c_str()), CC_CALLBACK_1(MainLayer::menuCallback, this));
			height -= item->getContentSize().height + 3;
			item->setPosition(item->getPositionX() + item->getContentSize().width /2 - winSize.width / 2 + 10,height);
			item->setTag(nodes[i].nodeId);
			menu->addChild(item);
		}
	}

	menu->setPosition(winSize.width/2,winSize.height - 30) ;
}

void MainLayer::menuCallback(Ref* sender)
{
	//清空阅读标记
	currentReadPos = 0;
	//判断点击结点是否有子结点
	senderItem:setScale(1);
    auto senderItem = static_cast<MenuItemFont*>(sender);
	auto treeObj = Trees::getInstance(); 
	auto nodeId = senderItem->getTag();

	if(treeObj->getCurrentTreeId() != treeObj->getMainNode())
	{
		//当前树不是主树,证明在文件里面在文件里面只播报无法再进入了
		auto node = treeObj->getNodeById(nodeId,treeObj->getCurrentTreeId());
		runAction(
			Sequence::create(
				DelayTime::create(0.001),
				CallFunc::create([=](){
					SpVoice::getInstance()->speakText(cctryAnsiCharToWide((char *)node.data.c_str()));
                }),
				nullptr
			)
		);
	}else
	{
		treeObj->setCurrentNodeId(nodeId);
		auto node = treeObj->getCurrentNode();
		auto ft = FileTools::getInstance();
		ft->addPathDepth(node.data);
		if (!treeObj->isSubNodes(nodeId,treeObj->getCurrentTreeId()))
		{
			//设置数据
			setCurrentPathData();
		}
	
		//这一帧menu在忙,需要下一刻调用它才不会出问题
		runAction(
			Sequence::create(
				DelayTime::create(0.001),
				CallFunc::create(CC_CALLBACK_0(MainLayer::resetMenuByCurrentFile,this)),
				nullptr
			)
		);
	}
}

//后退
void MainLayer::backCallback(Ref* sender)
{
	auto treeObj = Trees::getInstance(); 
	auto tree = treeObj->getCurrentTree();
	auto node = treeObj->getCurrentNode();
	auto ft = FileTools::getInstance();

	if(node.parentId == treeObj->getNullNode() && tree->parentTreeId != treeObj->getNullNode())
	{	
		//如果没有根结点了但是有父类树,则跳转到父类树上对应结点上
		ft->goBack();
		treeObj->setCurrentNodeId(tree->parentNodeId);
		treeObj->setCurrentTreeId(tree->parentTreeId);
		auto node = treeObj->getCurrentNode();
		treeObj->setCurrentNodeId(node.parentId);
		resetMenuByCurrentFile();
	}else if(node.parentId != treeObj->getNullNode() || tree->parentTreeId != treeObj->getNullNode())
	{	
		//除了母树的根节点外其他的才可以返回
		ft->goBack();
		treeObj->setCurrentNodeId(node.parentId);
		resetMenuByCurrentFile();
	}else
	{
		//其他情况就是在跟结点,根节点后退清空重置数据
		treeObj->clearData();
		treeObj->ADDTree(Trees::getNullNode(),Trees::getNullNode(),ft->getcurrentPath(),true);
		setCurrentPathData();
	}
}

bool MainLayer::onTouchBegan(Touch *touch, Event *event)
{
    _beginPos = touch->getLocation();
    return true;
}

void MainLayer::onTouchMoved(Touch *touch, Event *event)
{
	auto touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - _beginPos.y;
    auto curPos  = menu->getPosition();
    auto nextPos = Vec2(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        return;
    }

    menu->setPosition(nextPos);
    _beginPos = touchLocation;
}

//朗读
void MainLayer::ReadAllCallback(Ref* sender)
{
	auto treeObj = Trees::getInstance(); 
	auto allCount = treeObj->getCurrentNodeSubNodeCount();
	auto endPos = (currentReadPos + READ_COUNT) > allCount ? allCount : (currentReadPos + READ_COUNT);

	PTNode nodes[MAX_TREE_SIZE];
	treeObj->getNodesById(nodes,treeObj->getCurrentNodeId(),treeObj->getCurrentTreeId(),true);
	for (int i = currentReadPos; i < endPos; i++)
	{
		SpVoice::getInstance()->speakText(cctryAnsiCharToWide((char *)nodes[i].data.c_str()));
	}

	currentReadPos = endPos == allCount ? 0 : endPos;
}

void MainLayer::onTouchEnded(Touch *touch, Event *event)
{
}

void MainLayer::onTouchCancelled(Touch *touch, Event *event)
{
}

// on "init" you need to initialize your instance
bool MainLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	currentReadPos = 0;
    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	MenuItemFont::setFontSize(12);
	auto back = MenuItemFont::create(FontToUTF8("返回"), CC_CALLBACK_1(MainLayer::backCallback, this));
	auto readAll = MenuItemFont::create(FontToUTF8("朗读"), CC_CALLBACK_1(MainLayer::ReadAllCallback, this));
    back->setPosition(Vec2(winSize.width/2-15, origin.y + winSize.height/2-10));
    readAll->setPosition(Vec2(winSize.width/2-15 - 30, origin.y + winSize.height/2-10));
	auto itemMenu = Menu::create(back,readAll,nullptr);
    this->addChild(itemMenu);

	auto _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(MainLayer::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(MainLayer::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(MainLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, 1);
	
	//要遍历的目录
	string path = "D:\\Datas";
	//读取文件数据
	auto ft = FileTools::getInstance();
	ft->addPathDepth(path);
	//创建母树
	auto treeObj = Trees::getInstance(); 
	treeObj->ADDTree(Trees::getNullNode(),Trees::getNullNode(),ft->getcurrentPath(),true);
	//获取当前路径数据
	setCurrentPathData();

	//创建和添加菜单
	menu = Menu::create();
	addChild(menu);
	resetMenuByCurrentFile();

	//测试对象实例
	LinkListTestLi::getInstance();
    
	return true;
}



