#pragma once
#include "IResource.h"

class Mesh : public IResource
{
	using Super = IResource;

public:
	Mesh(const string& name, float width, float height);
	virtual ~Mesh();

public:
	void Bind();
	void CreateRect();
	GLuint GetVAO() { return _vao; }

private:
	float _width;
	float _height;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ibo;
	vector<GLfloat> _vertices;
	vector<uint32> _indices;
};

