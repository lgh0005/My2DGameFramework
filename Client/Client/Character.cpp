#include "pch.h"
#include "Character.h"
#include "CharacterController.h"

Character::Character(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Character::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto character = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	character->SetTransform(transform);

	auto flipbookPlayer = make_shared<FlipbookPlayer>("CharacterFlipbook", RESOURCE.GetResource<Flipbook>("Character_Idle_right"));
	character->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	auto collider = make_shared<BoxCollider>("PlayerCollider", glm::vec2(100.0f, 200.0f));
	COLLIDER.AddColliderComponent(collider);
	character->AddComponent(collider);

	shared_ptr<CharacterController> script = make_shared<CharacterController>("CharacterController");
	character->AddBehaviour(static_pointer_cast<IBehaviour>(script));

	scene->GetRenderPass("_CharacterRenderPass")->AddRenderable(flipbookPlayer);

	return character;
}
