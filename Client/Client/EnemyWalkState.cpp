#include "pch.h"
#include "EnemyWalkState.h"
#include "EnemyController.h"

void EnemyWalkState::Enter(const shared_ptr<EnemyController>& controller)
{
	// 1. FlipbookPlayer ��������
	auto animator = controller->_enemyFlipbookPlayer;
	if (animator == nullptr) return;

	// 2. �ȱ� �ִϸ��̼� ����
	auto walkFlipbook = controller->_normal_walk_r;
	if (walkFlipbook)
	{
		animator->SetFlipbook(walkFlipbook);
		walkFlipbook->Play();
	}

	// 3. ���� ���� �ݿ� (�¿� Flip)
	controller->ApplyFlipDirection();
}

void EnemyWalkState::Update(const shared_ptr<EnemyController>& controller)
{
	shared_ptr<Transform> transform = controller->_ownerTransform;
	if (transform == nullptr) return;

	glm::vec3 pos = transform->GetPosition();
	float moveAmount = controller->_moveSpeed * TIME.deltaTime;

	if (controller->_lastDir == EDirection::Right)
		pos.x += moveAmount;
	else
		pos.x -= moveAmount;

	if (pos.x >= controller->_maxMoveDistance)
	{
		controller->_lastDir = EDirection::Left;
		controller->ApplyFlipDirection();
	}
	else if (pos.x <= controller->_minMoveDistance)
	{
		controller->_lastDir = EDirection::Right;
		controller->ApplyFlipDirection();
	}

	transform->SetPosition(pos);
	controller->SetAttackCollider();
	controller->ApplyFlipDirection();
}

void EnemyWalkState::Exit(const shared_ptr<EnemyController>& controller)
{

}
