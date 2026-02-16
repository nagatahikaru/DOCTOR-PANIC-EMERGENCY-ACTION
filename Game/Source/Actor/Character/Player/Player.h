/**
* Player.h
* プレイヤー基底クラス
*/

enum EnAnimationClip {
	enAnimationClip_Idle,//待機
	enAnimationClip_Walk,//歩き
	enAnimationClip_Run,//走り
	enAnimationClip_Jump,//ジャンプ
	enAnimationClip_Clear,//クリア
	enAnimationClip_Death,//死亡
	enAnimationClip_Pain,//ダメージ
	enAnimationClip_Num//アニメーションクリップ数
};

namespace {
	int MAX_JUMP_COUNT = 2; // 最大ジャンプ回数


}

//Playerの変数をまとめる名前空間
namespace PlayerVariable
{
	//Playerのアイテム所持状況
	//アイテム所持状況
	//0:なし、1:スノーボール、2:スター、3:キノコ、4:本
	//0:None, 1:SnowBall, 2:Star, 3:Mushroom, 4:Book
	//呼び出しかた
	// 例:ItemStatus::SnowBall
	namespace ItemStatus
	{
		enum {
			None = 0,
			SnowBall = 1,
			Star = 2,
			Mushroom = 3,
			Book = 4
		};
	}

	//Playerの形態状態
	//0:死亡形態、1:通常形態、2:大人形態、3:魔女形態、4:形態数
	//0:Death, 1:Normal, 2:Adult, 3:Witch、4:Num
	//呼び出しかた
	// 例:PlayerVariable::FormState::SpeedUp
	namespace FormState {
		enum {
			Death = 0,
			Normal = 1,
			Adult = 2,
			Witch = 3,
			Num = 4
		};
	}

	const uint8_t INITIAL_RESIDUE = 3; //初期残基数
	const float MAX_JUMP_POWER = 1000.0f; //最大ジャンプ力
	const float RESET_TIME = 0.0f; //リセット時間
	const uint8_t RESET_JUMP_COUNT = 0; //リセットジャンプ回数
	const float  NONE_SPEED = 0.0f; //スピードアップなし
	const uint8_t VECTOR_SIZE = 10; //ベクトルサイズ

	namespace Transform
	{
		const Vector3 INITIAL_COORDINATE = Vector3(500.0f, 1500.0f, 0.0f);//初期座標
		const float GRAVITY = 50.0f; //重力
		const uint8_t ACCELERATION_TIME = 5;//加速時間
		const float BASICS_SPEED = 400.0f; //基本速度
		const Vector3 VECTOR_UP = Vector3(0.0f, 1.0f, 0.0f); //上方向ベクトル
		const Vector3 INITIAL_SCALE = Vector3(1.5f, 1.5f, 1.5f); //初期スケール
		const Vector3 COLLISION_SCALE = Vector3(50.0f, 35.0f, 50.0f); //当たり判定スケール

	}
}

#pragma once
#include "Source/Actor/Character/Character.h"

class GameCamera;
class PlayerStateMachine;


class Player : public Character
{
public:
	Player();
	 ~Player();

	//初期化
	bool Start();
	//更新
	void Update();
	//投的攻撃判定
	void ProjectionAtk();
	//ダメージ判定
	void Damage();
	//動き
	void Move();
	//ジャンプ
	void Jump();
	//加速
	void SpeedUp();
	//動き更新
	void MoveUpdate();



	//アニメーション
	void SetPlayAnimation(EnAnimationClip animation);

	//描画
	void Render(RenderContext& rc);

	void SetPlayerInformation()
	{
		m_stateMachine->SetPlayer(this);
	}

	const Vector3& GetPlayerDir()const
	{
		return m_facingDir;
	}

	const CollisionObject& GetPlayerCollisionObject() const
	{
		return *m_playerCollisionObj;
	}

	const bool GetIsOnGround() const
	{
		return m_characterController.IsOnGround();
	}

	const int GetJumpCount() const
	 {
		 return m_jumpCount;
	 }

	void SetJumpCount(int count)
	 {
		 m_jumpCount = count;
	 }
	
	const int GetMaxJumpCount() const
	 {
		 return MAX_JUMP_COUNT;
	 }

	const EnAnimationClip GetEnAnimationClip() const
	{
		if (!g_pad[0]->IsPressAnyKey())
		{
			return enAnimationClip_Idle;
		}
		return m_setAnimation;
	}
private:
	void SetEnAnimationClip(EnAnimationClip animation)
	{
		m_setAnimation = animation;
	}



private:
	std::unique_ptr<PlayerStateMachine> m_stateMachine;

	CharacterController m_characterController;
	CollisionObject* m_playerCollisionObj;
	Vector3 m_facingDir = Vector3(0.0f, 0.0f, 1.0f); // 初期向き
	FontRender m_posRender;//座標表示用
	Vector3 m_playerCollisionScale;	//プレイヤーの当たり判定スケール
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ
	int m_jumpCount = 0;//ジャンプ回数
	int m_score = 0; //スコア
	int m_itemStatus = 0;//アイテム所持状況
	float m_time = 0.0f; //時間経過用
	bool m_sperd = true;
	EnAnimationClip m_setAnimation = enAnimationClip_Idle; //アニメーションクリップ
};