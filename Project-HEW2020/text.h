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
#include "d3dfont.h"
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

	void CreateText(int posx, int posy, int nSize, const char* text, int nAwaiting = 0, int nDuration = 0, D3DCOLOR color = 0xffffffff);
	bool isActive();

private:
	D3DCOLOR color;
	string str;
	int posx, posy;
	int nDuration;
	int nAwaiting;
	unsigned int nFrame;
	unsigned int nIndex;
	unsigned int nSize;
	bool bActive;
};