#include "Text.h"


/* ************************************************************
 *
 * Construtor
 *
 *************************************************************/
Text::Text(	std::string fontFile,
			int fontSize,
			TextStyle style,
			std::string text,
			SDL_Color color,
			int x, int y)
{
	this->fontSize = fontSize;
	font = Resources::GetFont(fontFile, fontSize);
	this->style = style;
	this->text = text;
	this->color = color;
	box.x = x;
	box.y = y;
	texture = NULL;
	RemakeTexture();
}



/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Text::~Text()
{
	if (texture != NULL)
		SDL_DestroyTexture(texture);
}



/* ************************************************************
 *
 * Render
 *
 *************************************************************/
void Text::Render(int cameraX, int cameraY)
{
	SDL_Rect srcRect, dstRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = box.w;
	srcRect.h = box.h;

	dstRect.x = box.x - cameraX;
	dstRect.y = box.y - cameraY;
	dstRect.w = box.w;
	dstRect.h = box.h;

	//std::cout << scaleX << ", " << scaleY << std::endl;

	SDL_RenderCopy ( Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect);
}




/* ************************************************************
 *
 * Setar posicao
 *
 *************************************************************/
void Text::SetPos(int x, int y, bool centerX, bool centerY)
{
	box.x = centerX ? x - box.w / 2 : x;
	box.y = centerY ? y - box.h / 2 : y;
}



/* ************************************************************
 *
 * Sets
 *
 *************************************************************/
void Text::SetText(std::string text)
{
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
	this->fontSize = fontSize;
	RemakeTexture();
}



/* ************************************************************
 *
 * Recriar textura
 *
 *************************************************************/
void Text::RemakeTexture()
{
	int w, h;
	SDL_Surface* surface;
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;

	switch(this->style)
	{
		case SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case SHADED:
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), this->color, black);
			break;
		case BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	box.w = w;
	box.h = h;
}