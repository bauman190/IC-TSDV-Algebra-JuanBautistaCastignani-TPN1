#pragma once
#include "raylib.h"
#include "vector"

struct Polygon
{
	std::vector<Vector2> points;
	Color color;
	bool isColliding = false;
	bool isSelected = false;
};

void DrawPolygon(Polygon polygon);

void choosePolyColor(Polygon& polygon);


