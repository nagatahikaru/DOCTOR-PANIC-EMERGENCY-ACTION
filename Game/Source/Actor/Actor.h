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
	
	
	Transform m_transform;

public:
	inline const Transform& GetTransform()const { return m_transform; }

	inline ModelRender* GetModelRender() { return &m_modelRender; }

public:
	virtual bool Start() override { return true; };
	virtual void Update() override {};
	virtual void Render(RenderContext& rc) override {};
};







