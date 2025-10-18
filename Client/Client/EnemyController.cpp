#include "pch.h"
#include "EnemyController.h"

EnemyController::EnemyController(const string& name) : Super(name)
{
	_enemyShader = RESOURCE.GetResource<Shader>("EnemyShader");
	_enemyUniformSet = RESOURCE.GetResource<UniformSet>("EnemyUniforms");
}

void EnemyController::Init()
{
	auto self = GetSelf<EnemyController>();
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr<Scene>(_currentScene, scene) == false) return;

	// Get transform
	_ownerTransform = owner->GetTransform();

	// Get FlipbookPlayer
	_enemyFlipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("EnemyFlipbook"));

	// Get Flipbooks
	{
		auto src_combo_1 = RESOURCE.GetResource<Flipbook>("_normal_combo_1_r");
		if (src_combo_1) _normal_combo_1_r = make_shared<Flipbook>(*src_combo_1);

		auto src_combo_2 = RESOURCE.GetResource<Flipbook>("_normal_combo_2_r");
		if (src_combo_2) _normal_combo_2_r = make_shared<Flipbook>(*src_combo_2);

		auto src_combo_3 = RESOURCE.GetResource<Flipbook>("_normal_combo_3_r");
		if (src_combo_3) _normal_combo_3_r = make_shared<Flipbook>(*src_combo_3);

		auto src_damaged = RESOURCE.GetResource<Flipbook>("_normal_damaged_r");
		if (src_damaged) _normal_damaged_r = make_shared<Flipbook>(*src_damaged);

		auto src_died = RESOURCE.GetResource<Flipbook>("_normal_died_r");
		if (src_died) _normal_died_r = make_shared<Flipbook>(*src_died);

		auto src_idle = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
		if (src_idle) _normal_idle_r = make_shared<Flipbook>(*src_idle);

		auto src_walk = RESOURCE.GetResource<Flipbook>("_normal_walk_r");
		if (src_walk) _normal_walk_r = make_shared<Flipbook>(*src_walk);
	}

	// Get Collider
	_enemyCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("EnemyCollider"));
	_enemyCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnColliderWithPlayerAttack(other); });
	_normalAttackCollider = static_pointer_cast<BoxCollider>(owner->GetComponent("EnemyAttackCollider"));
	_normalAttackCollider->SetCollisionEnterCallback([self](const shared_ptr<BoxCollider>& other) { self->OnColliderWithPlayer(other); });
	_normalAttackColliderOffset = _normalAttackCollider->GetOffset();

	// Ensure initial state
	_enemyState = EEnemyState::Walk;
	_lastDir = EDirection::Right;

	// Set first state : Idle
	_currentState = make_shared<EnemyWalkState>();
	_currentState->Enter(self);
}

void EnemyController::Update()
{
	auto self = static_pointer_cast<EnemyController>(shared_from_this());
	_currentState->Update(self);
}

void EnemyController::ChangeState(const shared_ptr<StateMachine<EnemyController>>& newState)
{
	auto self = static_pointer_cast<EnemyController>(shared_from_this());
	if (_currentState) _currentState->Exit(self);
	_currentState = newState;
	_currentState->Enter(self);
}

void EnemyController::ApplyFlipDirection()
{
	if (_enemyFlipbookPlayer)
	{
		_enemyUniformSet->Set("flip", _lastDir == EDirection::Left);
		_enemyUniformSet->Apply(_enemyShader);
	}
}

void EnemyController::SetAttackCollider()
{
	const float dir = (_lastDir == EDirection::Left) ? -1.0f : 1.0f;

	if (_normalAttackCollider)
	{
		glm::vec2 newOffset = _normalAttackColliderOffset;
		newOffset.x *= dir;
		_normalAttackCollider->SetOffset(newOffset);
	}
}

void EnemyController::OnColliderWithPlayerAttack(const shared_ptr<BoxCollider>& other)
{
	// TODO
}

void EnemyController::OnColliderWithPlayer(const shared_ptr<BoxCollider>& other)
{
	// TODO
}
