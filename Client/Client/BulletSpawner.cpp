#include "pch.h"
#include "BulletSpawner.h"

#pragma region BULLET
#include "Bullet.h"
#include "BulletController.h"
#pragma endregion

BulletSpawner::BulletSpawner(const string& name) : Super(name)
{

}

void BulletSpawner::Init()
{
	_bulletPrefab = static_pointer_cast<Bullet>(RESOURCE.GetResource<Prefab>("Bullet"));
}

void BulletSpawner::SpawnBullet(const glm::vec3& position, Direction dir)
{
	shared_ptr<Scene> scene;
	if (Utils::IsValidPtr(_currentScene, scene) == false) return;
	shared_ptr<GameObject> bullet = _bulletPrefab->Instantiate("Bullet", position);
	auto bulletController = static_pointer_cast<BulletController>(bullet->GetBehaviour("BulletController"));
	bulletController->SetDirection(dir);
	scene->AddGameObject(bullet);
}
