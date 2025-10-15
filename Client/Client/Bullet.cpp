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
	// TOOD : ó�� ��ȯ�� �� �ٷ� �������� ���� �ʱ� ���� ��ġ�� �ʿ�

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
