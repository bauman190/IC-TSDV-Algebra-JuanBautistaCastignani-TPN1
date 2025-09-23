#pragma once
#include "raylib.h"
#include "raymath.h"
#include "vector"
#include "Utils.h"
#include "Constants.h"

using namespace std;

struct Polygon
{
	vector<Vector2> points;
	Color color = GREEN;
	bool isColliding = false;
	bool isSelected = false;
	bool isRegular = true;
};

void handlePolygonMovement(vector<Polygon>& polygons, int& selectedPolygon, Vector2& prevMousePos);
void DrawPolygon(Polygon polygon);
void drawPolygons(vector<Polygon> polygons);
void drawUnfinishedPolygon(Polygon& p1);
void choosePolysColor(vector<Polygon>& polygons);
void choosePolyColor(Polygon& polygon);
void createPolygon(vector<Polygon>& polygons, Polygon& auxPoly);
bool isLineOverLappingPolygon(Polygon polygon, Vector2 myLinePoint1Pos, Vector2 myLinePoint2Pos);
void SetColsPolyPoly(vector<Polygon>& polygons);
bool isPointCollidingWithPoly(Vector2 point, Polygon polygon);



