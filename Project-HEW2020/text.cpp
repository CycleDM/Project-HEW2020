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
#include "d3dfont.h"
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
	posx = posy = 0;
	memset(ch, 0, sizeof(ch));
	str = "";
	nDuration = 0;
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
	int nInterval = nDuration / strlen(ch);
	if (nFrame >= nInterval)
	{
		nIndex++;
		nFrame = 0;
	}
	if (nIndex >= strlen(ch))
	{
		nIndex = 0;
		bActive = false;
	}
}

void GameText::Draw()
{
	if (!bActive) return;
	char buf[8];
	char output[1024];
	for (int i = 0; i < nIndex; i++)
	{
		sprintf_s(buf, "%c", ch[i]);
		strcat_s(output, buf);
	}
	D3DFont::Draw(posx, posy, output, FONT_NAME, nSize);
}

void GameText::CreateText(int posx, int posy, const char* text, int nSize, int nDuration)
{
	if (bActive) return;
	this->posx = posx;
	this->posy = posy;
	//sprintf_s(str, text);
	strcpy_s(ch, text);
	this->str = text;
	this->nDuration = nDuration;
	this->nSize = nSize;
	this->bActive = true;
}

bool GameText::isActive()
{
	return bActive;
}