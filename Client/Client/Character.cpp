#include "pch.h"
#include "Character.h"

#pragma region SCRIPT
#include "example1.h"
#pragma endregion

shared_ptr<GameObject> Character::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto character = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	character->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto flipbook = RESOURCE.GetResource<Flipbook>("Character_Idle");

	auto flipbookPlayer = make_shared<FlipbookPlayer>(name, flipbook);
	character->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	shared_ptr<example1> script = make_shared<example1>("PlayerController");
	character->AddBehaviour(static_pointer_cast<IBehaviour>(script));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	return character;
}
