#include "stdafx.h"
#include "Player.h"
#include "PlayerStateMachine.h"


namespace {
	std::string FILE_PATH_GIRL = ("Assets/animData/girl/");
	std::string FILE_PATH_MODELDATA = ("Assets/modelData/");
	std::string FILE_PATH_DDS = (".tka");
	std::string FILE_PATH_TKM = (".tkm");
	std::string FILE_PATH_ANIMATION[7] = {
		"idle",//待機
		"walk",//歩く
		"run",//走る
		"jump",//ジャンプ
		"victory",//勝利
		"death",//負け
		"pitch"//ダメージ
	};
	std::string FILE_PATH_UNITYCHAN = {
		"unityChan"	

	};

	inline std::string GetAnimationFilePath(const int animationState)
	{
		return FILE_PATH_GIRL + FILE_PATH_ANIMATION[animationState] + FILE_PATH_DDS;
	}

	inline std::string GetModelFilePath()
	{
		return FILE_PATH_MODELDATA + FILE_PATH_UNITYCHAN+ FILE_PATH_TKM;
	}

	/**
	 モデルの一括初期化処理
	 ModelRenderの初期化、位置、スケール設定、更新処理をまとめて行う関数
	 modelRender			 初期化するModelRenderのポインタ
	 m_animationClips	 アニメーションクリップの配列
	 enAnimationClip_Num	 アニメーションクリップの数
	 pos					 モデルの位置
	 scl					 モデルのスケール
	 filePath			 モデルデータのファイルパス
	 例:
	 InitModelRender(
	 	&m_modelRender[i],
	 	m_animationClips,
	 	enAnimationClip_Num,
	 	PlayerVariable::Transform::INITIAL_COORDINATE,
	 	(i == PlayerVariable::FormState::Normal) ? Vector3(1.0f, 1.0f, 1.0f) : PlayerVariable::Transform::INITIAL_SCALE,
	 	GetModelFilePath(i));
	 */
	void InitModelRender(
		ModelRender* modelRender
		, AnimationClip* m_animationClips
		, int enAnimationClip_Num
		, const Vector3& pos
		, const Vector3& scl
		, std::string filePath) {
		modelRender->Init(filePath.c_str(), m_animationClips, enAnimationClip_Num, enModelUpAxisY);
		modelRender->SetPosition(pos);
		modelRender->SetScale(scl);
		modelRender->Update();
	}
};


Player::Player()
{
	m_stateMachine = std::make_unique<PlayerStateMachine>();

}

Player::~Player()
{
	m_stateMachine->SetPlayer(nullptr);
}

bool Player::Start()
{
	SetPlayerInformation();
	//forループでまとめる
//アニメーションクリップの読み込み
	for (int j = enAnimationClip_Idle; j < enAnimationClip_Jump; j++)
	{
		m_animationClips[j].Load(GetAnimationFilePath(j).c_str());
		m_animationClips[j].SetLoopFlag(true);
	}

	//ジャンプ、クリア、死亡、ダメージアニメーションの読み込み
	for (int j = enAnimationClip_Jump; j < enAnimationClip_Num; j++)
	{
		m_animationClips[j].Load(GetAnimationFilePath(j).c_str());
		m_animationClips[j].SetLoopFlag(false);
	}
	
	InitModelRender(
		&m_modelRender,
		m_animationClips,
		enAnimationClip_Num,
		PlayerVariable::Transform::INITIAL_COORDINATE,
		PlayerVariable::Transform::INITIAL_SCALE,
		GetModelFilePath());
	return true;
}

void Player::Update()
{
	m_stateMachine->Update();
}

void Player::ProjectionAtk()
{

}

void Player::Move()
{
	//xzの移動速度を0.0fにする
	m_moveSpeed.x = PlayerVariable::NONE_SPEED;
	m_moveSpeed.z = PlayerVariable::NONE_SPEED;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持って来る。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//ｙ方向には移動させない
	forward.y = PlayerVariable::NONE_SPEED;
	right.y = PlayerVariable::NONE_SPEED;

	//左スティックの入力量と200.0fを乗算
	right *= stickL.x * PlayerVariable::Transform::BASICS_SPEED;
	forward *= stickL.y * PlayerVariable::Transform::BASICS_SPEED;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;
	SetEnAnimationClip(enAnimationClip_Walk);
}

void Player::SpeedUp()
{
	m_moveSpeed.x *= m_time; // Bボタンが押されている間、時間経過で加速していく
	m_moveSpeed.z *= m_time; // Bボタンが押されている間、時間経過で加速していく
	if (m_time <= PlayerVariable::Transform::ACCELERATION_TIME)
	{
		m_time += g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
		m_sperd = true;
	}
	if (m_sperd)
	{
		m_time = PlayerVariable::Transform::ACCELERATION_TIME;
	}
	SetEnAnimationClip(enAnimationClip_Run);
}

void Player::MoveUpdate()
{
	//キャラクターコントローラーを使って座標を移動させる
	m_transform.m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_playerCollisionObj->SetPosition(m_transform.m_position);
	m_playerCollisionObj->SetRotation(Quaternion::Identity);
	m_playerCollisionObj->Update();
	m_modelRender.SetPosition(m_transform.m_position);
	m_modelRender.Update();
}

void Player::Jump()
{
	m_moveSpeed.y = PlayerVariable::MAX_JUMP_POWER; // ジャンプ力を設定
	m_jumpCount++; // ジャンプ回数を増やす
	SetEnAnimationClip(enAnimationClip_Jump);
}

void Player::SetPlayAnimation(EnAnimationClip animation)
{
	//アニメーションの再生
	m_modelRender.PlayAnimation(animation);
}

void Player::Damage()
{

}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


