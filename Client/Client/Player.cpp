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
	auto& GameObjectList = scene->GetGameObjectList();

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
		_bulletSpawner->SetTransform(_bulletSpawnerTransform);
		shared_ptr<BulletSpawner> spawner = make_shared<BulletSpawner>("BulletSpawner");
		spawner->SetCurrentScene(scene);
		_bulletSpawner->AddBehaviour(spawner);
		_bulletSpawner->SetParent(_player);
		_bulletSpawner->SetActive(false);
		GameObjectList.push_back(_bulletSpawner);
	}

	// Flipbook
	{
		auto flipbook = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
		shared_ptr<Flipbook> flipbookCopy = make_shared<Flipbook>(*flipbook);
		auto flipbookPlayer = make_shared<FlipbookPlayer>("PlayerFlipbook", flipbookCopy);
		_player->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));
		scene->GetRenderPass("_playerRenderPass")->AddRenderable(flipbookPlayer);
	}

	// Main player collider
	{
		shared_ptr<BoxCollider> playerCollider = make_shared<BoxCollider>("PlayerMainCollider", glm::vec2(80.0f, 150.0f), glm::vec2(0.0f, -50.0f));
		playerCollider->SetLayer(CollisionLayer::Layers::Player);
		playerCollider->SetMask(CollisionLayer::Layers::EnemyAttack);
		_player->AddComponent(playerCollider);
	}

	// AttackArea #1 : Normal
	{
		shared_ptr<BoxCollider> normalAttackArea = make_shared<BoxCollider>("PlayerAttackAreaNormal", glm::vec2(90.0f, 100.0f), glm::vec2(100.0f, -50.0f));
		normalAttackArea->SetLayer(CollisionLayer::Layers::PlayerAttack);
		normalAttackArea->SetMask(CollisionLayer::Layers::Enemy);
		_player->AddComponent(normalAttackArea);
	}

	// AttackArea #2 : Sword
	{
		shared_ptr<BoxCollider> swordAttackArea = make_shared<BoxCollider>("PlayerAttackAreaSword", glm::vec2(80.0f, 100.0f), glm::vec2(115.0f, -50.0f));
		swordAttackArea->SetLayer(CollisionLayer::Layers::PlayerAttack);
		swordAttackArea->SetMask(CollisionLayer::Layers::Enemy);
		_player->AddComponent(swordAttackArea);
	}

	// Player controller
	{
		shared_ptr<PlayerController> script = make_shared<PlayerController>("PlayerController");
		script->SetCurrentScene(scene);
		_player->AddBehaviour(script);
	}

	// RigidBody
	{
		shared_ptr<RigidBody> rigidBody = make_shared<RigidBody>("PlayerJumper", -3200.0f, 100.0f);
		rigidBody->SetGroundY(position.y);
		_player->AddComponent(rigidBody);
	}

	return _player;
}
