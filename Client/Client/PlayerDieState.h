#pragma once
#include "StateMachine.h"

class PlayerController;

class PlayerDieState : public StateMachine<PlayerController>
{
public:
	virtual ~PlayerDieState() override = default;
	virtual void Enter(const shared_ptr<PlayerController>& controller) override;
	virtual void Update(const shared_ptr<PlayerController>& controller) override;
	virtual void Exit(const shared_ptr<PlayerController>& controller) override;
};

