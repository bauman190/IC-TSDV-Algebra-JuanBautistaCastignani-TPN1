#include "raylib.h"
#include "polygon.h"
#include "vector"
#include "raymath.h"

std::vector<Polygon> polygons;
Vector2 lastMousePosition = { 0,0 };
int selectedPolygon = -1;

void handlePolygonMovement();
void drawPolygons();
void createPolygon(Polygon& p1);
void drawUnfinishedPolygon(Polygon& p1);
bool checkSimplePolygon(Polygon polygon);
void checkColPolyPoly();
bool checkColPointPoly(Vector2 point, Polygon polygon);

int main(void)
{
    
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "TP1_A");      

    Polygon p1;

    while (!WindowShouldClose())    
    {
        createPolygon(p1);

        if (IsKeyDown(KEY_BACKSPACE) && selectedPolygon >= 0)
        {
            polygons.erase(polygons.begin() + selectedPolygon);
            selectedPolygon = -1;
        }

        for (int i = 0; i < polygons.size(); i++)
        {
            choosePolyColor(polygons[i]);
        }

        if (polygons.size() > 0)
        {
            handlePolygonMovement();
        }

        checkColPolyPoly();

        BeginDrawing();

        ClearBackground(BLACK);

        drawPolygons();

        drawUnfinishedPolygon(p1);

        EndDrawing();
        
    }
    
    CloseWindow();        

    return 0;
}



void handlePolygonMovement()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedPolygon >= 0)
    {
        polygons[selectedPolygon].isSelected = false;
        selectedPolygon = -1;
    }


    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && (selectedPolygon < 0))
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
    }

    if (selectedPolygon >= 0)
    {
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
    }
}

void drawPolygons()
{
    if (polygons.size() >= 1)
    {
        for (int i = 0; i < polygons.size(); i++)
        {
            DrawPolygon(polygons[i]);
        }
    }
}

void createPolygon(Polygon& p1)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (p1.points.size() >= 3 && Vector2Distance(p1.points[0], GetMousePosition()) < 50) //si tengo mas de 3 puntos y la distancia entre el que estoy agregando y el inicial es menor a 50
        {
            p1.color = BLUE;
            if (checkSimplePolygon(p1))
            {
                polygons.push_back(p1);//agrego mi poligono a el vector 
            }
            p1.points.clear();// limpio el vector donde estan los puntos. Si no entendiste esto desp te lo explico 

        }
        else //en caso de que no pase lo de antes simplemente agrego el punto 
        {
            p1.points.push_back(GetMousePosition());
        }
    }
}

void drawUnfinishedPolygon(Polygon& p1)
{
    //dibujo las lineas que van a formar mi siguiente poligono 
    if (p1.points.size() >= 2)
    {
        for (int i = 0; i < p1.points.size(); i++)
        {
            if (i + 1 != p1.points.size())
            {
                DrawLineV(p1.points[i], p1.points[i + 1], GREEN);
            }
        }
    }
}

bool lineLineCol(Vector2 a, Vector2 a2, Vector2 b, Vector2 b2)
{
    float uA = ((b2.x - b.x) * (a.y - b.y) - (b2.y - b.y) * (a.x - b.x)) /
        ((b2.y - b.y) * (a2.x - a.x) - (b2.x - b.x) * (a2.y - a.y));

    float uB = ((a2.x - a.x) * (a.y - b.y) - (a2.y - a.y) * (a.x - b.x)) /
        ((b2.y - b.y) * (a2.x - a.x) - (b2.x - b.x) * (a2.y - a.y));

    return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
}

bool checkSimplePolygon(Polygon polygon)
{
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

            if (lineLineCol(a1, a2, b1, b2)) 
                return false; 
            
        }
    }
    return true;
}

bool checkColPointPoly(Vector2 point, Polygon polygon)
{

    Vector2 raycast = { GetScreenWidth(), point.y };

    int counter = 0;

    for (int i = 0; i < polygon.points.size(); i++)
    {
        Vector2 a1 = polygon.points[i];
        Vector2 a2 = polygon.points[(i + 1) % polygon.points.size()];

        if (lineLineCol(point, raycast, a1, a2))
            counter++;
            
    }
    return counter % 2 == 1;
}

void checkColPolyPoly()
{
    for (int i = 0; i < polygons.size(); i++)
    {
        polygons[i].isColliding = false;
    }

    for (int i = 0; i < polygons.size(); i++)
    {
        for (int j = 0; j < polygons[i].points.size(); j++)
        {
            for (int v = 0; v < polygons.size(); v++)
            {
                if (i == v) continue;

                if (checkColPointPoly(polygons[i].points[j], polygons[v]))
                {
                    polygons[i].isColliding = true;
                    polygons[v].isColliding = true;
                }


                for (int q = 0; q < polygons[v].points.size(); q++)
                {
                    if (lineLineCol(polygons[i].points[j], polygons[i].points[(j + 1) % polygons[i].points.size()],
                        polygons[v].points[q], polygons[v].points[(q + 1) % polygons[v].points.size()]))
                    {
                        polygons[i].isColliding = true;
                        polygons[v].isColliding = true;
                    }
                }
            }           
        }
    }
}

