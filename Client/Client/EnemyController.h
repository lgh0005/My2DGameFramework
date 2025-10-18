#pragma once
#include "Engine\IBehaviour.h"

#pragma region States
#include "EnemyWalkState.h"
#pragma endregion

enum class EEnemyState
{
	Walk,
	Damaged,
	Attack,
	Died,
	END
};

enum
{
	ENEMY_STATE_COUNT = static_cast<uint32>(EEnemyState::END)
};

class EnemyController : public IBehaviour
{
	using Super = IBehaviour;

	friend class EnemyWalkState;

public:
	EnemyController(const string& name);
	virtual ~EnemyController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*==============================
//     Default properties     //
//============================*/
private:
	int _health = 4;

/*=============================
//     Moving properties     //
//===========================*/
private:
	shared_ptr<Shader> _enemyShader;
	shared_ptr<UniformSet> _enemyUniformSet;
	shared_ptr<Transform> _ownerTransform;

	EDirection _lastDir = EDirection::Right;
	float _moveSpeed = 200.0f;
	float _maxMoveDistance = 2100.0f;
	float _minMoveDistance = -460.0f;

/*==============================
//     Collide properties     //
//============================*/
private:
	shared_ptr<BoxCollider> _enemyCollider;
	void OnColliderWithPlayerAttack(const shared_ptr<BoxCollider>& other);

	shared_ptr<BoxCollider> _normalAttackCollider;
	void OnColliderWithPlayer(const shared_ptr<BoxCollider>& other);
	glm::vec2 _normalAttackColliderOffset;

	void SetAttackCollider();

/*=============================
//     Attack properties     //
//===========================*/
private:
	bool _isAttacking = false;
	int _comboStep = 0;

/*=================================
//	   Enemy State Machine       //
//===============================*/
private:
	void ChangeState(const shared_ptr<StateMachine<EnemyController>>& newState);
	EEnemyState _enemyState = EEnemyState::Walk;
	shared_ptr<FlipbookPlayer> _enemyFlipbookPlayer;
	shared_ptr<StateMachine<EnemyController>> _currentState;

/*=============================
//     Enemy Flipbooks       //
//===========================*/
#pragma region FLIP_BOOKS
private:
	shared_ptr<Flipbook> _normal_combo_1_r;
	shared_ptr<Flipbook> _normal_combo_2_r;
	shared_ptr<Flipbook> _normal_combo_3_r;
	shared_ptr<Flipbook> _normal_damaged_r;
	shared_ptr<Flipbook> _normal_died_r;
	shared_ptr<Flipbook> _normal_idle_r;
	shared_ptr<Flipbook> _normal_walk_r;
#pragma endregion

	void ApplyFlipDirection();
};

