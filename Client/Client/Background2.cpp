#include "pch.h"
#include "Background2.h"

Background2::Background2(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Background2::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto background = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	background->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Background2"));
	sprite->SetParallaxFactor(0.96f);
	background->AddRenderable(sprite);

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return background;
}
