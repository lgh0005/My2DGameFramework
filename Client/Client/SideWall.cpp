#include "pch.h"
#include "SideWall.h"

SideWall::SideWall(const string& name) : Super(name)
{

}

shared_ptr<GameObject> SideWall::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto background = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	background->SetTransform(transform);

	auto sprite = make_shared<Sprite>(name, RESOURCE.GetResource<Texture>("SideWall"));
	background->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	auto collider = make_shared<BoxCollider>("WallCollider", glm::vec2(100.0f, 800.0f));
	COLLIDER.AddColliderComponent(collider);
	background->AddComponent(collider);

	scene->GetRenderPass("_textureRenderPass")->AddRenderable(sprite);

	return background;
}
