//----------------------------------------------------------------------------
// 
// Project-HEW2020 [object.h]
// �Q�[���I�u�W�F�N�g����
// 
// Date:   2020/11/06
// Author: AT12D187_17_���i
// 
//----------------------------------------------------------------------------
#pragma once

#include "sprite.h"

//----------------------------------------------------------------------------
// ��{�N���X
//----------------------------------------------------------------------------
class Object
{
public:
	Object();
	~Object();

	void Init(void);
	void Uninit(void);
	void Draw(void);

	// �I�u�W�F�N�g�̃T�C�Y���w��
	void SetSize(float, float);
	// �I�u�W�F�N�g�̒��S���W���w��
	void SetPosition(float, float);

	D3DXVECTOR2 GetPosition(void);
	float GetWidth(void);
	float GetHeight(void);

	Sprite* GetSprite(void);

protected:
	Sprite* pSprite;
	D3DXVECTOR2 globalPos;
	float width, height;
};

//----------------------------------------------------------------------------
// �h���N���X - GameObject
//----------------------------------------------------------------------------
class GameObject : public Object
{
public:
	enum ObjectType
	{
		NONE = -1,
		BED,
		FLOOR,
		LADDER,
		DOOR,
		KEY,
		MAX
	};
	GameObject();
	GameObject(ObjectType type);
	~GameObject();

	void Register(ObjectType type);
};