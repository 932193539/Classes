#ifndef __SPVOICE_SCENE_H__
#define __SPVOICE_SCENE_H__

#include "cocos2d.h"


class SpVoice
{
public:
	static SpVoice* getInstance();
	void speakText(const wchar_t* s);
private:
	

	SpVoice();
	~SpVoice();
	static void init();

};





#endif // __SpVoice_SCENE_H__


