#include "pch.h"
#include "Character.h"

#pragma region SCRIPT
#include "CharacterController.h"
#pragma endregion

shared_ptr<GameObject> Character::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto character = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	character->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto flipbook = RESOURCE.GetResource<Flipbook>("Character_Idle_right");
	static auto texture = RESOURCE.GetResource<Texture>("Test");

	auto flipbookPlayer = make_shared<FlipbookPlayer>("CharacterFlipbook", flipbook);
	character->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	auto collider = make_shared<BoxCollider>("PlayerCollider", glm::vec2(100.0f, 200.0f));
	COLLIDER.AddColliderComponent(collider);
	character->AddComponent(collider);

	shared_ptr<CharacterController> script = make_shared<CharacterController>("PlayerController");
	character->AddBehaviour(static_pointer_cast<IBehaviour>(script));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	return character;
}
