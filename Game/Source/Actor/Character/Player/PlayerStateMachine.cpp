#include "stdafx.h"
#include "Source/Actor/ActorStateMachine.h"
#include "PlayerStateMachine.h"
#include "Player.h" 

namespace {
	float LSTICK_ZERO_THRESHOLD = 0.000001f;
	float LSTICK_ZERO = 0.0f;
}


PlayerStateMachine::PlayerStateMachine()
{
	RegisterState<PlayerIdleState>();
	RegisterState<PlayerMoveState>();
	RegisterState<PlayerJumpState>();
	m_currentState = FindState(PlayerIdleState::ID());

}

PlayerStateMachine::~PlayerStateMachine()
{
	
}

void PlayerStateMachine::Update()
{
	_ASSERT(m_currentState != nullptr);
	if (m_currentState) {
		uint32_t request;
		if (m_currentState->RequestState(request)) {
			m_currentState->Exit();
			m_currentState = FindState(request);
			m_currentState->Enter();
		}
		m_currentState->Update();
	}
}

void PlayerIdleState::Enter()
{ 

}

void PlayerIdleState::Update()
{
	Player* player = GetPlayer();
	player->SetPlayAnimation(player->GetEnAnimationClip());
}

void PlayerIdleState::Exit()
{

}

//待機状態からの状態遷移判定。
//Aボタンでジャンプ、スティック入力で移動状態へ。
//戻り値：状態遷移が発生したらtrue、しなかったらfalseを返す。
bool PlayerIdleState::RequestState(uint32_t& request)
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		request = PlayerJumpState::ID();
		return true;
	}
	if (g_pad[0]->GetLStickXF() >= LSTICK_ZERO_THRESHOLD ||
		g_pad[0]->GetLStickYF() >= LSTICK_ZERO_THRESHOLD)
	{
		request = PlayerMoveState::ID();
		return true;
	}
	return false;
}

void PlayerMoveState::Enter()
{

}

void PlayerMoveState::Update()
{
	Player* player = GetPlayer();
	player->Move();
	if(g_pad[0]->IsPress(enButtonB))
	{
		player->SpeedUp();

	}
	player->MoveUpdate();
	player->SetPlayAnimation(player->GetEnAnimationClip());
}

void PlayerMoveState::Exit()
{

}

bool PlayerMoveState::RequestState(uint32_t&request)
{
	Player* player = GetPlayer();
	if(!g_pad[0]->IsPressAnyKey() &&
		player->GetIsOnGround())
	{
		request = PlayerIdleState::ID();
		return true;
	}
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		request = PlayerJumpState::ID();
		return true;
	}
	return false;

}

void PlayerJumpState::Enter()
{

}

void PlayerJumpState::Update()
{
	Player* player = GetPlayer();
	player->Jump();
	player->MoveUpdate();
	player->SetPlayAnimation(player->GetEnAnimationClip());
}

void PlayerJumpState::Exit()
{

}

bool PlayerJumpState::RequestState(uint32_t& request)
{
	// ジャンプ状態からの状態遷移判定。
	// 地面に着地したら待機状態へ、スティック入力があれば移動状態へ。
	
	Player* player = GetPlayer();

	if (!g_pad[0]->IsPressAnyKey() &&
		player->GetIsOnGround()) {
		request = PlayerIdleState::ID();
		return true;
	}
	if (g_pad[0]->GetLStickXF() >= LSTICK_ZERO_THRESHOLD || 
		g_pad[0]->GetLStickYF() >= LSTICK_ZERO_THRESHOLD)
	{
		request = PlayerMoveState::ID();
		return true;
	}
	if (g_pad[0]->IsTrigger(enButtonA) && 
		player->GetJumpCount() <= player->GetMaxJumpCount())
	{
		request = PlayerJumpState::ID();
		return true;
	}
	return false;
}