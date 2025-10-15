#include "pch.h"
#include "Building2.h"

Building2::Building2(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Building2::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto buliding = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	buliding->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Building2"));
	buliding->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return buliding;
}
