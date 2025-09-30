#pragma once
#include "IComponent.h"

class SpriteMesh;
class Material;

class SpriteRenderer : public IComponent
{
	using Super = IComponent;

public:
	SpriteRenderer(const string& name, const shared_ptr<SpriteMesh>& mesh, const shared_ptr<Material>& material);
	virtual ~SpriteRenderer() override = default;

private:
	shared_ptr<SpriteMesh> _mesh;
	shared_ptr<Material> _material;
};

