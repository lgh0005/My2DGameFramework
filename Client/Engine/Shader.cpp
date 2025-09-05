#include "pch.h"
#include "Shader.h"

Shader::Shader(const string& name, const string& vertexShaderFile, const string& fragmentShaderFile, const vector<const char*>& uniforms)
	: Super(name), 
	_vertexShaderFileLocation(vertexShaderFile), 
	_fragmentShaderFileLocation(fragmentShaderFile), 
	_uniformVariables(uniforms)
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

	// Set default view, projection matrix
	_view = glm::mat4(1.0);
	_projection = glm::ortho
	(
		-(float)WindowConfig::GWinSizeX / 2.0f, (float)WindowConfig::GWinSizeX / 2.0f,  // left, right
		-(float)WindowConfig::GWinSizeY / 2.0f, (float)WindowConfig::GWinSizeY / 2.0f,  // bottom, top
		-1.0f, 1.0f
	);

	// Compile shader
	CompileShader();
}

GLuint Shader::GetUniformLocation(const string& uniform)
{
	auto it = _uniformLocation.find(uniform);
	if (it != _uniformLocation.end()) return it->second;
	return -1;
}

void Shader::AddUniforms(const vector<const char*>& uniforms)
{
	for (auto uniform : uniforms)
		_uniformLocation[uniform] = glGetUniformLocation(_shaderID, uniform);
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

void Shader::CompileShader()
{
	// Add shader and compile it.
	// TODO : 하드 코딩된 부분 수정할 필요 있음.
	AddShader(ReadFile(_vertexShaderFileLocation), GL_VERTEX_SHADER);
	AddShader(ReadFile(_fragmentShaderFileLocation), GL_FRAGMENT_SHADER);

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

	// Add uniform variables
	AddUniforms(_uniformVariables);
}
