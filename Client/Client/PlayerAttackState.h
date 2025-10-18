#pragma once
#include "StateMachine.h"

class PlayerController;

class PlayerAttackState : public StateMachine<PlayerController>
{
public:
	virtual ~PlayerAttackState() override = default;
	virtual void Enter(const shared_ptr<PlayerController>& controller) override;
	virtual void Update(const shared_ptr<PlayerController>& controller) override;
	virtual void Exit(const shared_ptr<PlayerController>& controller) override;

private:	
	void StartAttack(const shared_ptr<PlayerController>& controller);
	shared_ptr<Flipbook> GetNormalComboAnim(const shared_ptr<PlayerController>& controller, uint32 combo);
	shared_ptr<Flipbook> GetSwordComboAnim(const shared_ptr<PlayerController>& controller, uint32 combo);
	void SpawnBullet(const shared_ptr<PlayerController>& controller);

private:
	bool _isComboRequested = false;
};

