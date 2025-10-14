#include "pch.h"
#include "PlayerController.h"

PlayerController::PlayerController(const string& name) : Super(name)
{
	_playerShader = RESOURCE.GetResource<Shader>("PlayerShader");
	_playerUniformSet = RESOURCE.GetResource<UniformSet>("PlayerUniforms");

	// ==========================
	// Normal Flipbooks
	// ==========================
	_normal_climb = RESOURCE.GetResource<Flipbook>("_normal_climb");
	_normal_combo_1_r = RESOURCE.GetResource<Flipbook>("_normal_combo_1_r");
	_normal_combo_2_r = RESOURCE.GetResource<Flipbook>("_normal_combo_2_r");
	_normal_combo_3_r = RESOURCE.GetResource<Flipbook>("_normal_combo_3_r");
	_normal_damaged_r = RESOURCE.GetResource<Flipbook>("_normal_damaged_r");
	_normal_dash_r = RESOURCE.GetResource<Flipbook>("_normal_dash_r");
	_normal_died_r = RESOURCE.GetResource<Flipbook>("_normal_died_r");
	_normal_fall_r = RESOURCE.GetResource<Flipbook>("_normal_fall_r");
	_normal_idle_r = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
	_normal_jump_r = RESOURCE.GetResource<Flipbook>("_normal_jump_r");
	_normal_run_r = RESOURCE.GetResource<Flipbook>("_normal_run_r");
	_normal_slide_r = RESOURCE.GetResource<Flipbook>("_normal_slide_r");
	_normal_walk_r = RESOURCE.GetResource<Flipbook>("_normal_walk_r");
	_normal_wallslide_r = RESOURCE.GetResource<Flipbook>("_normal_wallslide_r");

	// ==========================
	// Gun Flipbooks
	// ==========================
	_gun_climb = RESOURCE.GetResource<Flipbook>("_gun_climb");
	_gun_air_attack_r = RESOURCE.GetResource<Flipbook>("_gun_air_attack_r");
	_gun_damaged_r = RESOURCE.GetResource<Flipbook>("_gun_damaged_r");
	_gun_dash_r = RESOURCE.GetResource<Flipbook>("_gun_dash_r");
	_gun_died_r = RESOURCE.GetResource<Flipbook>("_gun_died_r");
	_gun_idle_r = RESOURCE.GetResource<Flipbook>("_gun_idle_r");
	_gun_jump_r = RESOURCE.GetResource<Flipbook>("_gun_jump_r");
	_gun_run_r = RESOURCE.GetResource<Flipbook>("_gun_run_r");
	_gun_shot_r = RESOURCE.GetResource<Flipbook>("_gun_shot_r");
	_gun_slide_r = RESOURCE.GetResource<Flipbook>("_gun_slide_r");
	_gun_walk_r = RESOURCE.GetResource<Flipbook>("_gun_walk_r");
	_gun_wallslide_r = RESOURCE.GetResource<Flipbook>("_gun_wallslide_r");

	// ==========================
	// Sword Flipbooks
	// ==========================
	_sword_climb = RESOURCE.GetResource<Flipbook>("_sword_climb");
	_sword_air_attack_r = RESOURCE.GetResource<Flipbook>("_sword_air_attack_r");
	_sword_combo_1_r = RESOURCE.GetResource<Flipbook>("_sword_combo_1_r");
	_sword_combo_2_r = RESOURCE.GetResource<Flipbook>("_sword_combo_2_r");
	_sword_combo_3_r = RESOURCE.GetResource<Flipbook>("_sword_combo_3_r");
	_sword_damaged_r = RESOURCE.GetResource<Flipbook>("_sword_damaged_r");
	_sword_dash_r = RESOURCE.GetResource<Flipbook>("_sword_dash_r");
	_sword_died_r = RESOURCE.GetResource<Flipbook>("_sword_died_r");
	_sword_idle_r = RESOURCE.GetResource<Flipbook>("_sword_idle_r");
	_sword_jump_r = RESOURCE.GetResource<Flipbook>("_sword_jump_r");
	_sword_run_r = RESOURCE.GetResource<Flipbook>("_sword_run_r");
	_sword_slide_r = RESOURCE.GetResource<Flipbook>("_sword_slide_r");
	_sword_walk_r = RESOURCE.GetResource<Flipbook>("_sword_walk_r");
	_sword_wallslide_r = RESOURCE.GetResource<Flipbook>("_sword_wallslide_r");
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
	_wallCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("Player_WallCollider"));
	_wallCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnColliderWithWall(other); });

	// Ensure initial state
	_playerState = PlayerState::Normal;
	_lastDir = Direction::Right;

	// Get GameObject
	_NoWeaponText = scene->GetGameObject("NoWeapon");
	_PistolText = scene->GetGameObject("PistolText");
	_SwordText = scene->GetGameObject("SwordText");
}

void PlayerController::Update()
{
	MovePlayer();
	ChangeWeapon();
	Attack();
}

void PlayerController::ChangeWeapon()
{
	if (INPUT.GetKeyDown(Inputs::Key::E))
	{
		int nextState = (static_cast<int>(_playerState) + 1) % static_cast<int>(PlayerState::END);
		_playerState = static_cast<PlayerState>(nextState);
	}

	// 모든 UI를 일단 비활성화
	if (_NoWeaponText)  _NoWeaponText->SetActive(false);
	if (_PistolText)    _PistolText->SetActive(false);
	if (_SwordText)     _SwordText->SetActive(false);

	// 현재 상태에 해당하는 UI만 활성화
	switch (_playerState)
	{
	case PlayerState::Normal:
		if (_NoWeaponText) _NoWeaponText->SetActive(true);
		break;
	case PlayerState::Gun:
		if (_PistolText) _PistolText->SetActive(true);
		break;
	case PlayerState::Sword:
		if (_SwordText) _SwordText->SetActive(true);
		break;
	default:
		break;
	}
}

void PlayerController::Attack()
{
	shared_ptr<Flipbook> attackFlipbook = nullptr;

	// 현재 콤보 단계에 따라 공격 Flipbook 선택
	if (_playerState == PlayerState::Normal)
	{
		switch (_comboStep)
		{
		case 0: attackFlipbook = _normal_combo_1_r; break;
		case 1: attackFlipbook = _normal_combo_2_r; break;
		case 2: attackFlipbook = _normal_combo_3_r; break;
		}
	}
	else if (_playerState == PlayerState::Sword)
	{
		switch (_comboStep)
		{
		case 0: attackFlipbook = _sword_combo_1_r; break;
		case 1: attackFlipbook = _sword_combo_2_r; break;
		case 2: attackFlipbook = _sword_combo_3_r; break;
		}
	}
	else if (_playerState == PlayerState::Gun)
	{
		attackFlipbook = _gun_shot_r;
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
		if (_playerState != PlayerState::Gun) // Gun은 단일 공격
			_comboStep = (_comboStep + 1) % 3;
	}

	// 공격 중이면 Flipbook 끝날 때까지 유지
	if (_isAttacking && !_playerFlipbookPlayer->GetCurrentFlipbook()->IsPlaying())
	{
		// 공격 끝나면 Idle로 전환
		shared_ptr<Flipbook> idleFlipbook = nullptr;
		switch (_playerState)
		{
		case PlayerState::Normal: idleFlipbook = _normal_idle_r; break;
		case PlayerState::Sword:  idleFlipbook = _sword_idle_r;  break;
		case PlayerState::Gun:    idleFlipbook = _gun_idle_r;    break;
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


void PlayerController::OnColliderWithWall(const shared_ptr<BoxCollider>& other)
{
	shared_ptr<GameObject> otherOwner;
	if (Utils::IsValidPtr(other->GetOwner(), otherOwner) == false) return;

	auto playerPos = _ownerTransform->GetPosition();
	glm::vec2 playerHalf = _wallCollider->GetSize() * 0.5f;

	auto otherPos = otherOwner->GetTransform()->GetPosition();
	glm::vec2 otherHalf = other->GetSize() * 0.5f;

	// 오른쪽 이동 중 벽에 충돌
	if (_lastDir == Direction::Right)
	{
		float maxX = otherPos.x - otherHalf.x - playerHalf.x;
		if (playerPos.x > maxX) playerPos.x = maxX;
	}
	// 왼쪽 이동 중 벽에 충돌
	else if (_lastDir == Direction::Left)
	{
		float minX = otherPos.x + otherHalf.x + playerHalf.x;
		if (playerPos.x < minX) playerPos.x = minX;
	}

	_ownerTransform->SetPosition(playerPos);
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
			switch (_playerState)
			{
			case PlayerState::Normal: flipbook = _normal_walk_r; break;
			case PlayerState::Gun:    flipbook = _gun_walk_r;    break;
			case PlayerState::Sword:  flipbook = _sword_walk_r;  break;
			}
		}
		else
		{
			switch (_playerState)
			{
			case PlayerState::Normal: flipbook = _normal_idle_r; break;
			case PlayerState::Gun:    flipbook = _gun_idle_r;    break;
			case PlayerState::Sword:  flipbook = _sword_idle_r;  break;
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

	pos.x = clamp(pos.x, _minMoveDistance, _maxMoveDistance);
	_ownerTransform->SetPosition(pos);
}