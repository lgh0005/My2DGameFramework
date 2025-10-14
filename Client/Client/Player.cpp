#include "pch.h"
#include "Player.h"

#pragma region SCRIPT
#include "PlayerController.h"
#pragma endregion

shared_ptr<GameObject> Player::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto player = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	player->SetTransform(transform);

	static auto flipbook = RESOURCE.GetResource<Flipbook>("_normal_idle_r");

	auto flipbookPlayer = make_shared<FlipbookPlayer>("PlayerFlipbook", flipbook);
	player->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	shared_ptr<PlayerController> script = make_shared<PlayerController>("PlayerController");
	player->AddBehaviour(static_pointer_cast<IBehaviour>(script));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	return player;
}
