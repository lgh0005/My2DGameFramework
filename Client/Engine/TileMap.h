#pragma once
#include "ITexture.h"

class TileMap : public ITexture
{
	using Super = ITexture;

public:
	TileMap(const string& name, const string& filePath);
	virtual ~TileMap() override = default;

public:
	virtual void Awake() override;
	virtual void Render(shared_ptr<Shader> shader, glm::mat4 model, shared_ptr<Camera> camera) override;

private:
	// TODO : Tile size etc.
};

