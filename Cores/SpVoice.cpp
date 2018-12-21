#include "SpVoice.h"
#include<iostream>
#include <string>
#include <sapi.h>    // 导入语音头文件
#include <sphelper.h>// 导入语音识别头文件
#pragma comment(lib,"sapi.lib") 

using namespace std;
USING_NS_CC;

static ISpVoice* pVoice = nullptr;
static SpVoice *sp = nullptr;


SpVoice::SpVoice()
{
}

SpVoice::~SpVoice()
{
	pVoice->Release();
	pVoice = NULL;
	CoUninitialize();
}

SpVoice* SpVoice::getInstance()
{

	if (!sp)
    {
        sp = new SpVoice();
        sp->init();
    }

    return sp;

}

void SpVoice::init()
{
	if (FAILED(CoInitialize(NULL)))
	{
        CCASSERT(false, "SpVoice init error");
	}
	// 初始化SAPI 
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	ISpObjectToken* pSpObjectToken = NULL;
	if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, _T("language=804"), NULL, &pSpObjectToken)))// 804代表中文 
	{
		pVoice->SetVoice(pSpObjectToken); // 声音大小
		pVoice->SetRate(1);// 语速
		pSpObjectToken->Release();
		if (!SUCCEEDED(hr))
		{
			CCASSERT(false, "SpVoice init error");
		}
	}
	else
	{
        CCASSERT(false, "SpVoice init error");
	}

}

void SpVoice::speakText(const wchar_t* s)
{
	LPTSTR lpStr = new TCHAR[32];
	//wchar_t Str[] = L"Hello World!";
	//auto strText = _T("截断");
	pVoice->Speak(s, 0, NULL);
}



