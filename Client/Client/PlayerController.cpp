#include "pch.h"
#include "PlayerController.h"

#pragma region PREFAB_SCRIPT
#include "BulletSpawner.h"
#pragma endregion

PlayerController::PlayerController(const string& name) : Super(name)
{
	_playerShader = RESOURCE.GetResource<Shader>("PlayerShader");
	_playerUniformSet = RESOURCE.GetResource<UniformSet>("PlayerUniforms");

	// ==========================
	// Normal Flipbooks
	// ==========================
	_normal_climb = RESOURCE.GetResource<Flipbook>("_normal_climb"); // X
	_normal_combo_1_r = RESOURCE.GetResource<Flipbook>("_normal_combo_1_r");
	_normal_combo_2_r = RESOURCE.GetResource<Flipbook>("_normal_combo_2_r");
	_normal_combo_3_r = RESOURCE.GetResource<Flipbook>("_normal_combo_3_r");
	_normal_damaged_r = RESOURCE.GetResource<Flipbook>("_normal_damaged_r");
	_normal_dash_r = RESOURCE.GetResource<Flipbook>("_normal_dash_r");	 // X
	_normal_died_r = RESOURCE.GetResource<Flipbook>("_normal_died_r");
	_normal_fall_r = RESOURCE.GetResource<Flipbook>("_normal_fall_r");
	_normal_idle_r = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
	_normal_jump_r = RESOURCE.GetResource<Flipbook>("_normal_jump_r");
	_normal_run_r = RESOURCE.GetResource<Flipbook>("_normal_run_r");	 // X
	_normal_slide_r = RESOURCE.GetResource<Flipbook>("_normal_slide_r"); // X
	_normal_walk_r = RESOURCE.GetResource<Flipbook>("_normal_walk_r");
	_normal_wallslide_r = RESOURCE.GetResource<Flipbook>("_normal_wallslide_r"); // X

	// ==========================
	// Gun Flipbooks
	// ==========================
	_gun_climb = RESOURCE.GetResource<Flipbook>("_gun_climb"); // X
	_gun_air_attack_r = RESOURCE.GetResource<Flipbook>("_gun_air_attack_r");
	_gun_damaged_r = RESOURCE.GetResource<Flipbook>("_gun_damaged_r");
	_gun_dash_r = RESOURCE.GetResource<Flipbook>("_gun_dash_r");   // X
	_gun_died_r = RESOURCE.GetResource<Flipbook>("_gun_died_r");
	_gun_idle_r = RESOURCE.GetResource<Flipbook>("_gun_idle_r");
	_gun_jump_r = RESOURCE.GetResource<Flipbook>("_gun_jump_r");
	_gun_run_r = RESOURCE.GetResource<Flipbook>("_gun_run_r");     // X
	_gun_shot_r = RESOURCE.GetResource<Flipbook>("_gun_shot_r");
	_gun_slide_r = RESOURCE.GetResource<Flipbook>("_gun_slide_r"); // X
	_gun_walk_r = RESOURCE.GetResource<Flipbook>("_gun_walk_r");
	_gun_wallslide_r = RESOURCE.GetResource<Flipbook>("_gun_wallslide_r"); // X

	// ==========================
	// Sword Flipbooks
	// ==========================
	_sword_climb = RESOURCE.GetResource<Flipbook>("_sword_climb"); // X
	_sword_air_attack_r = RESOURCE.GetResource<Flipbook>("_sword_air_attack_r"); // X
	_sword_combo_1_r = RESOURCE.GetResource<Flipbook>("_sword_combo_1_r");
	_sword_combo_2_r = RESOURCE.GetResource<Flipbook>("_sword_combo_2_r");
	_sword_combo_3_r = RESOURCE.GetResource<Flipbook>("_sword_combo_3_r");
	_sword_damaged_r = RESOURCE.GetResource<Flipbook>("_sword_damaged_r");
	_sword_dash_r = RESOURCE.GetResource<Flipbook>("_sword_dash_r");   // X
	_sword_died_r = RESOURCE.GetResource<Flipbook>("_sword_died_r");
	_sword_idle_r = RESOURCE.GetResource<Flipbook>("_sword_idle_r");
	_sword_jump_r = RESOURCE.GetResource<Flipbook>("_sword_jump_r");
	_sword_run_r = RESOURCE.GetResource<Flipbook>("_sword_run_r");      // X
	_sword_slide_r = RESOURCE.GetResource<Flipbook>("_sword_slide_r");  // X
	_sword_walk_r = RESOURCE.GetResource<Flipbook>("_sword_walk_r");
	_sword_wallslide_r = RESOURCE.GetResource<Flipbook>("_sword_wallslide_r"); // X
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
	_lastDir = Direction::Right;

	// Get GameObject
	_NoWeaponText = scene->GetGameObject("NoWeapon");
	_PistolText = scene->GetGameObject("PistolText");
	_SwordText = scene->GetGameObject("SwordText");
}

void PlayerController::Update()
{
	if (_gunTimer > 0.0f) _gunTimer -= TIME.deltaTime;

	MovePlayer();
	JumpPlayer();
	ChangeWeapon();
	Attack();
}

#pragma region LEGACY
void PlayerController::Attack()
{
	if (_playerRigidBody->IsGrounded() == false) return;

	shared_ptr<Flipbook> attackFlipbook = nullptr;

	// 현재 콤보 단계에 따라 공격 Flipbook 선택
	if (_playerWeaponState == EPlayerWeaponState::Normal)
	{
		switch (_comboStep)
		{
		case 0: attackFlipbook = _normal_combo_1_r; break;
		case 1: attackFlipbook = _normal_combo_2_r; break;
		case 2: attackFlipbook = _normal_combo_3_r; break;
		}
		// TODO : Damage enemy with normal
	}
	else if (_playerWeaponState == EPlayerWeaponState::Sword)
	{
		switch (_comboStep)
		{
		case 0: attackFlipbook = _sword_combo_1_r; break;
		case 1: attackFlipbook = _sword_combo_2_r; break;
		case 2: attackFlipbook = _sword_combo_3_r; break;
		}
		// TODO : Damage enemy with sword
	}
	else if (_playerWeaponState == EPlayerWeaponState::Gun)
	{
		attackFlipbook = _gun_shot_r;
		// TODO : Damage enemy with bullet
		AttackGun();
	}

	if (!attackFlipbook) return;

	auto currentFlipbook = _playerFlipbookPlayer->GetCurrentFlipbook();

	// 클릭 시 다음 콤보 단계 공격 실행
	if (INPUT.MouseClick(Inputs::Mouse::Left) && !_isAttacking)
	{
		_playerFlipbookPlayer->SetFlipbook(attackFlipbook);
		attackFlipbook->Play();
		_isAttacking = true;

		// 다음 콤보 단계로
		if (_playerWeaponState != EPlayerWeaponState::Gun) // Gun은 단일 공격
			_comboStep = (_comboStep + 1) % 3;
	}

	// 공격 중이면 Flipbook 끝날 때까지 유지
	if (_isAttacking && !_playerFlipbookPlayer->GetCurrentFlipbook()->IsPlaying())
	{
		// 공격 끝나면 Idle로 전환
		shared_ptr<Flipbook> idleFlipbook = nullptr;
		switch (_playerWeaponState)
		{
		case EPlayerWeaponState::Normal: idleFlipbook = _normal_idle_r; break;
		case EPlayerWeaponState::Sword:  idleFlipbook = _sword_idle_r;  break;
		case EPlayerWeaponState::Gun:    idleFlipbook = _gun_idle_r;    break;
		}

		if (idleFlipbook)
		{
			_playerFlipbookPlayer->SetFlipbook(idleFlipbook);
			idleFlipbook->Play();
		}

		_isAttacking = false;
	}

	// Flip 처리
	if (_playerUniformSet)
	{
		_playerUniformSet->Set("flip", _lastDir == Direction::Left);
		_playerUniformSet->Apply(_playerShader);
	}
}

void PlayerController::AttackNormal()
{

}

void PlayerController::AttackSword()
{

}

void PlayerController::AttackGun()
{
	if (INPUT.MouseClick(Inputs::Mouse::Left) && !_isAttacking && _gunTimer <= 0.0f)
	{
		shared_ptr<Flipbook> attackFlipbook = _gun_shot_r;
		if (!attackFlipbook) return;

		_playerFlipbookPlayer->SetFlipbook(attackFlipbook);
		attackFlipbook->Play();
		_isAttacking = true;

		// 총알 생성
		if (_bulletSpawner)
		{
			auto spawnerTransform = _bulletSpawnerObject->GetTransform();
			glm::vec3 spawnPos = spawnerTransform->GetWorldPosition();
			_bulletSpawner->SpawnBullet(spawnPos, _lastDir);
		}

		_gunTimer = _gunCooldown;
	}
}

void PlayerController::MovePlayer()
{
	auto pos = _ownerTransform->GetPosition();
	bool isMoving = false;

	if (INPUT.GetKey(Inputs::Key::D)) { pos.x += _moveSpeed * TIME.deltaTime; _lastDir = Direction::Right; isMoving = true; }
	if (INPUT.GetKey(Inputs::Key::A)) { pos.x -= _moveSpeed * TIME.deltaTime; _lastDir = Direction::Left; isMoving = true; }

	// 공격 중이면 Flipbook 덮어쓰기 금지
	if (!_isAttacking)
	{
		shared_ptr<Flipbook> flipbook = nullptr;
		if (isMoving)
		{
			switch (_playerWeaponState)
			{
			case EPlayerWeaponState::Normal: flipbook = _normal_walk_r; break;
			case EPlayerWeaponState::Gun:    flipbook = _gun_walk_r;    break;
			case EPlayerWeaponState::Sword:  flipbook = _sword_walk_r;  break;
			}
		}
		else
		{
			switch (_playerWeaponState)
			{
			case EPlayerWeaponState::Normal: flipbook = _normal_idle_r; break;
			case EPlayerWeaponState::Gun:    flipbook = _gun_idle_r;    break;
			case EPlayerWeaponState::Sword:  flipbook = _sword_idle_r;  break;
			}
		}

		if (flipbook)
			_playerFlipbookPlayer->SetFlipbook(flipbook);
	}

	if (_playerUniformSet)
	{
		_playerUniformSet->Set("flip", _lastDir == Direction::Left);
		_playerUniformSet->Apply(_playerShader);
	}

	SetAttackCollider();

	pos.x = clamp(pos.x, _minMoveDistance, _maxMoveDistance);
	_ownerTransform->SetPosition(pos);
}

void PlayerController::JumpPlayer()
{
	// 스페이스 입력 시 점프 처리
	if (INPUT.GetKeyDown(Inputs::Key::Space))
	{
		if (_playerRigidBody->IsGrounded())
			_playerRigidBody->Jump(1000.0f);
	}

	// 공중 상태일 때만 애니메이션 재생
	if (!_playerRigidBody->IsGrounded())
	{
		shared_ptr<Flipbook> fallFlipbook = nullptr;
		switch (_playerWeaponState)
		{
		case EPlayerWeaponState::Normal: fallFlipbook = _normal_fall_r; break;
		case EPlayerWeaponState::Gun:    fallFlipbook = _gun_jump_r;    break;
		case EPlayerWeaponState::Sword:  fallFlipbook = _sword_jump_r;  break;
		}

		if (fallFlipbook && _playerFlipbookPlayer->GetCurrentFlipbook() != fallFlipbook)
		{
			_playerFlipbookPlayer->SetFlipbook(fallFlipbook);
			fallFlipbook->Play();
		}
	}
}

void PlayerController::ChangeWeapon()
{
	if (INPUT.GetKeyDown(Inputs::Key::E))
	{
		int nextState = (static_cast<int>(_playerWeaponState) + 1) % static_cast<int>(EPlayerWeaponState::END);
		_playerWeaponState = static_cast<EPlayerWeaponState>(nextState);
	}

	// 모든 UI를 일단 비활성화
	if (_NoWeaponText)  _NoWeaponText->SetActive(false);
	if (_PistolText)    _PistolText->SetActive(false);
	if (_SwordText)     _SwordText->SetActive(false);

	// 현재 상태에 해당하는 UI만 활성화
	switch (_playerWeaponState)
	{
	case EPlayerWeaponState::Normal:
		if (_NoWeaponText) _NoWeaponText->SetActive(true);
		break;
	case EPlayerWeaponState::Gun:
		if (_PistolText) _PistolText->SetActive(true);
		break;
	case EPlayerWeaponState::Sword:
		if (_SwordText) _SwordText->SetActive(true);
		break;
	default:
		break;
	}
}

void PlayerController::SetAttackCollider()
{
	// 1. 총알 발사기 위치/활성화 설정
	if (_bulletSpawnerObject)
	{
		bool isGunner = (_playerWeaponState == EPlayerWeaponState::Gun);
		_bulletSpawnerObject->SetActive(isGunner);

		if (isGunner)
		{
			auto spawnerTransform = _bulletSpawnerObject->GetTransform();
			glm::vec3 localPos = spawnerTransform->GetPosition();
			localPos.x = (_lastDir == Direction::Left) ? -abs(localPos.x) : abs(localPos.x);
			spawnerTransform->SetPosition(localPos);
		}
	}

	// 2. 근접 공격 콜라이더들의 offset을 방향에 따라 즉시 조정
	if (_lastDir == Direction::Right)
	{
		// 오른쪽을 볼 때는 원본 offset을 그대로 사용
		// shared_ptr는 if문에서 바로 유효성 검사가 가능합니다.
		if (_normalAttackCollider)
			_normalAttackCollider->SetOffset(_normalAttackColliderOffset);
		if (_swordAttackCollider)
			_swordAttackCollider->SetOffset(_swordAttackColliderOffset);
	}
	else // Direction::Left
	{
		// 왼쪽을 볼 때는 원본 offset의 x값만 부호를 바꿔서 설정
		if (_normalAttackCollider)
		{
			glm::vec2 leftOffset = _normalAttackColliderOffset;
			leftOffset.x *= -1.0f;
			_normalAttackCollider->SetOffset(leftOffset);
		}
		if (_swordAttackCollider)
		{
			glm::vec2 leftOffset = _swordAttackColliderOffset;
			leftOffset.x *= -1.0f;
			_swordAttackCollider->SetOffset(leftOffset);
		}
	}
}
#pragma endregion

#pragma region COLLIDER_METHODS
void PlayerController::OnColliderWithEnemy(const shared_ptr<BoxCollider>& other)
{
	cout << "[Player Body] 적과 부딪힘!" << endl;
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