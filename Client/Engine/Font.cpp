#include "pch.h"
#include "Font.h"
#include "Shader.h"
#include "Camera.h"

Font::Font(const string& name, const string& filePath, const string& text, uint32 fontSize, SDL_Color color)
	: Super(name, filePath), _text(text), _fontSize(fontSize), _color(color)
{
}

Font::~Font()
{
}

void Font::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	// Use shader program and bind buffers
	glUseProgram(shader->GetShaderProgram());
	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

	// Uniforms
	shader->SetUniformValue(Uniforms::UNIFORM_MODEL, model);
	shader->SetUniformValue(Uniforms::UNIFORM_VIEW, camera->GetView());
	shader->SetUniformValue(Uniforms::UNIFORM_PROJECTION, camera->GetProjection());
	shader->SetUniformValue(Uniforms::UNIFORM_COLOR, glm::vec4(_color.r / 255.0f, _color.g / 255.0f, _color.b / 255.0f, _color.a / 255.0f));
	shader->SetUniformValue(Uniforms::UNIFORM_TEXTURE, 0);

	// Apply them at once
	shader->ApplyUniforms();

	// Bind texture
	UseTexture();
	glUniform1i(shader->GetUniformLocation(Uniforms::UNIFORM_TEXTURE), 0);

	// Draw call
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Font::LoadTexture()
{
	// Open font file
	TTF_Font* font = TTF_OpenFont(_resourceFilePath.c_str(), _fontSize);
	LOGGER.DebugAssert(font == nullptr, format("Failed to open font : {}", _resourceFilePath), nullptr);

	// Create SDL_Surface 
	SDL_Surface* fontSurface = TTF_RenderUTF8_Blended(font, _text.c_str(), _color);
	LOGGER.DebugAssert(fontSurface == nullptr, format("Failed to render text : {}", _resourceFilePath), nullptr);

	// 3. RGBA 포맷 강제 변환
	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(fontSurface, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(fontSurface);
	LOGGER.DebugAssert(formattedSurface == nullptr, format("Failed to convert font surface : {}", _resourceFilePath), nullptr);

	// Get surface width and height
	_width = formattedSurface->w;
	_height = formattedSurface->h;

	// Create OpenGL texture
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// SDL surface → OpenGL 텍스처 업로드
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(formattedSurface);
}
