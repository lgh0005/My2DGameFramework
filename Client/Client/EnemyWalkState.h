#pragma once
#include "StateMachine.h"

class EnemyController;

class EnemyWalkState : public StateMachine<EnemyController>
{
	using Super = StateMachine;

public:
	virtual ~EnemyWalkState() override = default;
	virtual void Enter(const shared_ptr<EnemyController>& controller) override;
	virtual void Update(const shared_ptr<EnemyController>& controller) override;
	virtual void Exit(const shared_ptr<EnemyController>& controller) override;
};

