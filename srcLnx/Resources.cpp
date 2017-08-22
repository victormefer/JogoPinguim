#include "Resources.h"


std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;

/* ************************************************************
 *
 * Carregar textura se não está carregada
 *
 *************************************************************/
SDL_Texture* Resources::GetImage(const char* file)
{
	std::unordered_map<std::string, SDL_Texture*>::const_iterator it = imageTable.find(file);

	if ( it == imageTable.end() )
	{
		// Nao achou imagem na tabela, carrega
		SDL_Texture* texture = IMG_LoadTexture ( Game::GetInstance().GetRenderer() , file );
		if (texture == NULL)
		{
			std::string imgError = IMG_GetError();
			std::string fileStr(file);
			throw ExcecaoTextura( "Erro no carregamento da textura " + fileStr + '\n' + imgError );
		}
		imageTable.emplace(file, texture);
		return texture;
	}
	else
	{
		// Imagem ja está carregada, retorna ponteiro para ela
		SDL_Texture* texture = it->second;
		return texture;
	}
}


/* ************************************************************
 *
 * Destruir todas as texturas
 *
 *************************************************************/
void Resources::ClearImages()
{
	for ( auto it = imageTable.begin() ; it != imageTable.end(); ++it )
	{
		SDL_DestroyTexture(it->second);
	}
	imageTable.clear();
}