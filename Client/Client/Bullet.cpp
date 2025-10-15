#include "pch.h"
#include "Bullet.h"

#pragma region SCRIPT
#include "BulletController.h"
#pragma endregion

Bullet::Bullet(const string& name) : Super(name)
{

}

shared_ptr<GameObject> Bullet::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto bullet = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	bullet->SetTransform(transform);

	auto sprite = make_shared<Sprite>("BulletSprite", RESOURCE.GetResource<Texture>("BulletTexture"));
	bullet->AddRenderable(sprite);

	shared_ptr<BulletController> script = make_shared<BulletController>("BulletController");
	bullet->AddBehaviour(script);

	return bullet;
}
