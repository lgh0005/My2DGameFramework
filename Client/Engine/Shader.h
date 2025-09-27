#pragma once
#include "IResource.h"

#pragma region TEMPLATE_PROPERTIES
template<typename T> struct UniformSetter;
using UniformValue = variant<int, float, bool, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>;
#pragma endregion

class Shader : public IResource
{
	using Super = IResource;

public:
	Shader(const string& name, const string& vertexShaderFile, const string& fragmentShaderFile);
	virtual ~Shader() override;

public:
	virtual void Awake() override;

public:
	void Use() { glUseProgram(_shaderID); }
	void Unuse() { glUseProgram(0); }
	GLuint GetShaderProgram() { return _shaderID; }
	GLuint GetUniformLocation(const string& uniform);

#pragma region TEST
//TEST
public:
	void AddUniform(const string& uniform);
	void ApplyUniforms();

	template<typename T>
	void SetUniformValue(const string& name, const T& value)
	{
		_uniformMap[name] = value;
	}
#pragma endregion

private:
	void CompileShader();
	string ReadFile(const string& filePath);
	void AddShader(const string& shaderCode, GLenum shaderType);

	template<typename T>
	void SetUniform(const string& name, const T& value)
	{
		GLuint loc = GetUniformLocation(name);
		if (loc == -1) return;
		UniformSetter<T>::Set(loc, value);
	}

private:
	GLuint _shaderID;
	string _vertexShaderFileLocation;
	string _fragmentShaderFileLocation;
	unordered_map<string, GLuint> _uniformLocation;
	unordered_map<string, UniformValue> _uniformMap;
};

/*==================================//
//	Uniform Variable Type Functors  //
====================================*/
#pragma region UNIFORM_VARIABLE_TYPES

// float
template<> struct UniformSetter<float>
{
	static void Set(GLuint loc, float v) { glUniform1f(loc, v); }
};

// int
template<> struct UniformSetter<int>
{
	static void Set(GLuint loc, int v) { glUniform1i(loc, v); }
};

// unsigned int (sampler2D 등)
template<> struct UniformSetter<GLuint>
{
	static void Set(GLuint loc, GLuint v) { glUniform1i(loc, static_cast<int>(v)); }
};

// vec2
template<> struct UniformSetter<glm::vec2>
{
	static void Set(GLuint loc, const glm::vec2& v) { glUniform2fv(loc, 1, glm::value_ptr(v)); }
};

// vec3
template<> struct UniformSetter<glm::vec3>
{
	static void Set(GLuint loc, const glm::vec3& v) { glUniform3fv(loc, 1, glm::value_ptr(v)); }
};

// vec4
template<> struct UniformSetter<glm::vec4>
{
	static void Set(GLuint loc, const glm::vec4& v) { glUniform4fv(loc, 1, glm::value_ptr(v)); }
};

// mat2
template<> struct UniformSetter<glm::mat2>
{
	static void Set(GLuint loc, const glm::mat2& v) { glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
};

// mat3
template<> struct UniformSetter<glm::mat3>
{
	static void Set(GLuint loc, const glm::mat3& v) { glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
};

// mat4
template<> struct UniformSetter<glm::mat4>
{
	static void Set(GLuint loc, const glm::mat4& v) { glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(v)); }
};

// bool (GLSL에서 uniform bool은 int로 전달)
template<> struct UniformSetter<bool>
{
	static void Set(GLuint loc, bool v) { glUniform1i(loc, v ? 1 : 0); }
};
#pragma endregion