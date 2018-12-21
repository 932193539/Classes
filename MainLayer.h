

#include "cocos2d.h"
USING_NS_CC;

class MainLayer : public Layer
{
public:

	//阅读标记,当前读到的位置
	int currentReadPos;
    Menu *menu;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void backCallback(Ref* sender);
	void ReadAllCallback(Ref* sender);
    void menuCallback(Ref* sender);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    // implement the "static node()" method manually
    CREATE_FUNC(MainLayer);

    virtual void resetMenuByCurrentFile();
    virtual void setCurrentPathData();
    Vec2 _beginPos;
};

