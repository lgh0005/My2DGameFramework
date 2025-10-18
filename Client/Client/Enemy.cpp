#include "pch.h"
#include "Enemy.h"
#include "EnemyController.h"

Enemy::Enemy(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Enemy::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;
	auto& GameObjectList = scene->GetGameObjectList();

	// Enemy
	{
		_enemy = make_shared<GameObject>(name);
		_enemyTransform = make_shared<Transform>(name, position, rotation, scale);
		_enemy->SetTransform(_enemyTransform);
	}

	// flipbook
	{
		auto flipbook = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
		shared_ptr<Flipbook> flipbookCopy = make_shared<Flipbook>(*flipbook);
		auto flipbookPlayer = make_shared<FlipbookPlayer>("EnemyFlipbook", flipbookCopy);
		_enemy->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));
		scene->GetRenderPass("_enemyRenderPass")->AddRenderable(flipbookPlayer);
	}

	// AttackArea #1
	{
		shared_ptr<BoxCollider> enemyAttackCollider = make_shared<BoxCollider>("EnemyAttackCollider", glm::vec2(80.0f, 100.0f), glm::vec2(80.0f, -80.0f));
		enemyAttackCollider->SetLayer(CollisionLayer::Layers::EnemyAttack);
		enemyAttackCollider->SetMask(CollisionLayer::Layers::Player);
		_enemy->AddComponent(enemyAttackCollider);
	}

	// Main Collider
	{
		shared_ptr<BoxCollider> enemyCollider = make_shared<BoxCollider>("EnemyCollider", glm::vec2(60.0f, 150.0f), glm::vec2(0.0f, -50.0f));
		enemyCollider->SetLayer(CollisionLayer::Layers::Enemy);
		enemyCollider->SetMask(CollisionLayer::Layers::PlayerAttack | CollisionLayer::Layers::Bullet);
		_enemy->AddComponent(enemyCollider);
	}

	// Script
	{
		shared_ptr<EnemyController> script = make_shared<EnemyController>("EnemyController");
		script->SetCurrentScene(scene);
		_enemy->AddBehaviour(script);
	}

	return _enemy;
}
