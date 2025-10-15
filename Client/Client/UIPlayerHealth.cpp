#include "pch.h"
#include "UIPlayerHealth.h"

UIPlayerHealth::UIPlayerHealth(const string& name) : Super(name)
{

}

shared_ptr<GameObject> UIPlayerHealth::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto icon = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	icon->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("heart"));
	icon->AddRenderable(sprite);

	scene->GetRenderPass("_uiRenderPass")->AddRenderable(sprite);

	return icon;
}
