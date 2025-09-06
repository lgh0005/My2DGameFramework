#pragma once
#include "IResource.h"

class Shader;
class Camera;

class ITexture : public IResource
{
	using Super = IResource;

public:
	ITexture(const string& name, const string& filePath);
	virtual ~ITexture();

public:
	virtual void Init() override;

#pragma region TEST
	virtual void Render(shared_ptr<Shader> shader, glm::mat4 model, shared_ptr<Camera> camera);
#pragma endregion

public:
	uint32 GetWidth() { return _width; }
	uint32 GetHeight() { return _height; }

protected:
	virtual void LoadTexture();
	void CreateRect();
	void UseTexture();
	void ClearTexture();

protected:
	GLuint _textureID;
	string _resourceFilePath;
	GLuint _vao, _ibo, _vbo;
	uint32 _width, _height;
};

