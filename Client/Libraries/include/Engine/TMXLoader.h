#pragma once

struct TileData 
{
    int gid;
    glm::vec2 position;
};

struct MapData 
{
    int mapWidth;
    int mapHeight;
    int tileWidth;
    int tileHeight;
    vector<TileData> tiles;
};

class TMXLoader
{
public:
    static MapData LoadTMX(const string& tmxPath);
};

