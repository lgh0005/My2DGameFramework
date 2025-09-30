#pragma once
#include "IResource.h"

class ITexture;
class Shader;

class Material : public IResource
{
	using Super = IResource;

public:
	Material(const string& name, const shared_ptr<ITexture>& texture, const shared_ptr<Shader>& shader);
	virtual ~Material() override = default;

public:
	void Bind();

public:
	shared_ptr<ITexture> GetTexture() { return _texture; }
	shared_ptr<Shader> GetShader() { return _shader; }

private:
	shared_ptr<ITexture> _texture;
	shared_ptr<Shader> _shader;
};

