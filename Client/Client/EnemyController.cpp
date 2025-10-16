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
	// 1. minMoveDistance�� maxDist�� �����ϸ� ������ �ٲ㼭 �����δ�.
	// 2. ���� �ð� ������ �ּ� Idle ���°� �ǵ��� �����.
}

void EnemyController::Attack()
{
	// TODO
	// 1. ���°� Attack�� �Ǵ� �� ���� Ȯ���� �� ���� �ִϸ��̼��� �ٲ۴�.
	// 2. [�÷��̾ Enemy�� ���� ������ ��Ҵٸ� ü���� �ϳ� ��´�.]
}

void EnemyController::Died()
{
	// TODO
	// 0. ü���� 0�������� üũ -> ���ϸ� ���¸� Died�� �ٲ۴�.
	// 1. ���°� Died���� üũ
	// 2. Died �ִϸ��̼����� ��ȯ
	// 3. ��ü �Ҹ�
}
