#include "pch.h"
#include "House3.h"

House3::House3(const string& name) : Super(name)
{

}

shared_ptr<GameObject> House3::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto house = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	house->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("House3"));
	house->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return house;
}
