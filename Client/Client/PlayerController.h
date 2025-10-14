#pragma once
#include "Engine\IBehaviour.h"

enum class Direction
{
	Left,
	Right
};

enum class PlayerState
{
	// TODO
};

class PlayerController : public IBehaviour
{
	using Super = IBehaviour;

public:
	PlayerController(const string& name);
	virtual ~PlayerController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*=============================
//     Moving properties     //
//===========================*/
private:
	shared_ptr<Shader> _playerShader;
	shared_ptr< UniformSet> _playerUniformSet;

	shared_ptr<FlipbookPlayer> _playerFlipbookPlayer;

	shared_ptr<Transform> _ownerTransform;
	bool _isMoving = false;
	Direction _lastDir = Direction::Right;
	float _moveSpeed = 500.0f;

/*=============================
//     Player Flipbooks      //
//===========================*/
private:
#pragma region PLAYER_FLIPBOOK_NORMAL
	shared_ptr<Flipbook> _normal_climb;
	shared_ptr<Flipbook> _normal_combo_1_r;
	shared_ptr<Flipbook> _normal_combo_2_r;
	shared_ptr<Flipbook> _normal_combo_3_r;
	shared_ptr<Flipbook> _normal_damaged_r;
	shared_ptr<Flipbook> _normal_dash_r;
	shared_ptr<Flipbook> _normal_died_r;
	shared_ptr<Flipbook> _normal_fall_r;
	shared_ptr<Flipbook> _normal_idle_r;
	shared_ptr<Flipbook> _normal_jump_r;
	shared_ptr<Flipbook> _normal_run_r;
	shared_ptr<Flipbook> _normal_slide_r;
	shared_ptr<Flipbook> _normal_walk_r;
	shared_ptr<Flipbook> _normal_wallslide_r;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_GUN
	shared_ptr<Flipbook> _gun_climb;
	shared_ptr<Flipbook> _gun_air_attack_r;
	shared_ptr<Flipbook> _gun_damaged_r;
	shared_ptr<Flipbook> _gun_dash_r;
	shared_ptr<Flipbook> _gun_died_r;
	shared_ptr<Flipbook> _gun_idle_r;
	shared_ptr<Flipbook> _gun_jump_r;
	shared_ptr<Flipbook> _gun_run_r;
	shared_ptr<Flipbook> _gun_shot_r;
	shared_ptr<Flipbook> _gun_slide_r;
	shared_ptr<Flipbook> _gun_walk_r;
	shared_ptr<Flipbook> _gun_wallslide_r;
#pragma endregion

#pragma region PLAYER_FLIPBOOK_SWORD
	shared_ptr<Flipbook> _sword_climb;
	shared_ptr<Flipbook> _sword_air_attack_r;
	shared_ptr<Flipbook> _sword_combo_1_r;
	shared_ptr<Flipbook> _sword_combo_2_r;
	shared_ptr<Flipbook> _sword_combo_3_r;
	shared_ptr<Flipbook> _sword_damaged_r;
	shared_ptr<Flipbook> _sword_dash_r;
	shared_ptr<Flipbook> _sword_died_r;
	shared_ptr<Flipbook> _sword_idle_r;
	shared_ptr<Flipbook> _sword_jump_r;
	shared_ptr<Flipbook> _sword_run_r;
	shared_ptr<Flipbook> _sword_slide_r;
	shared_ptr<Flipbook> _sword_walk_r;
	shared_ptr<Flipbook> _sword_wallslide_r;
#pragma endregion
};

