#include "Sprite.h"


/* ************************************************************
 *
 * Construtores
 *
 *************************************************************/
Sprite::Sprite()
{
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	frameCount = 1;
	frameTime = 1;
	timeElapsed = 0.0;
	currentFrame = 0;
	SetClip(0, 0, width / frameCount, height);
}

Sprite::Sprite(const char* file, int frameCount, float frameTime)
{
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	timeElapsed = 0.0;
	currentFrame = 0;
	Open(file);
	SetClip(0, 0, width / frameCount, height);
}


/* ************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Sprite::~Sprite(){}


/* ************************************************************
 *
 * Abrir imagem
 *
 *************************************************************/
void Sprite::Open(const char* file)
{
	texture = Resources::GetImage(file);
	SDL_QueryTexture ( texture, NULL, NULL, &width, &height );
}


/* ************************************************************
 *
 * Setar o clip da imagem
 *
 *************************************************************/
void Sprite::SetClip(int x, int y, int w, int h)
{
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}


/* ************************************************************
 *
 * Renderizar imagem
 *
 *************************************************************/
void Sprite::Render(int x, int y, float angle)
{
	SDL_Rect dstRect;

	dstRect.x = x - Camera::pos.x;
	dstRect.y = y - Camera::pos.y;
	dstRect.w = clipRect.w * scaleX;
	dstRect.h = clipRect.h * scaleY;

	//std::cout << scaleX << ", " << scaleY << std::endl;

	SDL_RenderCopyEx ( Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, (double)angle, NULL, SDL_FLIP_NONE );
}


/* ************************************************************
 *
 * Retornar largura da imagem
 *
 *************************************************************/
int Sprite::GetWidth()
{
	return (width / frameCount) * scaleX;
}


/* ************************************************************
 *
 * Retornar altura da imagem
 *
 *************************************************************/
int Sprite::GetHeight()
{
	return height * scaleY;
}


/* ************************************************************
 *
 * Indicar se imagem está alocada
 *
 *************************************************************/
bool Sprite::IsOpen()
{
	return texture == NULL ? false : true;
}


/* ************************************************************
 *
 * Setar escala
 *
 *************************************************************/
void Sprite::SetScaleX(float scale)
{
	scaleX = scale;
}

void Sprite::SetScaleY(float scale)
{
	scaleY = scale;
}



/* ************************************************************
 *
 * Update frame da animação
 *
 *************************************************************/
void Sprite::Update(float dt)
{
	timeElapsed += dt;
	if (timeElapsed >= frameTime)
	{
		SetFrame(currentFrame + 1);
		timeElapsed = 0.0;
	}
}


/* ************************************************************
 *
 * Setar frame da animação
 *
 *************************************************************/
void Sprite::SetFrame(int frame)
{
	if(frame >= frameCount)
		currentFrame = frame % frameCount;
	else
		currentFrame = frame;
	SetClip( currentFrame * width / frameCount, 0, width / frameCount, height );
}



/* ************************************************************
 *
 * Setar número de frames da animação
 *
 *************************************************************/
void Sprite::SetFrameCount(int frameCount)
{
	this->frameCount = frameCount;
}



/* ************************************************************
 *
 * Setar tempo de frames da animação
 *
 *************************************************************/
void Sprite::SetFrameTime(float frameTime)
{
	this->frameTime = frameTime;
}