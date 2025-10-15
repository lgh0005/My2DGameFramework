#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Enemy::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return nullptr;

	auto enemy = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	enemy->SetTransform(transform);

	auto flipbook = RESOURCE.GetResource<Flipbook>("_normal_idle_r");
	shared_ptr<Flipbook> flipbookCopy = make_shared<Flipbook>(*flipbook);

	auto flipbookPlayer = make_shared<FlipbookPlayer>("EnemyFlipbook", flipbookCopy);
	enemy->AddRenderable(static_pointer_cast<IRenderable>(flipbookPlayer));

	scene->GetRenderPass("_enemyRenderPass")->AddRenderable(flipbookPlayer);

	return enemy;
}
