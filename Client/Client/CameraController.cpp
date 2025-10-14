#include "pch.h"
#include "CameraController.h"

CameraController::CameraController(const string& name) : Super(name)
{

}

void CameraController::Update()
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	auto transform = owner->GetTransform();
	auto pos = transform->GetPosition();

	if (INPUT.GetKey(Inputs::Key::D))
	{
		pos.x += _moveSpeed * TIME.deltaTime;
	}
	else if (INPUT.GetKey(Inputs::Key::A))
	{
		pos.x -= _moveSpeed * TIME.deltaTime;
	}

	pos.x = clamp(pos.x, _minMoveDistance, _maxMoveDistance);

	transform->SetPosition(pos);
}
