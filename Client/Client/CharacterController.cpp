#include "pch.h"
#include "CharacterController.h"

CharacterController::CharacterController(const string& name) : Super(name)
{
	_idleLeft = RESOURCE.GetResource<Flipbook>("Character_Idle_left");
	_idleRight = RESOURCE.GetResource<Flipbook>("Character_Idle_right");
	_walkLeft = RESOURCE.GetResource<Flipbook>("Character_Walk_left");
	_walkRight = RESOURCE.GetResource<Flipbook>("Character_Walk_right");
	_chararcterShader = RESOURCE.GetResource<Shader>("CharacterShader");
	_characterUniformSet = RESOURCE.GetResource<UniformSet>("CharacterUniforms");
}

void CharacterController::Init()
{
	auto self = GetSelf< CharacterController>();

	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr<GameObject>(_owner, owner) == false) return;

	_collider = static_pointer_cast<BoxCollider>(owner->GetComponent("PlayerCollider"));
	_collider->SetCollisionEnterCallback
	(
		[self](const shared_ptr<BoxCollider>& other) { self->OnCollisionEnter(other); }
	);
}

void CharacterController::Update()
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;

	auto transform = owner->GetTransform();
	auto flipbookPlayer = static_pointer_cast<FlipbookPlayer>(owner->GetRenderable("CharacterFlipbook"));
	auto pos = transform->GetPosition();

	/*if (INPUT.GetKey(Inputs::Key::D))
	{
		pos.x += _moveSpeed * TIME.deltaTime;
		flipbookPlayer->SetFlipbook(_walkRight);
		_lastDir = Direction::Right;
	}
	else if (INPUT.GetKey(Inputs::Key::A))
	{
		pos.x -= _moveSpeed * TIME.deltaTime;
		flipbookPlayer->SetFlipbook(_walkLeft);
		_lastDir = Direction::Left;
	}
	else
	{
		if (_lastDir == Direction::Right) flipbookPlayer->SetFlipbook(_idleRight);
		else flipbookPlayer->SetFlipbook(_idleLeft);
	}*/

	if (INPUT.GetKey(Inputs::Key::D))
	{
		pos.x += _moveSpeed * TIME.deltaTime;
		flipbookPlayer->SetFlipbook(_walkRight);
		_lastDir = Direction::Right;
	}
	else if (INPUT.GetKey(Inputs::Key::A))
	{
		pos.x -= _moveSpeed * TIME.deltaTime;
		flipbookPlayer->SetFlipbook(_walkRight); // �¿� ���� �ʿ� ����
		_lastDir = Direction::Left;
	}
	else
	{
		flipbookPlayer->SetFlipbook(_idleRight); // �׻� ������ Flipbook ���
	}

	// �¿� ���⿡ ���� ������ ����
	if (_characterUniformSet)
	{
		_characterUniformSet->Set("flip", _lastDir == Direction::Left);
		_characterUniformSet->Apply(_chararcterShader);

#pragma region DEBUG
		if (_characterUniformSet)
		{
			GLuint programID = _chararcterShader->GetShaderProgram(); // Shader Ŭ�������� ���α׷� ID�� �������� �Լ�
			GLint flipLoc = glGetUniformLocation(programID, "flip");
			GLint flipValue = 0;
			glGetUniformiv(programID, flipLoc, &flipValue);

			// �ܼ� ���
			std::cout << "[DEBUG] flip uniform: " << flipValue << std::endl;
		}
#pragma endregion
	}

	// just moving constraint 
	if (pos.x >= _moveXRange) pos.x = _moveXRange;

	transform->SetPosition(pos);
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

	// ������ �̵� �� ���� �浹
	if (_lastDir == Direction::Right)
	{
		float maxX = otherPos.x - otherHalf.x - playerHalf.x;
		if (playerPos.x > maxX)
			playerPos.x = maxX;
	}
	// ���� �̵� �� ���� �浹
	else if (_lastDir == Direction::Left)
	{
		float minX = otherPos.x + otherHalf.x + playerHalf.x;
		if (playerPos.x < minX)
			playerPos.x = minX;
	}

	transform->SetPosition(playerPos);
}
