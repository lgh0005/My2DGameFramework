#pragma once
#include "Engine\Prefab.h"

class UIPlayerHealth : public Prefab
{
	using Super = Prefab;

public:
	UIPlayerHealth(const string& name);
	virtual ~UIPlayerHealth() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;
};

