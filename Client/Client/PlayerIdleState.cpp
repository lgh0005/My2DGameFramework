#include "pch.h"
#include "PlayerIdleState.h"
#include "PlayerController.h"

void PlayerIdleState::Enter(const shared_ptr<PlayerController>& controller)
{
    shared_ptr<Flipbook> idleFlipbook = nullptr;
    switch (controller->_playerWeaponState)
    {
    case EPlayerWeaponState::Normal: idleFlipbook = controller->_normal_idle_r; break;
    case EPlayerWeaponState::Gun:    idleFlipbook = controller->_gun_idle_r; break;
    case EPlayerWeaponState::Sword:  idleFlipbook = controller->_sword_idle_r; break;
    }

    if (idleFlipbook)
    {
        controller->_playerFlipbookPlayer->SetFlipbook(idleFlipbook);
        idleFlipbook->Play();
    }

    controller->ApplyFlipDirection();
}

void PlayerIdleState::Update(const shared_ptr<PlayerController>& controller)
{
    auto pos = controller->_ownerTransform->GetPosition();
    bool isMoving = false;

    // 이동 입력
    if (INPUT.GetKey(Inputs::Key::D))
    {
        pos.x += controller->_moveSpeed * TIME.deltaTime;
        controller->_lastDir = EDirection::Right;
        isMoving = true;
        controller->ChangeState(make_shared<PlayerWalkState>());
        return; // WalkState로 전환
    }
    if (INPUT.GetKey(Inputs::Key::A))
    {
        pos.x -= controller->_moveSpeed * TIME.deltaTime;
        controller->_lastDir = EDirection::Left;
        isMoving = true;
        controller->ChangeState(make_shared<PlayerWalkState>());
        return; // WalkState로 전환
    }

    // 점프 입력
    if (INPUT.GetKeyDown(Inputs::Key::Space))
    {
        if (controller->_playerRigidBody->IsGrounded())
        {
            controller->_playerRigidBody->Jump(1000.0f);
            controller->ChangeState(make_shared<PlayerJumpState>());
            return; // JumpState로 전환
        }
    }

    // 공격 입력 (좌클릭)
    if (INPUT.MouseClick(Inputs::Mouse::Left))
    {
        bool canAttack = false;
        EPlayerWeaponState weaponState = controller->_playerWeaponState;

        switch (weaponState)
        {
            case EPlayerWeaponState::Normal:
            case EPlayerWeaponState::Sword:
                canAttack = true; break;
            case EPlayerWeaponState::Gun:
                if (controller->_gunTimer <= 0.0f) canAttack = true; break;
        default:
            break;
        }

        if (canAttack)
        {
            controller->ChangeState(make_shared<PlayerAttackState>());
            return;
        }
    }

    // Flipbook 갱신
    shared_ptr<Flipbook> idleFlipbook = nullptr;
    switch (controller->_playerWeaponState)
    {
    case EPlayerWeaponState::Normal: idleFlipbook = controller->_normal_idle_r; break;
    case EPlayerWeaponState::Gun:    idleFlipbook = controller->_gun_idle_r; break;
    case EPlayerWeaponState::Sword:  idleFlipbook = controller->_sword_idle_r; break;
    }

    if (idleFlipbook && controller->_playerFlipbookPlayer->GetCurrentFlipbook() != idleFlipbook)
    {
        controller->_playerFlipbookPlayer->SetFlipbook(idleFlipbook);
        idleFlipbook->Play();
    }

    // 이동 없으면 Idle 상태 유지
    controller->_ownerTransform->SetPosition(glm::vec3(clamp(pos.x, controller->_minMoveDistance, controller->_maxMoveDistance), pos.y, pos.z));
    controller->ApplyFlipDirection();

    // 공격 콜라이더 위치 업데이트
    controller->SetAttackCollider();
}

void PlayerIdleState::Exit(const shared_ptr<PlayerController>& controller)
{

}
