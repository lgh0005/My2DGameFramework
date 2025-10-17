#pragma once
#include "Engine\Prefab.h"

class GameObject;

class Player : public Prefab
{
	using Super = Prefab;

public:
	Player(const string& name);
	virtual ~Player() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:
	shared_ptr<GameObject> _player;
	shared_ptr<Transform> _playerTransform;

	// Bullet spawner
	shared_ptr<GameObject> _bulletSpawner;
	shared_ptr<Transform> _bulletSpawnerTransform;

#pragma region COLLIDER_DEBUG
	// Attack area : normal state
	shared_ptr<GameObject> _attackArea1;
	shared_ptr<Transform> _attackAreaTransform1;

	// Attack area : sword state
	shared_ptr<GameObject> _attackArea2;
	shared_ptr<Transform> _attackAreaTransform2;

	// Player Collider
	shared_ptr<GameObject> _playerCollider;
	shared_ptr<Transform> _playerColliderTransform;
#pragma endregion
};

