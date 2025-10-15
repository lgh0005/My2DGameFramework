#include "pch.h"
#include "ColliderDebuger.h"

ColliderDebuger::ColliderDebuger(const string& name) : Super(name)
{

}

shared_ptr<GameObject> ColliderDebuger::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto test = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	test->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("TEST"));
	test->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	scene->GetRenderPass("_debugRenderPass")->AddRenderable(sprite);

	return test;
}
