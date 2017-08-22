#include "Geometria.h"


/* ***********************************************************
 *
 * Construtores de Point
 *
 * *********************************************************** */
Point::Point()
{
	this->x = 0.0;
	this->y = 0.0;
}

Point::Point(const float x, const float y)
{
	this->x = x;
	this->y = y;
}


/* ***********************************************************
 *
 * Operadores de Point
 *
 * *********************************************************** */
Point Point::operator+ (const Point& p2)
{
	Point point;
	point.x = this->x + p2.x;
	point.y = this->y + p2.y;
	return point;
}

Point Point::operator- (const Point& p2)
{
	Point point;
	point.x = this->x - p2.x;
	point.y = this->y - p2.y;
	return point;
}


/* ***********************************************************
 *
 * Multiplicação de vetor por escalar
 *
 * *********************************************************** */
Point Point::operator* (const float& escalar) const
{
	Point point;
	point.x = this->x * escalar;
	point.y = this->y * escalar;
	return point;
}


/* ***********************************************************
 *
 * Rotacionar vetor
 *
 * *********************************************************** */
void Point::Rotate(float angle)
{
	angle = angle * PI / 180; // converte de graus para radianos
	float curX = this->x, curY = this->y;
	this->x = curX * cos(angle) - curY * sin(angle);
	this->y = curY * cos(angle) + curX * sin(angle);
}


void Point::Rotate(Point point, float module, float angle)
{
	angle = angle * PI / 180;
	this->x = module * sin(angle) + point.x;
	this->y = module * cos(angle) + point.y;
}



/* ***********************************************************
 *
 * Projecao nos eixos a partir de um vetor com mudulo e direcao
 *
 * *********************************************************** */
float ProjectX(float module, float angle)
{
	angle = angle * PI / 180; // converte de graus para radianos
	return cos(angle) * module;
}

float ProjectY(float module, float angle)
{
	angle = angle * PI / 180; // converte de graus para radianos
	return sin(angle) * module;
}



/* ***********************************************************
 *
 * Distancia entre dois pontos
 *
 * *********************************************************** */
float Distance(Point p1, Point p2)
{
	return sqrt( pow ( p2.x - p1.x, 2.0 ) + pow ( p2.y - p1.y, 2.0 ) );
}


/* ***********************************************************
 *
 * Inclinação da reta entre dois pontos
 *
 * *********************************************************** */
float LineInclination(Point p1, Point p2)
{
	float angle = atan( (p2.y - p1.y) / (p2.x - p1.x) ) * 180 / PI; // converte para graus
	if (p1.x > p2.x)
		return angle + 180;
	return angle;
}


/* ***********************************************************
 *
 * Construtores de Rect
 *
 * *********************************************************** */
Rect::Rect()
{
	this->x = 0.0;
	this->y = 0.0;
	this->w = 0.0;
	this->h = 0.0;
}

Rect::Rect(const float x, const float y, const float w, const float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}


/* ***********************************************************
 *
 * Retorna ponto do centro de Rect
 *
 * *********************************************************** */
Point Rect::Center() const
{
	return Point ( this->x + this->w / 2, this->y + this->h / 2 );
}


void Rect::Center(float* x, float* y)
{
	*x = this->x + this->w / 2;
	*y = this->y + this->h / 2;
}


/* ***********************************************************
 *
 * Operador de soma de Rect com um ponto
 *
 * *********************************************************** */
Rect Rect::operator+ (const Point& point)
{
	Rect rect;
	rect.x = this->x + point.x;
	rect.y = this->y + point.y;
	rect.w = this->w;
	rect.h = this->h;
	return rect;
}


/* ***********************************************************
 *
 * True se o ponto está dentro do retangulo
 *
 * *********************************************************** */
bool Rect::IsInside(Point point)
{
	if ( point.x >= this->x &&
		 point.x <= this->x + this->w &&
		 point.y >= this->y &&
		 point.y <= this->y + this->h )
		return true;
	else
		return false;
}


/* ***********************************************************
 *
 * Distancia entre os centros de dois retangulos
 *
 * *********************************************************** */
float Distance(Rect r1, Rect r2)
{
	return Distance( r1.Center(), r2.Center() );
}