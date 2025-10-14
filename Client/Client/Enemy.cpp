#include "pch.h"
#include "Enemy.h"

shared_ptr<GameObject> Enemy::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto enemy = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	enemy->SetTransform(transform);

	static auto flipbook = RESOURCE.GetResource<Flipbook>("_normal_idle_r");

	auto flipbookPlayer = make_shared<FlipbookPlayer>("PlayerFlipbook", flipbook);
	enemy->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	return enemy;
}
