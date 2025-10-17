#pragma once
#include "Engine\Prefab.h"

class Bullet : public Prefab
{
	using Super = Prefab;

public:
	Bullet(const string& name);
	virtual ~Bullet() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;

private:
	shared_ptr<GameObject> _bullet;
	shared_ptr<Transform> _bulletTransform;

	shared_ptr<GameObject> _bulletCollider;
	shared_ptr<Transform> _bulletColliderTransform;
};

