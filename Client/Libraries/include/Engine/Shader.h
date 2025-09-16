#pragma once
#include "IResource.h"

class Shader : public IResource
{
	using Super = IResource;

public:
	Shader(const string& name, const string& vertexShaderFile, const string& fragmentShaderFile, const vector<const char*>& uniforms);
	virtual ~Shader() override;

public:
	virtual void Awake() override;

public:
	void Use() { glUseProgram(_shaderID); }
	void Unuse() { glUseProgram(0); }
	GLuint GetShaderProgram() { return _shaderID; }
	GLuint GetUniformLocation(const string& uniform);

public:
	void SetBool(const string& name, bool value) { glUniform1i(GetUniformLocation(name), value ? 1 : 0); }
	void SetInt(const string& name, int value) { glUniform1i(GetUniformLocation(name), value); }
	void SetFloat(const string& name, float value) { glUniform1f(GetUniformLocation(name), value); }
	void SetVec2(const string& name, const glm::vec2& value) { glUniform2fv(GetUniformLocation(name), 1, &value[0]); }
	void SetVec3(const string& name, const glm::vec3& value) { glUniform2fv(GetUniformLocation(name), 1, &value[0]); }
	void SetVec4(const string& name, const glm::vec4& value) { glUniform2fv(GetUniformLocation(name), 1, &value[0]); }
	void SetMat4(const string& name, const glm::mat4& value) { glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]); }

private:
	void AddUniforms(const vector<const char*>& uniforms);
	void CompileShader();
	string ReadFile(const string& filePath);
	void AddShader(const string& shaderCode, GLenum shaderType);

private:
	GLuint _shaderID;
	string _vertexShaderFileLocation;
	string _fragmentShaderFileLocation;
	vector<const char*> _uniformVariables;
	unordered_map<string, GLuint> _uniformLocation;
};