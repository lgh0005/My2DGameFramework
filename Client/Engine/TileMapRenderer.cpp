#include "pch.h"
#include "TileMapRenderer.h"
#include "Camera.h"
#include "TileMap.h"

TileMapRenderer::TileMapRenderer(const string& name, shared_ptr<TileMap> tileMap)
	: Super(name), _tileMap(tileMap)
{

}

void TileMapRenderer::Init()
{
	Super::Init();

}
