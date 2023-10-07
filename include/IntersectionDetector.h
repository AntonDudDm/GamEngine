#pragma once


#ifndef _INTERSECTIONDETECTOR

#define _INTERSECTIONDETECTOR

#include "Vector.hpp"
#include "Line.h"
#include "Figures.h"
#include "Ray.h"
#include "RayCastResult.h"

class IntersectionDetector {

private:


public:

	static bool PointInLine(Vector point, Line line);

	static bool PointInCircle(Vector point, Circle cirle);

	static bool PointInAABB(Vector point, AABB box);

	static bool PointInBOX2D(Vector point, BOX2D box);

	static bool LineInCircle(Line line, Circle circle);

	static bool LineInAABB(Line line, AABB box);

	static bool LineInBOX2D(Line line, BOX2D box);

	//RayCast

	static bool RayCast(Circle circle, Ray ray, RayCastResult result);

};

#endif // !_INTERSECTIONDETECTOR