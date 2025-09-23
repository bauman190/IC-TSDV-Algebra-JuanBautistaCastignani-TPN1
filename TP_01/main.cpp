//quedo un bugsito, tiene que ver con como sabe si esta adentro o no un punto de una figura, pasa cuando el raycast toca la interseccion entre dos lineas
#include "raylib.h"
#include "polygon.h"
#include "vector"
#include "raymath.h"
#include "Utils.h"

std::vector<Polygon> polygons;
Vector2 lastMousePosition = { 0,0 };
int selectedPolygon = -1;

int main(void)
{

	const int screenWidth = 1280;
	const int screenHeight = 720;

	Vector2 prevMousePos = { 0,0 };

	InitWindow(screenWidth, screenHeight, "TP1_A");

	Polygon auxPoly;

	while (!WindowShouldClose())
	{
		if (selectedPolygon < 0)
		{
			createPolygon(polygons, auxPoly);
		}

		if (polygons.size() > 0)
		{
			handlePolygonMovement(polygons, selectedPolygon, prevMousePos);
		}

		SetColsPolyPoly(polygons);

		choosePolysColor(polygons);

		BeginDrawing();

		ClearBackground(BLACK);

		drawPolygons(polygons);

		drawUnfinishedPolygon(auxPoly);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}


