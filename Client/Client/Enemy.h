#pragma once
#include "Engine\Prefab.h"

class Enemy : public Prefab
{
	using Super = Prefab;

public:
	Enemy(const string& name);
	virtual ~Enemy() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:
	shared_ptr<GameObject> _enemy;
	shared_ptr<Transform> _enemyTransform;

	// DEBUG : Attack area : normal state
	shared_ptr<GameObject> _attackArea1;
	shared_ptr<Transform> _attackAreaTransform1;

	// DEBUG : Player Collider
	shared_ptr<GameObject> _enemyCollider;
	shared_ptr<Transform> _enemyColliderTransform;
};

