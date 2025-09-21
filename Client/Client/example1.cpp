#include "pch.h"
#include "example1.h"

#pragma region Misc
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#pragma endregion

example1::example1(const string& name) : Super(name)
{
}

void example1::Update()
{
	Super::Update();

	auto transform = _owner.lock()->GetTransform(); // Transform ��������
	if (!transform) return;

	glm::vec3 pos = transform->GetPosition();
	float moveSpeed = 500.0f * TIME.deltaTime;

	if (INPUT.GetKey(Inputs::Key::W)) pos.y += moveSpeed;
	if (INPUT.GetKey(Inputs::Key::S)) pos.y -= moveSpeed;
	if (INPUT.GetKey(Inputs::Key::A)) pos.x -= moveSpeed;
	if (INPUT.GetKey(Inputs::Key::D)) pos.x += moveSpeed;

	transform->SetPosition(pos);
}
