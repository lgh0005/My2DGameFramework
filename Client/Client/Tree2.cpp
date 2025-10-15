#include "pch.h"
#include "Tree2.h"

Tree2::Tree2(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Tree2::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto tree = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	tree->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Tree2"));
	sprite->SetParallaxFactor(0.98f);
	tree->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return tree;
}
