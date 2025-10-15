#pragma once
#include "Engine\Prefab.h"

class Bush : public Prefab
{
	using Super = Prefab;

public:
	Bush(const string& name);
	virtual ~Bush() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;
};

