#include "polygon.h"

void DrawPolygon(Polygon polygon)
{
    for (int i = 0; i < polygon.points.size(); i++)
    {
        if (i + 1 == polygon.points.size())
        {
            DrawLineV(polygon.points[i], polygon.points[0], polygon.color);
        }
        else
        {
            DrawLineV(polygon.points[i], polygon.points[i + 1], polygon.color);
        }
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
