#pragma once
#include "IResource.h"

class Shader;
class Camera;

class ITexture : public IResource
{
	using Super = IResource;

public:
	ITexture(const string& name, const string& filePath);
	virtual ~ITexture() = default;

public:
	virtual void Init() override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera);

public:
	uint32 GetWidth() const { return _width; }
	uint32 GetHeight() const { return _height; }
	glm::vec2 GetSize() const { return glm::vec2(_width, _height); }

protected:
	virtual void LoadTexture();
	void CreateRect();
	void UseTexture();
	void ClearTexture();

protected:
	GLuint _textureID;
	string _resourceFilePath;
	GLuint _vao, _ibo, _vbo;
	array<GLfloat, 20> _vertices;
	uint32 _width, _height;
};

