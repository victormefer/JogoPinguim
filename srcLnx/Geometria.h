#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <cmath>
#define PI 3.14159265359

class Point
{
public:
	Point();
	Point(const float x, const float y);

	float x, y;

	Point operator+ (const Point&);
	Point operator- (const Point&);
	// Multiplicação de vetor por escalar
	Point operator* (const float&) const;

	void Rotate(float angle);
	// Rotacionar em volta de outro ponto
	void Rotate(Point point, float module, float angle);

};

float Distance(Point p1, Point p2);

// Inclinação da reta formada por dois pontos
float LineInclination(Point p1, Point p2);


float ProjectX(float module, float angle);
float ProjectY(float module, float angle);


class Rect
{
public:
	Rect();
	Rect(const float x, const float y, const float w, const float h);

	float x, y, w, h;

	Point Center() const;
	void Center(float* x, float* y);

	// Somar retangulo com um ponto para mover retangulo
	Rect operator+ (const Point&);

	// Saber se um ponto esta dentro de um retangulo
	bool IsInside(Point);

};

float Distance(Rect r1, Rect r2);


#endif // GEOMETRIA_H