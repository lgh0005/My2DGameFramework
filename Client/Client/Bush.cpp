#include "pch.h"
#include "Bush.h"

Bush::Bush(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Bush::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto bush = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	bush->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Bush"));
	bush->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return bush;
}
