#pragma once
#include "Engine\Prefab.h"

class House3 : public Prefab
{
	using Super = Prefab;

public:
	House3(const string& name);
	virtual ~House3() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;
};

