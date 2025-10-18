#include "pch.h"
#include "PlayerController.h"
#include "PlayerJumpState.h"

void PlayerJumpState::Enter(const shared_ptr<PlayerController>& controller)
{
	auto& rigid = controller->_playerRigidBody;
    shared_ptr<Flipbook> jumpFlipbook = nullptr;

    switch (controller->_playerWeaponState)
    {
        case EPlayerWeaponState::Normal: jumpFlipbook = controller->_normal_jump_r; break;
        case EPlayerWeaponState::Gun:    jumpFlipbook = controller->_gun_jump_r;    break;
        case EPlayerWeaponState::Sword:  jumpFlipbook = controller->_sword_jump_r;  break;
    }

    if (jumpFlipbook)
    {
        controller->_playerFlipbookPlayer->SetFlipbook(jumpFlipbook);
        jumpFlipbook->Play();
    }

    if (rigid->IsGrounded())
    {
        rigid->Jump(1000.0f);
        _hasJumped = true;
    }

    controller->ApplyFlipDirection();
}

void PlayerJumpState::Update(const shared_ptr<PlayerController>& controller)
{
    auto& rigid = controller->_playerRigidBody;
    if (rigid->IsGrounded())
    {
        auto self = static_pointer_cast<PlayerController>(controller);
        if (INPUT.GetKey(Inputs::Key::A) || INPUT.GetKey(Inputs::Key::D))
            controller->ChangeState(make_shared<PlayerWalkState>());
        else
            controller->ChangeState(make_shared<PlayerIdleState>());
        return;
    }

    // 공중에서 좌우 이동 처리
    glm::vec3 pos = controller->_ownerTransform->GetPosition();
    if (INPUT.GetKey(Inputs::Key::D))
    {
        pos.x += controller->_moveSpeed * TIME.deltaTime;
        controller->_lastDir = EDirection::Right;
    }
    else if (INPUT.GetKey(Inputs::Key::A))
    {
        pos.x -= controller->_moveSpeed * TIME.deltaTime;
        controller->_lastDir = EDirection::Left;
    }

    pos.x = clamp(pos.x, controller->_minMoveDistance, controller->_maxMoveDistance);
    controller->_ownerTransform->SetPosition(pos);

    controller->SetAttackCollider();

    controller->ApplyFlipDirection();
}

void PlayerJumpState::Exit(const shared_ptr<PlayerController>& controller)
{
    _hasJumped = false;
}
