#include "pch.h"
#include "Enemy.h"

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
		_attackArea1 = make_shared<GameObject>("EnemyAttackArea1");
		_attackAreaTransform1 = make_shared<Transform>
			(
				"EnemyAttackAreaTransform",
				glm::vec3(80.0f, -80.0f, 0.0f),
				glm::vec3(0.0f),
				glm::vec3(80.0f, 100.0f, 1.0f)
			);
		shared_ptr<Sprite> testSprite = make_shared<Sprite>("TestSprite", RESOURCE.GetResource<Texture>("TEST1"));
		_attackArea1->AddRenderable(testSprite);
		_attackArea1->SetTransform(_attackAreaTransform1);
		_attackArea1->SetParent(_enemy);
		scene->GetRenderPass("_debugRenderPass")->AddRenderable(testSprite);
		GameObjectList.push_back(_attackArea1);
	}

	// Main Collider
	{
		_enemyCollider = make_shared<GameObject>("EnemyCollider");
		_enemyColliderTransform = make_shared<Transform>
			(
				"EnemyCollider",
				glm::vec3(0.0f, -50.0f, 0.0f),
				glm::vec3(0.0f),
				glm::vec3(80.0f, 150.0f, 1.0f)
			);
		_enemyCollider->SetTransform(_enemyColliderTransform);
		_enemyCollider->SetParent(_enemy);

		shared_ptr<BoxCollider> enemyCollider = make_shared<BoxCollider>("EnemyCollider", glm::vec2(1.0f, 1.0f));
		_enemyCollider->AddComponent(enemyCollider);

		shared_ptr<Sprite> testSprite = make_shared<Sprite>("TestSprite3", RESOURCE.GetResource<Texture>("TEST3"));
		_enemyCollider->AddRenderable(testSprite);
		scene->GetRenderPass("_debugRenderPass")->AddRenderable(testSprite);
		GameObjectList.push_back(_enemyCollider);
	}

	return _enemy;
}
