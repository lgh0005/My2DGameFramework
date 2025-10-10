#include "pch.h"
#include "CharacterController.h"

CharacterController::CharacterController(const string& name) : Super(name)
{
	_idleLeft = RESOURCE.GetResource<Flipbook>("Character_Idle_left");
	_idleRight = RESOURCE.GetResource<Flipbook>("Character_Idle_right");
	_walkLeft = RESOURCE.GetResource<Flipbook>("Character_Walk_left");
	_walkRight = RESOURCE.GetResource<Flipbook>("Character_Walk_right");
}

void CharacterController::Update()
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	auto transform = owner->GetTransform();
	auto flipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("CharacterFlipbook"));
	auto pos = transform->GetPosition();

	if (INPUT.GetKey(Inputs::Key::Right))
	{
		pos.x += _moveSpeed * TIME.deltaTime;
		flipbookPlayer->SetFlipbook(_walkRight);
		_lastDir = Direction::Right;
	}
	else if (INPUT.GetKey(Inputs::Key::Left))
	{
		pos.x -= _moveSpeed * TIME.deltaTime;
		flipbookPlayer->SetFlipbook(_walkLeft);
		_lastDir = Direction::Left;
	}
	else
	{
		if (_lastDir == Direction::Right) flipbookPlayer->SetFlipbook(_idleRight);
		else flipbookPlayer->SetFlipbook(_idleLeft);
	}

	transform->SetPosition(pos);
}

