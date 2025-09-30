#pragma once
#include "IResource.h"

class SpriteMesh : public IResource
{
	using Super = IResource;

public:
	SpriteMesh(const string& name, float width, float height);
	virtual ~SpriteMesh();

public:
	void Bind();
	void Draw();
	void DrawInstanced(const vector<glm::mat4>& matrices);

private:
	void CreateRect();

private:
	float _width;
	float _height;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ibo;
	GLuint _instancedVBO;
	vector<GLfloat> _vertices;
	vector<uint32> _indices;
};

