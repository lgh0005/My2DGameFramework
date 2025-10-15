#include "pch.h"
#include "Building3.h"

Building3::Building3(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Building3::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto buliding = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	buliding->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Building3"));
	buliding->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return buliding;
}
