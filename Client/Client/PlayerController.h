#pragma once
#include "Engine\IBehaviour.h"

#pragma region States
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerJumpState.h"
#include "PlayerAttackState.h"
#include "PlayerDamageState.h"
#include "PlayerDieState.h"
#pragma endregion

class BulletSpawner;

enum class EPlayerWeaponState
{
	Normal,
	Gun,
	Sword,
	END
};

enum class EPlayerState
{
	Idle,
	Walk,
	Damaged,
	Attack,
	Died,
	Jump,
	END
};

enum
{
	PLAYER_WEAPON_STATE_COUNT = static_cast<uint32>(EPlayerWeaponState::END),
	PLAYER_STATE_COUNT = static_cast<uint32>(EPlayerState::END)
};

class PlayerController : public IBehaviour
{
	using Super = IBehaviour;

	friend class PlayerIdleState;
	friend class PlayerWalkState;
	friend class PlayerJumpState;
	friend class PlayerAttackState;
	friend class PlayerDamageState;
	friend class PlayterDieState;

public:
	PlayerController(const string& name);
	virtual ~PlayerController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*==============================
//     Collide properties     //
//============================*/
private:
	shared_ptr<BoxCollider> _playerCollider;
	void OnColliderWithEnemy(const shared_ptr<BoxCollider>& other);

	shared_ptr<BoxCollider> _normalAttackCollider;
	void OnCollideNormalAttackArea(const shared_ptr<BoxCollider>& other);
	glm::vec2 _normalAttackColliderOffset;

	shared_ptr<BoxCollider> _swordAttackCollider;
	void OnCollideSwordAttackArea(const shared_ptr<BoxCollider>& other);
	glm::vec2 _swordAttackColliderOffset;

	void SetAttackCollider();

/*=============================
//     Moving properties     //
//===========================*/
private:
	shared_ptr<Shader> _playerShader;
	shared_ptr<UniformSet> _playerUniformSet;

	shared_ptr<Transform> _ownerTransform;
	bool _isMoving = false;
	EDirection _lastDir = EDirection::Right;
	float _moveSpeed = 500.0f;

	float _maxMoveDistance = 2100.0f;
	float _minMoveDistance = -460.0f;

	shared_ptr<RigidBody> _playerRigidBody;

/*=============================
//     Attack properties     //
//===========================*/
private:
	bool _isAttacking = false;
	int _comboStep = 0; 

	shared_ptr<GameObject> _bulletSpawnerObject;
	shared_ptr<BulletSpawner> _bulletSpawner;
	float _gunCooldown = 1.0f;
	float _gunTimer = 0.0f;
	void HandleWeaponChange();

/*=================================
//     Player State Machine      //
//===============================*/
private:
	void ChangeState(const shared_ptr<StateMachine<PlayerController>>& newState);
	EPlayerWeaponState _playerWeaponState = EPlayerWeaponState::Normal;
	EPlayerState _playerState = EPlayerState::Idle;
	shared_ptr<StateMachine<PlayerController>> _currentState;
	shared_ptr<FlipbookPlayer> _playerFlipbookPlayer;

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

	void ApplyFlipDirection();
	shared_ptr<GameObject> _NoWeaponText;
	shared_ptr<GameObject> _PistolText;
	shared_ptr<GameObject> _SwordText;
};

