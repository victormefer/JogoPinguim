#include "Resources.h"


std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

/* ************************************************************
 *
 * Carregar textura se não está carregada
 *
 *************************************************************/
std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
	auto it = imageTable.find(file);

	if ( it == imageTable.end() )
	{
		// Nao achou imagem na tabela, carrega
		SDL_Texture* texture = IMG_LoadTexture ( Game::GetInstance().GetRenderer() , file.c_str() );
		if (texture == NULL)
		{
			std::string imgError = IMG_GetError();
			throw ExcecaoTextura( "Erro no carregamento da textura " + file + '\n' + imgError );
		}
		std::shared_ptr<SDL_Texture> ptr (texture, deleteTexture);
		imageTable.emplace(file, ptr);
		return ptr;
	}
	else
	{
		// Imagem ja está carregada, retorna ponteiro para ela
		std::shared_ptr<SDL_Texture> texture = it->second;
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
		if (it->second.unique())
			imageTable.erase(it);
	}
	//imageTable.clear();
}


/* ************************************************************
 *
 * Carregar musica se não está carregada
 *
 *************************************************************/
std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file)
{
	auto it = musicTable.find(file);

	if ( it == musicTable.end() )
	{
		// Nao achou musica na tabela, carrega
		Mix_Music* music = Mix_LoadMUS (file.c_str());
		if (music == NULL)
		{
			std::string musError = Mix_GetError();
			throw ExcecaoTextura( "Erro no carregamento da musica " + file + '\n' + musError );
		}
		std::shared_ptr<Mix_Music> ptr (music, deleteMusic);
		musicTable.emplace(file, ptr);
		return ptr;
	}
	else
	{
		// Musica ja está carregada, retorna ponteiro para ela
		std::shared_ptr<Mix_Music> music = it->second;
		return music;
	}
}




/* ************************************************************
 *
 * Destruir todas as musicas
 *
 *************************************************************/
void Resources::ClearMusic()
{
	for ( auto it = musicTable.begin() ; it != musicTable.end(); ++it )
	{
		if (it->second.unique())
			musicTable.erase(it);
	}
	//musicTable.clear();
}


/* ************************************************************
 *
 * Carregar som se não está carregada
 *
 *************************************************************/
std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file)
{
	auto it = soundTable.find(file);

	if ( it == soundTable.end() )
	{
		// Nao achou musica na tabela, carrega
		Mix_Chunk* chunk = Mix_LoadWAV (file.c_str());
		if (chunk == NULL)
		{
			std::string musError = Mix_GetError();
			throw ExcecaoTextura( "Erro no carregamento do som " + file + '\n' + musError );
		}
		std::shared_ptr<Mix_Chunk> ptr (chunk, deleteSound);
		soundTable.emplace(file, ptr);
		return ptr;
	}
	else
	{
		// Musica ja está carregada, retorna ponteiro para ela
		std::shared_ptr<Mix_Chunk> chunk = it->second;
		return chunk;
	}
}




/* ************************************************************
 *
 * Destruir todos os sons
 *
 *************************************************************/
void Resources::ClearSound()
{
	for ( auto it = soundTable.begin() ; it != soundTable.end(); ++it )
	{
		if (it->second.unique())
			soundTable.erase(it);
	}
	//soundTable.clear();
}


/* ************************************************************
 *
 * Carregar som se não está carregada
 *
 *************************************************************/
std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize)
{    
	std::ostringstream ss;
	ss << fontSize;
	auto it = fontTable.find(file + ss.str());

	if ( it == fontTable.end() )
	{
		// Nao achou musica na tabela, carrega
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
		if (font == NULL)
		{
			std::string error = TTF_GetError();
			throw ExcecaoTextura( "Erro no carregamento da fonte " + file + '\n' + error );
		}
		std::shared_ptr<TTF_Font> ptr (font, deleteFont);
		fontTable.emplace(file + ss.str(), ptr);
		return ptr;
	}
	else
	{
		// Musica ja está carregada, retorna ponteiro para ela
		std::shared_ptr<TTF_Font> font = it->second;
		return font;
	}
}




/* ************************************************************
 *
 * Destruir todos os sons
 *
 *************************************************************/
void Resources::ClearFonts()
{
	for ( auto it = fontTable.begin() ; it != fontTable.end(); ++it )
	{
		if (it->second.unique())
			fontTable.erase(it);
	}
	//fontTable.clear();
}