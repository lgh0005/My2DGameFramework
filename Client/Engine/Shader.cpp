#include "pch.h"
#include "Shader.h"

Shader::Shader(const string& name) : Super(name)
{
}

Shader::~Shader()
{
}

void Shader::Init()
{
	// Create shader program
	_shaderID = glCreateProgram();
	LOGGER.DebugAssert(_shaderID == 0, "Failed to create shader program.", glGetError);
}

string Shader::ReadFile(const string& filePath)
{
	// Open shader file
	string content;
	ifstream fileStream(filePath.c_str(), ios::in);
	LOGGER.DebugAssert(!fileStream.is_open(), format("Failed to open file {}", filePath), nullptr);

	// Read shader file
	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}

	// Return shader code
	fileStream.close();
	return content;
}

void Shader::AddShader(const string& shaderCode, GLenum shaderType)
{
	// Create Shader
	GLuint shader = glCreateShader(shaderType);

	// Compile Shader
	const GLchar* code = shaderCode.c_str();
	GLint codeLen = (GLint)shaderCode.size();
	glShaderSource(shader, 1, &code, &codeLen);
	glCompileShader(shader);

	// Check compile error
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	LOGGER.DebugAssert
	(
		success == GL_FALSE,
		"Failed to compile shader.",
		[&]() -> string
		{
			GLint logLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			vector<char> infoLog(logLength);
			glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());
			return string(infoLog.begin(), infoLog.end());
		}
	);

	// Attach shader to shader program.
	glAttachShader(_shaderID, shader);
}

void Shader::CompileShader(const string& shaderCode, uint32 glShaderType)
{
	// Add shader and compile it.
	AddShader(shaderCode, glShaderType);

	GLint success = 0;

	// Link shader program
	glLinkProgram(_shaderID);
	glGetProgramiv(_shaderID, GL_LINK_STATUS, &success);
	LOGGER.DebugAssert
	(
		success == GL_FALSE,
		"Failed to link shader program.",
		[&]() -> string
		{
			GLint logLength = 0;
			glGetProgramiv(_shaderID, GL_INFO_LOG_LENGTH, &logLength);
			vector<char> infoLog(logLength);
			glGetProgramInfoLog(_shaderID, logLength, nullptr, infoLog.data());
			return string(infoLog.begin(), infoLog.end());
		}
	);

	// Validate shader program.
	glValidateProgram(_shaderID);
	glGetProgramiv(_shaderID, GL_VALIDATE_STATUS, &success);
	LOGGER.DebugAssert
	(
		success == GL_FALSE,
		"Failed to validate shader program.",
		[&]() -> string
		{
			GLint logLength = 0;
			glGetProgramiv(_shaderID, GL_INFO_LOG_LENGTH, &logLength);
			vector<char> infoLog(logLength);
			glGetProgramInfoLog(_shaderID, logLength, nullptr, infoLog.data());
			return string(infoLog.begin(), infoLog.end());
		}
	);

	// TODO: Implement logic to register uniform variables here later.
}
