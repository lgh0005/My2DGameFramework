#include "pch.h"
#include "Player.h"

#pragma region SCRIPT
#include "PlayerController.h"
#include "BulletSpawner.h"
#pragma endregion

Player::Player(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Player::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	// Player
	{
		_player = make_shared<GameObject>(name);
		_playerTransform = make_shared<Transform>(name, position, rotation, scale);
		_player->SetTransform(_playerTransform);
	}

	// Bullet spanwer
	{
		_bulletSpawner = make_shared<GameObject>("BulletSpawner");
		_bulletSpawnerTransform = make_shared<Transform>
			(
				"BulletSpawner",
				glm::vec3(120.0f, -40.0f, 0.0f),
				glm::vec3(0.0f),
				glm::vec3(50.0f, 50.0f, 1.0f)
			);
		shared_ptr<Sprite> testSprite = make_shared<Sprite>("TestSprite3", RESOURCE.GetResource<Texture>("TEST3"));
		_bulletSpawner->AddRenderable(testSprite);
		_bulletSpawner->SetTransform(_bulletSpawnerTransform);
		shared_ptr<BulletSpawner> spawner = make_shared<BulletSpawner>("BulletSpawner");
		spawner->SetCurrentScene(scene);
		_bulletSpawner->AddBehaviour(spawner);
		_bulletSpawner->SetParent(_player);
		_bulletSpawner->SetActive(false);
		scene->GetRenderPass("_debugRenderPass")->AddRenderable(testSprite);
		scene->GetGameObjectList().push_back(_bulletSpawner);
	}

	// AttackArea #1
	{
		_attackArea1 = make_shared<GameObject>("PlayerAttackArea1");
		_attackAreaTransform1 = make_shared<Transform>
			(
				"PlayerAttackAreaTransform", 
				glm::vec3(80.0f, -80.0f, 0.0f), 
				glm::vec3(0.0f), 
				glm::vec3(80.0f, 100.0f, 1.0f)
			);
		shared_ptr<Sprite> testSprite = make_shared<Sprite>("TestSprite", RESOURCE.GetResource<Texture>("TEST1"));
		_attackArea1->AddRenderable(testSprite);
		_attackArea1->SetTransform(_attackAreaTransform1);
		_attackArea1->SetParent(_player);
		_attackArea1->SetActive(false);
		scene->GetRenderPass("_debugRenderPass")->AddRenderable(testSprite);
		scene->GetGameObjectList().push_back(_attackArea1);
	}

	// AttackArea #2
	{
		_attackArea2 = make_shared<GameObject>("PlayerAttackArea2");
		_attackAreaTransform2 = make_shared<Transform>
			(
				"PlayerAttackAreaTransform",
				glm::vec3(80.0f, -80.0f, 0.0f),
				glm::vec3(0.0f),
				glm::vec3(110.0f, 100.0f, 1.0f)
			);
		shared_ptr<Sprite> testSprite = make_shared<Sprite>("TestSprite2", RESOURCE.GetResource<Texture>("TEST2"));
		_attackArea2->AddRenderable(testSprite);
		_attackArea2->SetTransform(_attackAreaTransform2);
		_attackArea2->SetParent(_player);
		_attackArea2->SetActive(false);
		scene->GetRenderPass("_debugRenderPass")->AddRenderable(testSprite);
		scene->GetGameObjectList().push_back(_attackArea2);
	}

	// Flipbook
	{
		auto flipbook = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
		shared_ptr<Flipbook> flipbookCopy = make_shared<Flipbook>(*flipbook);
		auto flipbookPlayer = make_shared<FlipbookPlayer>("PlayerFlipbook", flipbookCopy);
		_player->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));
		scene->GetRenderPass("_playerRenderPass")->AddRenderable(flipbookPlayer);
	}

	// Collider
	{
		auto collider1 = make_shared<BoxCollider>("Player_WallCollider", glm::vec2(80.0f, 250.0f));
		COLLIDER.AddColliderComponent(collider1);
		_player->AddComponent(collider1);
	}

	// Player controller
	{
		shared_ptr<PlayerController> script = make_shared<PlayerController>("PlayerController");
		shared_ptr<Scene> scene;
		if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;
		script->SetCurrentScene(scene);
		_player->AddBehaviour(static_pointer_cast<IBehaviour>(script));
	}

	// RigidBody
	{
		shared_ptr<RigidBody> rigidBody = make_shared<RigidBody>("PlayerJumper", -3200.0f, 100.0f);
		rigidBody->SetGroundY(position.y);
		_player->AddComponent(rigidBody);
	}

	return _player;
}
