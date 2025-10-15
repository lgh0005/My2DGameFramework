#include "pch.h"
#include "Background1.h"

Background1::Background1(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Background1::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto background = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	background->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Background1"));
	sprite->SetParallaxFactor(0.92f);
	background->AddRenderable(sprite);

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return background;
}
