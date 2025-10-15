#pragma once
#include "Engine\Prefab.h"

class Tree2 : public Prefab
{
	using Super = Prefab;

public:
	Tree2(const string& name);
	virtual ~Tree2() override = default;

public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;
};