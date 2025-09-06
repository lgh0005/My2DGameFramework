#include "pch.h"
#include "Camera.h"
#include "ITexture.h"
#include "Shader.h"
#include "Camera.h"

ITexture::ITexture(const string& name, const string& filePath)
	: Super(name), _resourceFilePath(filePath)
{

}

ITexture::~ITexture()
{
}


void ITexture::Init()
{
	LoadTexture();
	CreateRect();
}

void ITexture::Render(shared_ptr<Shader> shader, glm::mat4 model, shared_ptr<Camera> camera)
{
	shader->Use();

	// Use shader program and bind buffers
	glUseProgram(shader->GetShaderProgram());
	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

	// Transfrom 관련된 것들
	glUniformMatrix4fv(shader->GetUniformLocation(Uniforms::UNIFORM_MODEL), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(shader->GetUniformLocation(Uniforms::UNIFORM_VIEW), 1, GL_FALSE, glm::value_ptr(camera->GetView()));
	glUniformMatrix4fv(shader->GetUniformLocation(Uniforms::UNIFORM_PROJECTION), 1, GL_FALSE, glm::value_ptr(camera->GetProjection()));

	// Bind texture
	UseTexture();
	glUniform1i(shader->GetUniformLocation(Uniforms::UNIFORM_TEXTURE), 0);

	// Draw call
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader->Unuse();
}

void ITexture::LoadTexture()
{
	// Create SDL_Surface
	SDL_Surface* surface = IMG_Load(_resourceFilePath.c_str());
	LOGGER.DebugAssert(surface == nullptr, format("Failed to load image : {}", _resourceFilePath), nullptr);

	// RGBA 포맷 강제 변환 (OpenGL 호환)
	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(surface);
	LOGGER.DebugAssert(formattedSurface == nullptr, format("Failed to convert surface : {}", _resourceFilePath), nullptr);

	// Get surface width and height
	_width = formattedSurface->w;
	_height = formattedSurface->h;

	// Create OpenGL texture
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// SDL surface → OpenGL 텍스처 업로드
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(formattedSurface);
}

void ITexture::CreateRect()
{
	unsigned int indices[] = { 0, 1, 2, 2, 1, 3 };

	float halfW = _width / 2.0f;
	float halfH = _height / 2.0f;

	GLfloat vertices[] =
	{
		-halfW, -halfH, 0.0f,   0.0f, 1.0f, // 좌하단
		-halfW,  halfH, 0.0f,   0.0f, 0.0f, // 좌상단
		 halfW, -halfH, 0.0f,   1.0f, 1.0f, // 우하단
		 halfW,  halfH, 0.0f,   1.0f, 0.0f  // 우상단
	};

	// vao
	glGenVertexArrays(1, &_vao); // Generate vao id.
	glBindVertexArray(_vao);	 // Bind the vao with that id.

	// ibo
	glGenBuffers(1, &_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vbo
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 정점 속성 중 1 : 위치
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0);
	glEnableVertexAttribArray(0);

	// 정점 속성 중 2 : UV 좌표
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	// 언바인딩 : 정보를 확정
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ITexture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void ITexture::ClearTexture()
{
	glDeleteTextures(1, &_textureID);
}

