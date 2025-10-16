#include "pch.h"
#include "EnemyController.h"

EnemyController::EnemyController(const string& name) : Super(name)
{
	_enemyShader = RESOURCE.GetResource<Shader>("EnemyShader");
	_enemyUniformSet = RESOURCE.GetResource<UniformSet>("EnemyUniforms");

	_normal_combo_1_r = RESOURCE.GetResource<Flipbook>("_normal_combo_1_r");
	_normal_combo_2_r = RESOURCE.GetResource<Flipbook>("_normal_combo_2_r");
	_normal_combo_3_r = RESOURCE.GetResource<Flipbook>("_normal_combo_3_r");
	_normal_damaged_r = RESOURCE.GetResource<Flipbook>("_normal_damaged_r");
	_normal_died_r = RESOURCE.GetResource<Flipbook>("_normal_died_r");
	_normal_idle_r = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
	_normal_walk_r = RESOURCE.GetResource<Flipbook>("_normal_walk_r");
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
	_playerFlipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("EnemyFlipbook"));

	// Ensure initial state
	_enemyState = EEnemyState::Idle;
	_lastDir = Direction::Right;
}

void EnemyController::Update()
{
	MoveEnemy();
	Attack();
	Died();
}

void EnemyController::MoveEnemy()
{
	// TODO
	// 1. minMoveDistance와 maxDist에 도달하면 방향을 바꿔서 움직인다.
	// 2. 랜덤 시간 간격을 둬서 Idle 상태가 되도록 만든다.
}

void EnemyController::Attack()
{
	// TODO
	// 1. 상태가 Attack이 되는 지 먼저 확인을 한 다음 애니메이션을 바꾼다.
	// 2. [플레이어가 Enemy의 공격 영역에 닿았다면 체력을 하나 깎는다.]
}

void EnemyController::Died()
{
	// TODO
	// 0. 체력이 0이하인지 체크 -> 이하면 상태를 Died로 바꾼다.
	// 1. 상태가 Died인지 체크
	// 2. Died 애니메이션으로 전환
	// 3. 객체 소멸
}
