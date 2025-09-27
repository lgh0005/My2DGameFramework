#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const string& name, const string& filePath) : Super(name, filePath)
{

}

void TileMap::Awake()
{
	// TODO
}

void TileMap::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	// TODO
}
