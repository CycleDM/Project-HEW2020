//----------------------------------------------------------------------------
// 
// Project-HEW2020 [text.cpp]
// ゲームシーンの中のテキスト制御
// 
// Date:   2021/01/27
// Author: AT12D187_17_周進
// 
//----------------------------------------------------------------------------
#include <stdio.h>
#include "text.h"
#include "config.h"

GameText::GameText()
{
	Init();
}

GameText::~GameText()
{
	Uninit();
}

void GameText::Init()
{
	color = 0xffffffff;
	posx = posy = 0;
	str = "";
	nDuration = 0;
	nAwaiting = 0;
	nFrame = 0;
	nIndex = 0;
	nSize = 12;
	bActive = false;
}

void GameText::Uninit()
{
}

void GameText::Update()
{
	if (!bActive) return;
	nFrame++;
	int nInterval = nDuration / str.length();
	if (nFrame >= nInterval)
	{
		nIndex++;
		nFrame = 0;
	}
	if (nIndex >= str.length())
	{
		bActive = false;
	}
}

void GameText::Draw()
{
	if (nAwaiting >= 0 && nIndex >= str.length() && nFrame <= nAwaiting)
	{
		D3DFont::Draw(posx, posy, str.c_str(), FONT_NAME, nSize, color);
		nFrame++;
		return;
	}
	if (nAwaiting == -1 && nIndex >= str.length())
	{
		D3DFont::Draw(posx, posy, str.c_str(), FONT_NAME, nSize, color);
		return;
	}
	if (!bActive) return;
	string outStr = "";
	for (int i = 0; i < nIndex; i++)
	{
		outStr = outStr + str[i];
	}
	D3DFont::Draw(posx, posy, outStr.c_str(), FONT_NAME, nSize, color);
}

void GameText::CreateText(int posx, int posy, int nSize, const char* text, int nAwaiting, int nDuration, D3DCOLOR color)
{
	if (bActive) return;
	this->color = color;
	this->posx = posx;
	this->posy = posy;
	this->str = text;
	this->nDuration = nDuration;
	this->nAwaiting = nAwaiting;
	this->nSize = nSize;
	this->nFrame = 0;
	this->nIndex = 0;
	this->bActive = true;
}

bool GameText::isActive()
{
	return bActive;
}