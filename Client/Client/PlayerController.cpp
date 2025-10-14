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
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	// Get transform
	_ownerTransform = owner->GetTransform();

	// Get FlipbookPlayer
	_playerFlipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("PlayerFlipbook"));
}

void PlayerController::Update()
{
	auto pos = _ownerTransform->GetPosition();

	if (INPUT.GetKey(Inputs::Key::D))
	{
		pos.x += _moveSpeed * TIME.deltaTime;
		_playerFlipbookPlayer->SetFlipbook(_normal_walk_r);
		_lastDir = Direction::Right;
	}
	else if (INPUT.GetKey(Inputs::Key::A))
	{
		pos.x -= _moveSpeed * TIME.deltaTime;
		_playerFlipbookPlayer->SetFlipbook(_normal_walk_r);
		_lastDir = Direction::Left;
	}
	else
	{
		_playerFlipbookPlayer->SetFlipbook(_normal_idle_r);
	}

	if (_playerUniformSet)
	{
		_playerUniformSet->Set("flip", _lastDir == Direction::Left);
		_playerUniformSet->Apply(_playerShader);
	}

	_ownerTransform->SetPosition(pos);
}

