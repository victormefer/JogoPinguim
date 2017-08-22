#ifndef TILE_H
#define TILE_H

#include "Excecoes.h"
#include "Sprite.h"
#include "Game.h"
#include <fstream>
#include <vector>

class TileSet
{
public:
	TileSet(int tileWidth, int tileHeight, const char* file);

	void Render(unsigned index, float x, float y);
	int GetTileWidth() const;
	int GetTileHeight() const;

private:
	Sprite tileSet;
	int rows;
	int columns;

	int tileWidth;
	int tileHeight;

};


class TileMap
{
public:
	TileMap(const char* file, TileSet* tileSet);

	void Load(const char* file);
	void SetTileSet(TileSet* tileSet);

	int& at(int x, int y, int z);

	void Render(int cameraX, int cameraY);
	void RenderLayer(int layer, int cameraX, int cameraY);

	int GetWidth() const;
	int GetHeight() const;
	int GetDepth() const;

private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;

};


#endif // TILE_H