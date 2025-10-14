#include "pch.h"
#include "CharacterController.h"

CharacterController::CharacterController(const string& name) : Super(name)
{
	_idleRight = RESOURCE.GetResource<Flipbook>("Character_Idle_right");
	_walkRight = RESOURCE.GetResource<Flipbook>("Character_Walk_right");
	_chararcterShader = RESOURCE.GetResource<Shader>("CharacterShader");
	_characterUniformSet = RESOURCE.GetResource<UniformSet>("CharacterUniforms");
}

void CharacterController::Init()
{
	auto self = GetSelf<CharacterController>();

	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	// Get transform
	_ownerTransform = owner->GetTransform();

	// Get collider
	_collider = static_pointer_cast<BoxCollider>(owner->GetComponent("PlayerCollider"));
	_collider->SetCollisionEnterCallback
	(
		[self](const shared_ptr<BoxCollider>& other) { self->OnCollisionEnter(other); }
	);

	// Get FlipbookPlayer
	_CharacterFlipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("CharacterFlipbook"));
}

void CharacterController::Update()
{
	auto pos = _ownerTransform->GetPosition();

	if (INPUT.GetKey(Inputs::Key::D))
	{
		pos.x += _moveSpeed * TIME.deltaTime;
		_CharacterFlipbookPlayer->SetFlipbook(_walkRight);
		_lastDir = Direction::Right;
	}
	else if (INPUT.GetKey(Inputs::Key::A))
	{
		pos.x -= _moveSpeed * TIME.deltaTime;
		_CharacterFlipbookPlayer->SetFlipbook(_walkRight);
		_lastDir = Direction::Left;
	}
	else
	{
		_CharacterFlipbookPlayer->SetFlipbook(_idleRight);
	}

	if (_characterUniformSet)
	{
		_characterUniformSet->Set("flip", _lastDir == Direction::Left);
		_characterUniformSet->Apply(_chararcterShader);
	}

	// just moving constraint 
	if (pos.x >= _moveXRange) pos.x = _moveXRange;

	_ownerTransform->SetPosition(pos);
}

void CharacterController::OnCollisionEnter(const shared_ptr<BoxCollider>& other)
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	shared_ptr<GameObject> otherOwner;
	if (Utils::IsValidPtr(other->GetOwner(), otherOwner) == false) return;

	auto transform = owner->GetTransform();
	auto playerPos = transform->GetPosition();
	glm::vec2 playerHalf = _collider->GetSize() * 0.5f;

	auto otherPos = otherOwner->GetTransform()->GetPosition();
	glm::vec2 otherHalf = other->GetSize() * 0.5f;

	// 오른쪽 이동 중 벽에 충돌
	if (_lastDir == Direction::Right)
	{
		float maxX = otherPos.x - otherHalf.x - playerHalf.x;
		if (playerPos.x > maxX)
			playerPos.x = maxX;
	}
	// 왼쪽 이동 중 벽에 충돌
	else if (_lastDir == Direction::Left)
	{
		float minX = otherPos.x + otherHalf.x + playerHalf.x;
		if (playerPos.x < minX)
			playerPos.x = minX;
	}

	transform->SetPosition(playerPos);
}
