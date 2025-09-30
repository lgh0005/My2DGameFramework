#pragma once
#include "ITexture.h"

struct InstanceData
{
	glm::mat4 modelMatrix;
};

class ITextureInstance : public ITexture
{
	using Super = ITexture;

public:
	ITextureInstance(const string& name, const string& filePath);
	virtual ~ITextureInstance() override = default;

public:
	virtual void Awake() override;
	virtual void Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera) override;

public:
	void AddInstance(const glm::mat4& model);

protected:
	virtual void LoadTexture() override;

protected:
	vector<InstanceData> _instances;
	GLuint _instanceVBO;
};

