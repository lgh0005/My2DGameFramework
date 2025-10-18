#include "pch.h"
#include "PlayerController.h"
#include "PlayerAttackState.h"
#include "BulletSpawner.h"

void PlayerAttackState::Enter(const shared_ptr<PlayerController>& controller)
{
    _isComboRequested = false;
	controller->_isAttacking = false;
    StartAttack(controller);
}

void PlayerAttackState::Update(const shared_ptr<PlayerController>& controller)
{
    // 1. 캔슬 로직 (이동/점프)
    if (INPUT.GetKey(Inputs::Key::D) || INPUT.GetKey(Inputs::Key::A))
    {
        controller->ChangeState(make_shared<PlayerWalkState>());
        return;
    }

    // 3. 콤보 입력 버퍼링 및 다음 행동 결정 (항상 isAttacking == true인 상태)
    if (INPUT.MouseClick(Inputs::Mouse::Left))
    {
        _isComboRequested = true;
    }

    auto currentFlip = controller->_playerFlipbookPlayer->GetCurrentFlipbook();
    if (!currentFlip->IsPlaying())
    {
        if (_isComboRequested)
        {
            _isComboRequested = false;
            StartAttack(controller); // 다음 콤보 공격
        }
        else
        {
            controller->ChangeState(make_shared<PlayerIdleState>()); // Idle로 전환
            return;
        }
    }

    // 4. 공통 업데이트
    controller->SetAttackCollider();
    controller->ApplyFlipDirection();
}

void PlayerAttackState::Exit(const shared_ptr<PlayerController>& controller)
{
	controller->_isAttacking = false;
    controller->_comboStep = 0;
}

void PlayerAttackState::StartAttack(const shared_ptr<PlayerController>& controller)
{
    shared_ptr<Flipbook> attackFlipbook = nullptr;

    switch (controller->_playerWeaponState)
    {
    case EPlayerWeaponState::Normal:
        attackFlipbook = GetNormalComboAnim(controller, controller->_comboStep);
        controller->_comboStep = (controller->_comboStep + 1) % 3;
        break;
    case EPlayerWeaponState::Sword:
        attackFlipbook = GetSwordComboAnim(controller, controller->_comboStep);
        controller->_comboStep = (controller->_comboStep + 1) % 3;
        break;
    case EPlayerWeaponState::Gun:
        attackFlipbook = controller->_gun_shot_r;
        SpawnBullet(controller);
        controller->_gunTimer = controller->_gunCooldown;
        break;
    }

    if (attackFlipbook)
    {
        controller->_playerFlipbookPlayer->SetFlipbook(attackFlipbook);
        attackFlipbook->Play();
        controller->_isAttacking = true;
    }
}

shared_ptr<Flipbook> PlayerAttackState::GetNormalComboAnim(const shared_ptr<PlayerController>& controller, uint32 combo)
{
    switch (combo)
    {
    case 0: return controller->_normal_combo_1_r;
    case 1: return controller->_normal_combo_2_r;
    case 2: return controller->_normal_combo_3_r;
    }
    return nullptr;
}

shared_ptr<Flipbook> PlayerAttackState::GetSwordComboAnim(const shared_ptr<PlayerController>& controller, uint32 combo)
{
    switch (combo)
    {
    case 0: return controller->_sword_combo_1_r;
    case 1: return controller->_sword_combo_2_r;
    case 2: return controller->_sword_combo_3_r;
    }
    return nullptr;
}

void PlayerAttackState::SpawnBullet(const shared_ptr<PlayerController>& controller)
{
    if (!controller->_bulletSpawner) return;
    auto spawnPos = controller->_bulletSpawnerObject->GetTransform()->GetWorldPosition();
    controller->_bulletSpawner->SpawnBullet(spawnPos, controller->_lastDir);
}
