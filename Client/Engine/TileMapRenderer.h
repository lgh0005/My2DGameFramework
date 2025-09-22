#pragma once
#include "IRenderable.h"

class Camera;
class TileMap;

class TileMapRenderer : public IRenderable
{
	using Super = IRenderable;

public:
	TileMapRenderer(const string& name, shared_ptr<Camera> camera, shared_ptr<TileMap> tileMap);
	virtual ~TileMapRenderer() override = default;

public:
	virtual void Init() override;

private:
	shared_ptr<TileMap> _tileMap;
};

