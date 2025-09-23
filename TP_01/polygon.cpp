#include "polygon.h"
#include <iostream>

void handlePolygonMovement(vector<Polygon>& polygons, int& selectedPolygon, Vector2& prevMousePos)
{
	/*
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedPolygon >= 0)
	{
		polygons[selectedPolygon].isSelected = false;
		selectedPolygon = -1;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedPolygon < 0)
	{
		for (int i = 0; i < polygons.size(); i++)
		{
			if (checkColPointPoly(GetMousePosition(), polygons[i]))
			{
				selectedPolygon = i;
				polygons[i].isSelected = true;
				break;
			}
		}
		prevMousePos = GetMousePosition();

	}
	*/
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		for (int i = 0; i < polygons.size(); i++)
		{
			if (isPointCollidingWithPoly(GetMousePosition(), polygons[i]) && selectedPolygon < 0)
			{
				selectedPolygon = i;
				polygons[i].isSelected = true;
				break;
			}
		}
	}
	else
	{
		for (int polygon = 0; polygon < polygons.size(); polygon++)
		{
			polygons[polygon].isSelected = false;
		}
		selectedPolygon = -1;
	}
	if (selectedPolygon >= 0)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			for (int currentPoint = 0; currentPoint < polygons[selectedPolygon].points.size(); currentPoint++)
			{
				if (GetMousePosition().x > prevMousePos.x)
				{
					polygons[selectedPolygon].points[currentPoint].x += abs(GetMousePosition().x) - abs(prevMousePos.x);
				}
				else if (GetMousePosition().x < prevMousePos.x)
				{
					polygons[selectedPolygon].points[currentPoint].x -= abs(prevMousePos.x) - abs(GetMousePosition().x);
				}

				if (GetMousePosition().y > prevMousePos.y)
				{
					polygons[selectedPolygon].points[currentPoint].y += abs(GetMousePosition().y) - abs(prevMousePos.y);
				}
				else if (GetMousePosition().y < prevMousePos.y)
				{
					polygons[selectedPolygon].points[currentPoint].y -= abs(prevMousePos.y) - abs(GetMousePosition().y);
				}
			}
		}
	}
	prevMousePos = GetMousePosition();
	/*
	if (IsKeyDown(KEY_LEFT))
	{
		for (int i = 0; i < polygons[selectedPolygon].points.size(); i++)
		{
			polygons[selectedPolygon].points[i].x -= 100 * GetFrameTime();
		}

	}
	if (IsKeyDown(KEY_RIGHT))
	{
		for (int i = 0; i < polygons[selectedPolygon].points.size(); i++)
		{
			polygons[selectedPolygon].points[i].x += 100 * GetFrameTime();
		}
	}
	if (IsKeyDown(KEY_UP))
	{
		for (int i = 0; i < polygons[selectedPolygon].points.size(); i++)
		{
			polygons[selectedPolygon].points[i].y -= 100 * GetFrameTime();
		}
	}
	if (IsKeyDown(KEY_DOWN))
	{
		for (int i = 0; i < polygons[selectedPolygon].points.size(); i++)
		{
			polygons[selectedPolygon].points[i].y += 100 * GetFrameTime();
		}
	}
	*/

}
void DrawPolygon(Polygon polygon)
{
	for (int i = 0; i < polygon.points.size(); i++)
	{
		if (i + 1 == polygon.points.size())
		{
			DrawLineEx(polygon.points[i], polygon.points[0], LineInitialThickness, polygon.color);
		}
		else
		{
			DrawLineEx(polygon.points[i], polygon.points[i + 1], LineInitialThickness, polygon.color);
		}
	}
}
void drawPolygons(std::vector<Polygon> polygons)
{
	if (polygons.size() >= 1)
	{
		for (int i = 0; i < polygons.size(); i++)
		{
			DrawPolygon(polygons[i]);
		}
	}
}
void drawUnfinishedPolygon(Polygon& polygon)
{
	//dibujo las lineas que van a formar mi siguiente poligono 
	if (polygon.points.size() >= 2)
	{
		for (int i = 0; i < polygon.points.size(); i++)
		{
			if (i + 1 != polygon.points.size())
			{
				DrawLineEx(polygon.points[i], polygon.points[i + 1], LineInitialThickness, GREEN);
			}
		}
	}
}
void choosePolysColor(vector<Polygon>& polygons)
{
	for (int current = 0; current < polygons.size(); current++)
	{
		choosePolyColor(polygons[current]);
	}
}
void choosePolyColor(Polygon& polygon)
{
	if (polygon.isSelected && polygon.isColliding)
		polygon.color = ORANGE;

	else if (polygon.isSelected)
		polygon.color = YELLOW;

	else if (polygon.isColliding)
		polygon.color = RED;

	else
		polygon.color = BLUE;
}
void createPolygon(vector<Polygon>& polygons, Polygon& auxPoly)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (auxPoly.points.size() >= 3 && Vector2Distance(auxPoly.points[0], GetMousePosition()) < ClosePolyTriggerDistance) //si tengo mas de 3 puntos y la distancia entre el que estoy agregando y el inicial es menor a 50
		{
			//si una vez dados los puntos el ultimo no puede cerrar con el primero entonces es irregular. 
			for (int currentLine = 0; currentLine < auxPoly.points.size() - 1; currentLine++) //el menos 1 excluye a la ultima linea
			{
				Vector2 currentLinePoint1 = auxPoly.points[currentLine];
				Vector2 currentLinePoint2 = auxPoly.points[currentLine + 1];

				if (isLineCollidingWithLine(auxPoly.points[auxPoly.points.size() - 1], auxPoly.points[0], currentLinePoint1, currentLinePoint2)
					&& auxPoly.points[auxPoly.points.size() - 1].x != currentLinePoint1.x
					&& auxPoly.points[auxPoly.points.size() - 1].y != currentLinePoint1.y
					&& auxPoly.points[auxPoly.points.size() - 1].x != currentLinePoint2.x
					&& auxPoly.points[auxPoly.points.size() - 1].y != currentLinePoint2.y

					&& auxPoly.points[0].x != currentLinePoint1.x
					&& auxPoly.points[0].y != currentLinePoint1.y
					&& auxPoly.points[0].x != currentLinePoint2.x
					&& auxPoly.points[0].y != currentLinePoint2.y)
				{
					auxPoly.isRegular = false;
				}
			}

			if (auxPoly.isRegular)
			{
				polygons.push_back(auxPoly);//agrego mi poligono a el vector 
				auxPoly.color = BLUE;
			}
			auxPoly.points.clear();
			auxPoly.isRegular = true;
		}
		else
		{
			auxPoly.points.push_back(GetMousePosition());

			if (auxPoly.points.size() > 1)
			{
				int latestPointIndex = auxPoly.points.size() - 1;
				int secondLatestPointIndex = auxPoly.points.size() - 2;

				Vector2 latestPointPos = auxPoly.points[latestPointIndex];
				Vector2 secondLatestPointPos = auxPoly.points[secondLatestPointIndex];

				if (isLineOverLappingPolygon(auxPoly, latestPointPos, secondLatestPointPos))
				{
					auxPoly.isRegular = false;
				}
			}
		}
	}
}
bool isLineOverLappingPolygon(Polygon polygon, Vector2 myLinePoint1, Vector2 myLinePoint2)
{
	int maxLines = polygon.points.size() - 1 - 1; //por cada punto en una figura hay una linea, los -1 son: uno para manejarlo como indice, en el array de puntos y el otro pq revisas antes de cerrar la figura

	for (int currentLine = 0; currentLine < maxLines; currentLine++)
	{
		Vector2 currentLinePoint1 = polygon.points[currentLine];
		Vector2 currentLinePoint2 = polygon.points[currentLine + 1];

		if (isLineCollidingWithLine(myLinePoint1, myLinePoint2, currentLinePoint1, currentLinePoint2)
			&& myLinePoint1.x != currentLinePoint1.x
			&& myLinePoint1.y != currentLinePoint1.y
			&& myLinePoint1.x != currentLinePoint2.x
			&& myLinePoint1.y != currentLinePoint2.y
			
			&& myLinePoint2.x != currentLinePoint1.x
			&& myLinePoint2.y != currentLinePoint1.y
			&& myLinePoint2.x != currentLinePoint2.x
			&& myLinePoint2.y != currentLinePoint2.y)
		{
			return true;
		}
	}

	return false;


	/*
	for (int i = 0; i < polygon.points.size(); i++)
	{
		Vector2 a1 = polygon.points[i];
		Vector2 a2 = polygon.points[(i + 1) % polygon.points.size()];

		for (int j = i + 1; j < polygon.points.size(); j++) {
			Vector2 b1 = polygon.points[j];
			Vector2 b2 = polygon.points[(j + 1) % polygon.points.size()];


			if (i == j) continue;
			if ((i + 1) % polygon.points.size() == j) continue;
			if (i == (j + 1) % polygon.points.size()) continue;

			if (isLineCollidingWithLine(a1, a2, b1, b2))
				return false;

		}
	}
	return true;
	*/
}
void SetColsPolyPoly(vector<Polygon>& polygons)
{
	int maxPolys = polygons.size();

	int myPolyMaxLines = 0;
	Vector2 myLinePoint1 = { 0,0 };
	Vector2 myLinePoint2 = { 0,0 };

	int toCheckMaxPolyLines = 0;
	Vector2 toCheckLinePoint1 = { 0,0 };
	Vector2 toCheckLinePoint2 = { 0,0 };

	//Por cada poligono checkea si alguno de sus lados colisiona con alguno de los lados de alguno de los poligonos
	//myPoly es el que esta actualmente checkeandose como principal, y toCheck es con quien se esta checkeando


	for (int myPoly = 0; myPoly < maxPolys; myPoly++)
	{
		polygons[myPoly].isColliding = false;

		myPolyMaxLines = polygons[myPoly].points.size();

		for (int myPolyLines = 0; myPolyLines < myPolyMaxLines; myPolyLines++)
		{
			myLinePoint1 = polygons[myPoly].points[myPolyLines];

			if (myPolyLines + 1 < myPolyMaxLines)
			{
				myLinePoint2 = polygons[myPoly].points[myPolyLines + 1];
			}
			else
			{
				myLinePoint2 = polygons[myPoly].points[0];
			}

			for (int toCheckPoly = 0; toCheckPoly < maxPolys; toCheckPoly++)
			{
				toCheckMaxPolyLines = polygons[toCheckPoly].points.size();

				for (int toCheckLines = 0; toCheckLines < toCheckMaxPolyLines; toCheckLines++)
				{
					toCheckLinePoint1 = polygons[toCheckPoly].points[toCheckLines];

					if (toCheckLines + 1 < toCheckMaxPolyLines)
					{
						toCheckLinePoint2 = polygons[toCheckPoly].points[toCheckLines + 1];
					}
					else
					{
						toCheckLinePoint2 = polygons[toCheckPoly].points[0];
					}

					if (isLineCollidingWithLine(myLinePoint1, myLinePoint2, toCheckLinePoint1, toCheckLinePoint2))
					{
						//polygons[myPoly].isColliding = true;
					}
				}
			}
		}
	}


	Vector2 myCurrentPoint = { };

	Polygon currentToCheckPoly = { };


	for (int myPoly = 0; myPoly < maxPolys; myPoly++)
	{
		for (int myPolyPoints = 0; myPolyPoints < polygons[myPoly].points.size(); myPolyPoints++)
		{
			myCurrentPoint = polygons[myPoly].points[myPolyPoints];

			for (int toCheckPoly = 0; toCheckPoly < maxPolys; toCheckPoly++)
			{
				currentToCheckPoly = polygons[toCheckPoly];

				if (myPoly == toCheckPoly)
				{
					continue;
				}
				else
				{
					if (isPointCollidingWithPoly(myCurrentPoint, currentToCheckPoly) && myPoly != toCheckPoly)
					{
						polygons[myPoly].isColliding = true;
						polygons[toCheckPoly].isColliding = true;
					}
				}
				
			}
		}
	}

	/*
	for (int i = 0; i < polygons.size(); i++)
	{
		for (int j = 0; j < polygons[i].points.size(); j++)
		{
			for (int v = 0; v < polygons.size(); v++)
			{
				if (i == v) continue;

				if (isPointCollidingWithPoly(polygons[i].points[j], polygons[v]))
				{
					polygons[i].isColliding = true;
					polygons[v].isColliding = true;
				}
			}
		}
	}
	*/
}
bool isPointCollidingWithPoly(Vector2 point, Polygon polygon)
{
	Vector2 raycast = { GetScreenWidth(), point.y };
	Vector2 toCheckPoint1 = { };
	Vector2 toCheckPoint2 = { };

	int maxToCheckPolyLines = polygon.points.size();

	int collideCounter = 0;


	for (int toCheckLines = 0; toCheckLines < maxToCheckPolyLines; toCheckLines++)
	{
		toCheckPoint1 = polygon.points[toCheckLines];

		if (toCheckLines + 1 < maxToCheckPolyLines)
		{
			toCheckPoint2 = polygon.points[toCheckLines + 1];
		}
		else if (toCheckLines + 1 >= maxToCheckPolyLines)
		{
			toCheckPoint2 = polygon.points[0];
		}
		if (isLineCollidingWithLine(point, raycast, toCheckPoint1, toCheckPoint2) && (point.y > toCheckPoint1.y != point.y > toCheckPoint2.y))
		{
			collideCounter++;
		}
	}

	std:: cout << collideCounter << " ";
	if (collideCounter % 2 != 0)
	{
		cout << "Pego maestro" << " ";
	}

	return collideCounter % 2 != 0;



	/*
	int counter = 0;

	for (int i = 0; i < polygon.points.size(); i++)
	{
		Vector2 a1 = polygon.points[i];
		Vector2 a2 = polygon.points[(i + 1) % polygon.points.size()];

		if (isLineCollidingWithLine(point, raycast, a1, a2) && ((a1.y > point.y) != (a2.y > point.y)))
			counter++;

	}
	return counter % 2 == 1;
	*/

}
