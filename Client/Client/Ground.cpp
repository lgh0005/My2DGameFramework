#include "pch.h"
#include "Ground.h"

Ground::Ground(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Ground::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto ground = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	ground->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("Ground"));
	ground->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	auto collider = make_shared<BoxCollider>("GroundCollider", glm::vec2(800.0f, 100.0f));
	COLLIDER.AddColliderComponent(collider);
	ground->AddComponent(collider);

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return ground;
}
