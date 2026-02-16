/**
* Scene.h
* SceneŠî’êƒNƒ‰ƒX
*/

#pragma once

class Scene :public IGameObject
{
protected:
	SpriteRender m_spriteRender;


public:
	virtual bool Start() override {};
	virtual void Update() override {};
	virtual void Render(RenderContext& rc) override {};



};

