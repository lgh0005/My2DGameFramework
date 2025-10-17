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
	if (pos.x >= _maxMoveXRange) pos.x = _maxMoveXRange;
	if (pos.x <= _minMoveXRange) pos.x = _minMoveXRange;

	_ownerTransform->SetPosition(pos);
}

