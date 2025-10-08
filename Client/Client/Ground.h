#pragma once
#include "Engine/Prefab.h"

class RenderPass;

class Ground : public Prefab
{
public:
	virtual shared_ptr<GameObject> Instantiate
	(
		const string& name,
		const glm::vec3& position,
		const glm::vec3& rotation = glm::vec3(0.0f),
		const glm::vec3& scale = glm::vec3(1.0f)
	) override;
};

