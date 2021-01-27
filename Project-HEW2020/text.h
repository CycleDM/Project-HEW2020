//----------------------------------------------------------------------------
// 
// Project-HEW2020 [text.h]
// ゲームシーンの中のテキスト制御
// 
// Date:   2021/01/27
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#pragma once
#include <string>
using namespace std;

class GameText
{
public:
	GameText();
	~GameText();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void CreateText(int posx, int posy, const char* text, int nSize = 12, int nDuration = 0);
	bool isActive();

private:
	int posx, posy;
	char ch[1024];
	string str;
	int nDuration;
	unsigned int nFrame;
	unsigned int nIndex;
	unsigned int nSize;
	bool bActive;
};