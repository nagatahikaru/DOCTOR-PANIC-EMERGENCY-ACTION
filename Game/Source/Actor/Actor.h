/**
* Actor.h
* 見た目が存在するオブジェクトの基底クラス
*/
#pragma once

class Transform 
{
public:
	Transform() {};
	~Transform() {};


public:
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;

};


/**
* アクタークラス
*/
class Actor : public IGameObject
{
protected:
	/** モデル描画 */
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_speed;
	Transform m_transform;


public:
	virtual bool Start() override {};
	virtual void Update() override {};
	virtual void Render(RenderContext& rc) override {};
};







