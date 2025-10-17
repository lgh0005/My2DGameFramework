#include "pch.h"
#include "FlipbookPlayer.h"
#include "GameObject.h"
#include "Flipbook.h"
#include "Shader.h"

FlipbookPlayer::FlipbookPlayer(const string& name, shared_ptr<Flipbook> flipbook)
	: Super(name), _flipbook(flipbook)
{

}

void FlipbookPlayer::Awake(const shared_ptr<GameObject>& owner)
{
	Super::Awake(owner);
	_flipbook->Init();
}

void FlipbookPlayer::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;
	if (owner->IsActive() == false) return;

	_flipbook->Render(shader, model, camera);
}

void FlipbookPlayer::Update()
{
	Super::Update();
	_flipbook->Update();
}

