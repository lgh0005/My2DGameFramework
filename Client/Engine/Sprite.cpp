#include "pch.h"
#include "Sprite.h"
#include "ITexture.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

#pragma region TEST
#include "Transform.h"
#include "GameObject.h"
#pragma endregion

Sprite::Sprite(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader)
	: Super(name), _texture(texture), _shader(shader)
{

}

Sprite::~Sprite()
{

}

void Sprite::Init(shared_ptr<GameObject> owner)
{
	Super::Init(owner);
	_shader->Init();
	_texture->Init();
}

void Sprite::Render(const shared_ptr<Camera>& camera)
{
	_texture->Render(_shader, _model, camera);
}

bool Sprite::IsMouseHovered(glm::vec2 mousePos)
{
	auto transform = _owner.lock()->GetTransform();
	glm::vec2 pos = glm::vec2(transform->GetPosition());
	glm::vec2 scale = glm::vec2(transform->GetScale());
	glm::vec2 size = glm::vec2(_texture->GetWidth(), _texture->GetHeight()) * scale;

	// Áß¾Ó ±âÁØ Rect
	glm::vec2 halfSize = size * 0.5f;
	glm::vec2 min = pos - halfSize;
	glm::vec2 max = pos + halfSize;

	return (mousePos.x >= min.x && mousePos.x <= max.x &&
		mousePos.y >= min.y && mousePos.y <= max.y);
}

