/**
* Actor.h
* 見た目が存在するオブジェクトの基底クラス
*/
#pragma once
#include "Source/Actor/ActorStateMachine.h"
#include "PlayerIStateBess.h"


class Player;


class PlayerStateMachine : public StatePatternBase
{
	public:
		PlayerStateMachine();
		~PlayerStateMachine();
		void Update() override;
		void SetPlayer(Player*player)
		{
			m_player = player;
		}

		Player* GetPlayer()const
		{
			return m_player;
		}

private:
	Player* m_player = nullptr;
};

class PlayerIdleState :public PlayerIStateBess
{
	appState(PlayerIdleState);

public:
	PlayerIdleState() :PlayerIStateBess() {};
	virtual ~PlayerIdleState() {};

	virtual void Enter()override;
	virtual void Update()override;
	virtual void Exit()override;

	virtual bool RequestState(uint32_t& request)override;
};

class PlayerMoveState :public PlayerIStateBess
{
	appState(PlayerMoveState);

public:
	PlayerMoveState():PlayerIStateBess() {};
	virtual ~PlayerMoveState() {};

	virtual void Enter()override;
	virtual void Update()override;
	virtual void Exit()override;

	virtual bool RequestState(uint32_t& request)override;
};

class PlayerJumpState :public PlayerIStateBess
{
	appState(PlayerJumpState);

public:
	PlayerJumpState() :PlayerIStateBess() {};
	virtual ~PlayerJumpState() {};

	virtual void Enter()override;
	virtual void Update()override;
	virtual void Exit()override;

	virtual bool RequestState(uint32_t& request)override;
};

//class PlayerAttackState :public PlayerIStateBess
//{
//	appState(PlayerAttackState);
//
//public:
//	PlayerAttackState() :PlayerIStateBess() {};
//	virtual ~PlayerAttackState() {};
//
//	virtual void Enter()override;
//	virtual void Update()override;
//	virtual void Exit()override;
//	
//	virtual bool RequestState(uint32_t& request)override;
//};
//
//class PlayerDamageState :public PlayerIStateBess
//{
//	appState(PlayerDamageState);
//
//public:
//	PlayerDamageState() :PlayerIStateBess() {};
//	virtual ~PlayerDamageState() {};
//
//	virtual void Enter()override;
//	virtual void Update()override;
//	virtual void Exit()override;
//
//	virtual bool RequestState(uint32_t& request)override;
//};
//
