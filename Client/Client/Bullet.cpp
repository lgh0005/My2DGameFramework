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
	// TOOD : 처음 소환할 때 바로 렌더링이 되지 않기 위한 조치가 필요

	auto bullet = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	cout << transform->GetPosition().x << " " << transform->GetPosition().y << endl;

	transform->Awake(bullet);
	transform->UpdateModelMatrix();

	bullet->SetTransform(transform);

	shared_ptr<BulletController> script = make_shared<BulletController>("BulletController");
	bullet->AddBehaviour(script);

	//if (_renderPass == nullptr) return nullptr;
	//_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return bullet;
}
