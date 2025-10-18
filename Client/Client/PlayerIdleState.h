#pragma once
#include "StateMachine.h"

class PlayerController;

class PlayerIdleState : public StateMachine<PlayerController>
{
public:
	virtual ~PlayerIdleState() override = default;
	virtual void Enter(const shared_ptr<PlayerController>& controller) override;
	virtual void Update(const shared_ptr<PlayerController>& controller) override;
	virtual void Exit(const shared_ptr<PlayerController>& controller) override;
};

