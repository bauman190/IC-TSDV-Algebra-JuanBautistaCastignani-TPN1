#include "Utils.h"

bool isLineCollidingWithLine(Vector2 a, Vector2 a2, Vector2 b, Vector2 b2)
{
	float uA = ((b2.x - b.x) * (a.y - b.y) - (b2.y - b.y) * (a.x - b.x)) /
		((b2.y - b.y) * (a2.x - a.x) - (b2.x - b.x) * (a2.y - a.y));

	float uB = ((a2.x - a.x) * (a.y - b.y) - (a2.y - a.y) * (a.x - b.x)) /
		((b2.y - b.y) * (a2.x - a.x) - (b2.x - b.x) * (a2.y - a.y));

	return uA >= 0  && uA <= 1 && uB >= 0  && uB <= 1 ;
}
