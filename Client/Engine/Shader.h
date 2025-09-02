#pragma once
#include "IResource.h"

class Shader : public IResource
{
	using Super = IResource;

public:
	Shader(const string& name);
	virtual ~Shader() override;

public:
	virtual void Init() override;
	
public:
	string ReadFile(const string& filePath);
	void AddShader(const string& shaderCode, GLenum shaderType);
	void CompileShader(const string& shaderCode, uint32 glShaderType);

private:
	GLuint _shaderID;
	// TODO: Add necessary uniform variables
	// TODO : 조명이나 특정 텍스쳐를 입혀야 하는 경우 고려
};