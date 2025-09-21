#include "pch.h"
#include "FlipbookPlayer.h"
#include "Flipbook.h"
#include "Shader.h"

FlipbookPlayer::FlipbookPlayer(const string& name, shared_ptr<Camera> camera,
	shared_ptr<Flipbook> flipbook, shared_ptr<Shader> shader)
	: Super(name, camera), _flipbook(flipbook), _shader(shader)
{
}

void FlipbookPlayer::Awake(shared_ptr<GameObject> owner)
{
	Super::Awake(owner);
	_flipbook->Awake();
	_shader->Awake();
}

void FlipbookPlayer::Render()
{
	_flipbook->Render(_shader, _model, _camera);
}

void FlipbookPlayer::Update()
{
	Super::Update();
	_flipbook->Update();
}

