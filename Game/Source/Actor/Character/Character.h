/**
* Character.h
* キャラクターの基底クラス
*/
#pragma once

/**
* キャラクタークラス
*/

#include "Source/Actor/Actor.h"

class Character : public Actor
{
protected:


public:
	Vector3 m_moveSpeed; //移動速度


public:
	virtual bool Start() override { return true; };
	virtual void Update() override {};
	virtual void Render(RenderContext& rc) override {};

};



