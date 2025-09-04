#pragma once
#include "IResource.h"

class Shader : public IResource
{
	using Super = IResource;

public:
	Shader(const string& name, const string& vertexShaderFile, const string& fragmentShaderFile);
	virtual ~Shader() override;

public:
	virtual void Init() override;

public:
	void Use() { glUseProgram(_shaderID); }
	void Unuse() { glUseProgram(0); }
	GLuint GetShaderProgram() { return _shaderID; }
	GLuint GetUniformLocation(const string& uniform);

public:
	void AddUniforms(const vector<const char*>& uniforms);

public:
	void SetView(glm::mat4& view) { _view = view; }
	glm::mat4& GetView() { return _view; }
	void SetProjection(glm::mat4& projection) { _projection = projection; }
	glm::mat4& GetProjection() { return _projection; }

private:
	void AddUniform(const char* uniform);
	void CompileShader();
	string ReadFile(const string& filePath);
	void AddShader(const string& shaderCode, GLenum shaderType);

private:
	GLuint _shaderID;
	string _vertexShaderFileLocation;
	string _fragmentShaderFileLocation;
	unordered_map<string, GLuint> _uniformLocation;
	
	glm::mat4 _view;
	glm::mat4 _projection;
};