#pragma once
#include "Source/Actor/ActorStateMachine.h"
#include "PlayerStateMachine.h"

class Player;


class PlayerIStateBess :public IState
{
protected:
	Player* GetPlayer()const
	{
		auto* psm = static_cast<PlayerStateMachine*>(m_owner);
		return psm->GetPlayer();
	}
};