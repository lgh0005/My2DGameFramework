#include "pch.h"
#include "PlayerController.h"
#include "BulletSpawner.h"

PlayerController::PlayerController(const string& name) : Super(name)
{
	_playerShader = RESOURCE.GetResource<Shader>("PlayerShader");
	_playerUniformSet = RESOURCE.GetResource<UniformSet>("PlayerUniforms");
}

void PlayerController::Init()
{
	auto self = GetSelf<PlayerController>();
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr<Scene>(_currentScene, scene) == false) return;

	// Get transform
	_ownerTransform = owner->GetTransform();

	// Get FlipbookPlayer
	_playerFlipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("PlayerFlipbook"));

	// Get Flipbooks
	{
		// Normal Flipbooks
		{
			auto src_combo_1 = RESOURCE.GetResource<Flipbook>("_normal_combo_1_r");
			auto src_combo_2 = RESOURCE.GetResource<Flipbook>("_normal_combo_2_r");
			auto src_combo_3 = RESOURCE.GetResource<Flipbook>("_normal_combo_3_r");
			auto src_damaged = RESOURCE.GetResource<Flipbook>("_normal_damaged_r");
			auto src_died = RESOURCE.GetResource<Flipbook>("_normal_died_r");
			auto src_idle = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
			auto src_walk = RESOURCE.GetResource<Flipbook>("_normal_walk_r");

			if (src_combo_1) _normal_combo_1_r = make_shared<Flipbook>(*src_combo_1);
			if (src_combo_2) _normal_combo_2_r = make_shared<Flipbook>(*src_combo_2);
			if (src_combo_3) _normal_combo_3_r = make_shared<Flipbook>(*src_combo_3);
			if (src_damaged) _normal_damaged_r = make_shared<Flipbook>(*src_damaged);
			if (src_died)    _normal_died_r = make_shared<Flipbook>(*src_died);
			if (src_idle)    _normal_idle_r = make_shared<Flipbook>(*src_idle);
			if (src_walk)    _normal_walk_r = make_shared<Flipbook>(*src_walk);
		}

		// Gun Flipbooks
		{
			auto src_air_attack = RESOURCE.GetResource<Flipbook>("_gun_air_attack_r");
			auto src_damaged = RESOURCE.GetResource<Flipbook>("_gun_damaged_r");
			auto src_died = RESOURCE.GetResource<Flipbook>("_gun_died_r");
			auto src_idle = RESOURCE.GetResource<Flipbook>("_gun_idle_r");
			auto src_jump = RESOURCE.GetResource<Flipbook>("_gun_jump_r");
			auto src_shot = RESOURCE.GetResource<Flipbook>("_gun_shot_r");
			auto src_walk = RESOURCE.GetResource<Flipbook>("_gun_walk_r");

			if (src_air_attack) _gun_air_attack_r = make_shared<Flipbook>(*src_air_attack);
			if (src_damaged)    _gun_damaged_r = make_shared<Flipbook>(*src_damaged);
			if (src_died)       _gun_died_r = make_shared<Flipbook>(*src_died);
			if (src_idle)       _gun_idle_r = make_shared<Flipbook>(*src_idle);
			if (src_jump)       _gun_jump_r = make_shared<Flipbook>(*src_jump);
			if (src_shot)       _gun_shot_r = make_shared<Flipbook>(*src_shot);
			if (src_walk)       _gun_walk_r = make_shared<Flipbook>(*src_walk);
		}

		// Sword Flipbooks
		{
			auto src_combo_1 = RESOURCE.GetResource<Flipbook>("_sword_combo_1_r");
			auto src_combo_2 = RESOURCE.GetResource<Flipbook>("_sword_combo_2_r");
			auto src_combo_3 = RESOURCE.GetResource<Flipbook>("_sword_combo_3_r");
			auto src_damaged = RESOURCE.GetResource<Flipbook>("_sword_damaged_r");
			auto src_died = RESOURCE.GetResource<Flipbook>("_sword_died_r");
			auto src_idle = RESOURCE.GetResource<Flipbook>("_sword_idle_r");
			auto src_jump = RESOURCE.GetResource<Flipbook>("_sword_jump_r");
			auto src_walk = RESOURCE.GetResource<Flipbook>("_sword_walk_r");

			if (src_combo_1) _sword_combo_1_r = make_shared<Flipbook>(*src_combo_1);
			if (src_combo_2) _sword_combo_2_r = make_shared<Flipbook>(*src_combo_2);
			if (src_combo_3) _sword_combo_3_r = make_shared<Flipbook>(*src_combo_3);
			if (src_damaged) _sword_damaged_r = make_shared<Flipbook>(*src_damaged);
			if (src_died)    _sword_died_r = make_shared<Flipbook>(*src_died);
			if (src_idle)    _sword_idle_r = make_shared<Flipbook>(*src_idle);
			if (src_jump)    _sword_jump_r = make_shared<Flipbook>(*src_jump);
			if (src_walk)    _sword_walk_r = make_shared<Flipbook>(*src_walk);
		}
	}

	// Get Colliders
	_playerCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("PlayerMainCollider"));
	_playerCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnColliderWithEnemy(other); });
	_normalAttackCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("PlayerAttackAreaNormal"));
	_normalAttackCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnCollideNormalAttackArea(other); });
	_normalAttackColliderOffset = _normalAttackCollider->GetOffset();
	_swordAttackCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("PlayerAttackAreaSword"));
	_swordAttackCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnCollideSwordAttackArea(other); });
	_swordAttackColliderOffset = _swordAttackCollider->GetOffset();

	// Get BulletSpanwer
	_bulletSpawnerObject = scene->GetGameObject("BulletSpawner");
	_bulletSpawner = static_pointer_cast<BulletSpawner>(_bulletSpawnerObject->GetBehaviour("BulletSpawner"));

	// Get RigidBody;
	_playerRigidBody = static_pointer_cast<RigidBody>(owner->GetComponent("PlayerJumper"));

	// Ensure initial state
	_playerWeaponState = EPlayerWeaponState::Normal;
	_playerState = EPlayerState::Idle;
	_lastDir = EDirection::Right;

	// Get GameObject
	_NoWeaponText = scene->GetGameObject("NoWeapon");
	_PistolText = scene->GetGameObject("PistolText");
	_SwordText = scene->GetGameObject("SwordText");

	// Set first state : Idle
	_currentState = make_shared<PlayerIdleState>();
}

void PlayerController::Update()
{
	// Gun timing duration
	if (_gunTimer > 0.0f) _gunTimer -= TIME.deltaTime;

	// Change weapon
	HandleWeaponChange();

	// Play player state
	auto self = static_pointer_cast<PlayerController>(shared_from_this());
	_currentState->Update(self);
}

void PlayerController::ChangeState(const shared_ptr<StateMachine<PlayerController>>& newState)
{
	auto self = static_pointer_cast<PlayerController>(shared_from_this());
	if (_currentState) _currentState->Exit(self);
	_currentState = newState;
	_currentState->Enter(self);
}

void PlayerController::ApplyFlipDirection()
{
	if (_playerUniformSet)
	{
		_playerUniformSet->Set("flip", _lastDir == EDirection::Left);
		_playerUniformSet->Apply(_playerShader);
	}
}

void PlayerController::HandleWeaponChange()
{
	// 무기를 바꿀 수 있는 상태 제한 : Idle 과 walk일 때만 무기 교체 가능
	if (_playerState != EPlayerState::Idle && _playerState != EPlayerState::Walk)
		return;

	if (INPUT.GetKeyDown(Inputs::Key::E))
	{
		int next = (static_cast<uint32>(_playerWeaponState) + 1) % static_cast<uint32>(EPlayerWeaponState::END);
		_playerWeaponState = static_cast<EPlayerWeaponState>(next);

		// UI 갱신
		if (_NoWeaponText) _NoWeaponText->SetActive(_playerWeaponState == EPlayerWeaponState::Normal);
		if (_PistolText)   _PistolText->SetActive(_playerWeaponState == EPlayerWeaponState::Gun);
		if (_SwordText)    _SwordText->SetActive(_playerWeaponState == EPlayerWeaponState::Sword);
	}
}

void PlayerController::SetAttackCollider()
{
	const float dir = (_lastDir == EDirection::Left) ? -1.0f : 1.0f;

	// Bullet spawner
	if (_bulletSpawnerObject)
	{
		bool isGunner = (_playerWeaponState == EPlayerWeaponState::Gun);
		_bulletSpawnerObject->SetActive(isGunner);

		if (isGunner)
		{
			auto spawnerTransform = _bulletSpawnerObject->GetTransform();
			glm::vec3 localPos = spawnerTransform->GetPosition();
			localPos.x = abs(localPos.x) * dir;
			spawnerTransform->SetPosition(localPos);
		}
	}

	// Normal attack area
	if (_normalAttackCollider)
	{
		glm::vec2 newOffset = _normalAttackColliderOffset;
		newOffset.x *= dir;
		_normalAttackCollider->SetOffset(newOffset);
	}

	// Sword attack area
	if (_swordAttackCollider)
	{
		glm::vec2 newOffset = _swordAttackColliderOffset;
		newOffset.x *= dir;
		_swordAttackCollider->SetOffset(newOffset);
	}
}

#pragma region COLLIDER_METHODS
void PlayerController::OnColliderWithEnemy(const shared_ptr<BoxCollider>& other)
{
	cout << "[Player Body] 적 공격 영역과 부딪힘!" << endl;
}

void PlayerController::OnCollideNormalAttackArea(const shared_ptr<BoxCollider>& other)
{
	// 1. 공격 상태인지 먼저 확인합니다.
	if (!_isAttacking || _playerWeaponState != EPlayerWeaponState::Normal)
	{
		return;
	}

	// 2. 충돌한 상대방의 GameObject를 안전하게 가져옵니다.
	shared_ptr<GameObject> otherOwner;
	if (Utils::IsValidPtr(other->GetOwner(), otherOwner) == false)
	{
		return;
	}

	// 3. 상대방이 "EnemyController" 스크립트를 가지고 있는지 확인합니다.
	auto enemyController = otherOwner->GetBehaviour("EnemyController");
	if (enemyController != nullptr)
	{
		// 4. 적일 경우에만 공격 성공 로직을 실행합니다.
		cout << "[Normal Attack] 공격 성공! 상대: " << otherOwner->GetName() << endl;

		// TODO: 여기에 적의 체력을 깎는 코드를 추가합니다.
		// 예: static_pointer_cast<EnemyController>(enemyController)->TakeDamage(10);
	}
}

void PlayerController::OnCollideSwordAttackArea(const shared_ptr<BoxCollider>& other)
{
	if (!_isAttacking || _playerWeaponState != EPlayerWeaponState::Sword)
	{
		return;
	}

	shared_ptr<GameObject> otherOwner;
	if (Utils::IsValidPtr(other->GetOwner(), otherOwner) == false)
	{
		return;
	}

	auto enemyController = otherOwner->GetBehaviour("EnemyController");
	if (enemyController != nullptr)
	{
		cout << "[Sword Attack] 공격 성공! 상대: " << otherOwner->GetName() << endl;

		// TODO: 여기에 적의 체력을 깎는 코드를 추가합니다.
		// 예: static_pointer_cast<EnemyController>(enemyController)->TakeDamage(25);
	}
}
#pragma endregion