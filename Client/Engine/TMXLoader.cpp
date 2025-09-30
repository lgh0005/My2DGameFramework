#include "pch.h"
#include "TMXLoader.h"

MapData TMXLoader::LoadTMX(const string& tmxPath)
{
	MapData mapData;

	XMLDocument doc;
	if (doc.LoadFile(tmxPath.c_str()) != XML_SUCCESS) 
	{
		cout << "Failed to load TMX: " << tmxPath << endl;
		return mapData;
	}

	auto map = doc.FirstChildElement("map");
	mapData.mapWidth = atoi(map->Attribute("width"));
	mapData.mapHeight = atoi(map->Attribute("height"));
	mapData.tileWidth = atoi(map->Attribute("tilewidth"));
	mapData.tileHeight = atoi(map->Attribute("tileheight"));

	auto layer = map->FirstChildElement("layer");
	auto data = layer->FirstChildElement("data");
	const char* csvData = data->GetText();

	stringstream ss(csvData);
	string tileStr;

	int x = 0, y = 0;
	while (getline(ss, tileStr, ','))
	{
		int gid = stoi(tileStr);
		if (gid != 0) mapData.tiles.push_back({ gid, glm::vec2(x * mapData.tileWidth, -y * mapData.tileHeight) });
		
		x++;
		
		if (x >= mapData.mapWidth) 
		{
			x = 0;
			y++;
		}
	}

	return mapData;
}
