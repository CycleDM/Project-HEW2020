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
#include "collision.h"
#include "animator.h"

//----------------------------------------------------------------------------
// ��{�N���X
//----------------------------------------------------------------------------
class Object
{
public:
	Object();
	~Object();

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// �I�u�W�F�N�g�̃T�C�Y���w��
	virtual void SetSize(float, float);
	virtual void SetScale(float);
	// �I�u�W�F�N�g�̒��S���W���w��
	void SetScreenPos(float, float);
	void SetGlobalPos(float, float);
	// �I�u�W�F�N�g�̒��S���W���擾
	D3DXVECTOR2 GetScreenPos(void);
	D3DXVECTOR2 GetGlobalPos(void);

	float GetWidth(void);
	float GetHeight(void);

	// �I�u�W�F�N�g�̃e�N�X�`���|�C���^�[���擾
	Sprite* GetSprite(void);

protected:
	Sprite* pSprite;
	D3DXVECTOR2 screenPos, globalPos;
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
		OBJ_NONE = -1,
		OBJ_BED,
		OBJ_FLOOR,
		OBJ_LADDER,
		OBJ_DOOR1,
		OBJ_DIGITAL_DOOR,
		OBJ_KEY,
		OBJ_CODED_LOCK,
		OBJ_TRASH_STACK,
		OBJ_TRASH_LEG,
		OBJ_CRASH_ROBOT,
		OBJ_CRASH_ROBOT2,
		OBJ_GENERATOR,
		OBJ_SCREEN,
		OBJ_LANGUAGE_CHIP,
		OBJ_INTERACTABLE,
		OBJ_UNINTERACTABLE,
		OBJ_MAX
	};

	GameObject();
	GameObject(ObjectType type);
	~GameObject();

	void Register(ObjectType type);
	void Update(void);
	// �I�u�W�F�N�g�̃T�C�Y���w��
	void SetSize(float, float);

	Collision* GetCollision(void);
	Animator* GetAnimator(void);
	ObjectType GetType(void);

private:
	ObjectType type;			// �����̃^�C�v��ۑ����鏊
	Collision* pCollision;		// �R���W����
	Animator* pAnimator;		// �A�j���[�^�[
	bool bCustomized;
};