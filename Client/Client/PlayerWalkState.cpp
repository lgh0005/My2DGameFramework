#include "pch.h"
#include "PlayerController.h"
#include "PlayerWalkState.h"

void PlayerWalkState::Enter(const shared_ptr<PlayerController>& controller)
{
    shared_ptr<Flipbook> walkFlipbook = nullptr;
    switch (controller->_playerWeaponState)
    {
        case EPlayerWeaponState::Normal: walkFlipbook = controller->_normal_walk_r; break;
        case EPlayerWeaponState::Gun:    walkFlipbook = controller->_gun_walk_r;    break;
        case EPlayerWeaponState::Sword:  walkFlipbook = controller->_sword_walk_r;  break;
    }

    if (walkFlipbook)
    {
        controller->_playerFlipbookPlayer->SetFlipbook(walkFlipbook);
        walkFlipbook->Play();
    }

    controller->ApplyFlipDirection();
}

void PlayerWalkState::Update(const shared_ptr<PlayerController>& controller)
{
	auto pos = controller->_ownerTransform->GetPosition();
	bool moved = false;

    // �̵� �Է�
    if (INPUT.GetKey(Inputs::Key::D))
    {
        pos.x += controller->_moveSpeed * TIME.deltaTime;
        controller->_lastDir = EDirection::Right;
        moved = true;
    }
    else if (INPUT.GetKey(Inputs::Key::A))
    {
        pos.x -= controller->_moveSpeed * TIME.deltaTime;
        controller->_lastDir = EDirection::Left;
        moved = true;
    }
    pos.x = clamp(pos.x, controller->_minMoveDistance, controller->_maxMoveDistance);

    // ���� �Է�
    if (INPUT.GetKeyDown(Inputs::Key::Space))
    {
        if (controller->_playerRigidBody->IsGrounded())
        {
            controller->_playerRigidBody->Jump(1000.0f);
            controller->ChangeState(make_shared<PlayerJumpState>());
            return; // JumpState�� ��ȯ
        }
    }

    if (!moved) { controller->ChangeState(make_shared<PlayerIdleState>()); return; }

    // Flipbook ����
    shared_ptr<Flipbook> walkFlipbook = nullptr;
    switch (controller->_playerWeaponState)
    {
    case EPlayerWeaponState::Normal: walkFlipbook = controller->_normal_walk_r; break;
    case EPlayerWeaponState::Gun:    walkFlipbook = controller->_gun_walk_r;    break;
    case EPlayerWeaponState::Sword:  walkFlipbook = controller->_sword_walk_r;  break;
    }

    controller->_ownerTransform->SetPosition(pos);
    controller->SetAttackCollider();
    controller->ApplyFlipDirection();
}

void PlayerWalkState::Exit(const shared_ptr<PlayerController>& controller)
{

}
