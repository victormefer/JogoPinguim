#include "Tile.h"

/* *************************************************
 *
 * Construtor TileSet
 *
 * ************************************************* */
TileSet::TileSet(int tileWidth, int tileHeight, const char* file)
{
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	try
	{
		tileSet = Sprite(file);

		rows = (int)( tileSet.GetHeight() / tileHeight );
		columns = (int)( tileSet.GetWidth() / tileWidth );
	}
	catch(std::exception& ex)
	{
		throw ex;
	}
}



/* *************************************************
 *
 * Construtor TileSet
 *
 * ************************************************* */
void TileSet::Render(unsigned index, float x, float y)
{
	if (index >= rows * columns)
		throw std::invalid_argument("Indice muito grande para numero de tiles");

	tileSet.SetClip( (index % columns) * tileWidth, (int)(index / columns) * tileHeight, tileWidth, tileHeight );
	tileSet.Render(x, y);
}

/* *************************************************
 *
 * Retornar largura do tile
 *
 * ************************************************* */
int TileSet::GetTileWidth() const
{
	return tileWidth;
}

/* *************************************************
 *
 * Retornar altura do tile
 *
 * ************************************************* */
int TileSet::GetTileHeight() const
{
	return tileHeight;
}



/* *************************************************
 *
 * Construtor TileMap
 *
 * ************************************************* */
TileMap::TileMap(const char* file, TileSet* tileSet)
{
	Load(file);
	this->tileSet = tileSet;
}


/* *************************************************
 *
 * Carregar Tile Map
 *
 * ************************************************* */
void TileMap::Load(const char* file)
{
	std::ifstream ifs;
	char comma;

	ifs.open(file, std::ifstream::in);

	if(!ifs.is_open())
	{
		std::string fileStr(file);
		throw ExcecaoArquivo("Erro na abertura do arquivo de tile map " + fileStr);
	}

	ifs >> mapWidth;
	ifs >> comma;
	ifs >> mapHeight;
	ifs >> comma;
	ifs >> mapDepth;
	ifs >> comma;

	int curValue;

	//std::cout << "Antes do loop" << std::endl;
	while(ifs.good())
	{
		ifs >> curValue;
		ifs >> comma;
		tileMatrix.emplace_back(curValue - 1);
	}

	ifs.close();
}


/* *************************************************
 *
 * Setar TileSet
 *
 * ************************************************* */
void TileMap::SetTileSet(TileSet* tileSet)
{
	this->tileSet = tileSet;
}


/* *************************************************
 *
 * Operador de acesso encapsulado à matriz
 *
 * ************************************************* */
int& TileMap::at(int x, int y, int z = 0)
{
	return tileMatrix[ y + x*mapWidth + z*mapWidth*mapHeight ];
}


/* *************************************************
 *
 * Renderizar uma camada
 *
 * ************************************************* */
void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0)
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (at(i, j, layer) >= 0)
				tileSet->Render( (unsigned)at(i, j, layer), (float)(j * tileSet->GetTileWidth() - cameraX * layer), (float)(i * tileSet->GetTileHeight() - cameraY * layer) );
		}
	}
}


/* *************************************************
 *
 * Renderizar todas as camadas
 *
 * ************************************************* */
void TileMap::Render(int cameraX = 0, int cameraY = 0)
{
	for (int i = 0; i < mapDepth; i++)
		RenderLayer(i, cameraX, cameraY);
}


/* *************************************************
 *
 * Retorna largura do TileMap
 *
 * ************************************************* */
int TileMap::GetWidth() const
{
	return mapWidth;
}


/* *************************************************
 *
 * Retorna altura do TileMap
 *
 * ************************************************* */
int TileMap::GetHeight() const
{
	return mapHeight;
}


/* *************************************************
 *
 * Retorna numero de camadas do TileMap
 *
 * ************************************************* */
int TileMap::GetDepth() const
{
	return mapDepth;
}