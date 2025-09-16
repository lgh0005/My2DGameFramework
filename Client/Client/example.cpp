#include "pch.h"
#include "example.h"

#pragma region Misc
#include "Engine/GameObject.h"
#include "Engine/Transform.h"
#pragma endregion

example::example(const string& name) : Super(name)
{
}

example::~example()
{
}

void example::Update()
{
    Super::Update();

	auto transform = _owner.lock()->GetTransform(); // Transform 가져오기
	if (!transform) return;

	glm::vec3 pos = transform->GetPosition();
	float moveSpeed = 500.0f * TIME.deltaTime;

    if (INPUT.GetKey(Inputs::Key::W)) pos.y += moveSpeed;
    if (INPUT.GetKey(Inputs::Key::S)) pos.y -= moveSpeed;
    if (INPUT.GetKey(Inputs::Key::A)) pos.x -= moveSpeed;
    if (INPUT.GetKey(Inputs::Key::D)) pos.x += moveSpeed;

    transform->SetPosition(pos);
}