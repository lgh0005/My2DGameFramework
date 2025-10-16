#pragma once
#include "Engine\IBehaviour.h"

enum class EEnemyState
{
	Idle,
	Walk,
	Damaged,
	Attack,
	Died,
};

class EnemyController : public IBehaviour
{
	using Super = IBehaviour;

public:
	EnemyController(const string& name);
	virtual ~EnemyController() override = default;

public:
	virtual void Init() override;
	virtual void Update() override;

/*=============================
//     Moving properties     //
//===========================*/
private:
	void MoveEnemy();

	shared_ptr<Shader> _enemyShader;
	shared_ptr<UniformSet> _enemyUniformSet;
	shared_ptr<FlipbookPlayer> _playerFlipbookPlayer;
	shared_ptr<Transform> _ownerTransform;

	void SetEnemyState(EEnemyState state) { _enemyState = state; }
	EEnemyState _enemyState = EEnemyState::Idle;
	Direction _lastDir = Direction::Right;
	float _moveSpeed = 500.0f;

	float _maxMoveDistance = 2100.0f;
	float _minMoveDistance = -460.0f;

	void Attack();
	int _comboStep = 0;

	void Died();
	int _health = 4;

/*=============================
//     Enemy Flipbooks       //
//===========================*/
private:
	shared_ptr<Flipbook> _normal_combo_1_r;
	shared_ptr<Flipbook> _normal_combo_2_r;
	shared_ptr<Flipbook> _normal_combo_3_r;
	shared_ptr<Flipbook> _normal_damaged_r;
	shared_ptr<Flipbook> _normal_died_r;
	shared_ptr<Flipbook> _normal_idle_r;
	shared_ptr<Flipbook> _normal_walk_r;
};

