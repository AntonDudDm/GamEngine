#pragma once


#ifndef _INTERSECTIONDETECTOR

#define _INTERSECTIONDETECTOR

#include "Vector.hpp"
#include "Line.h"
#include "Figures.h"

class IntersectionDetector {

private:


public:

	static bool PointInLine(Vector point, Line line) {};

	static bool PointInCircle(Vector point, Circle cirle) {};

	static bool PointInAABB(Vector point, AABB box) {};

	static bool PointInBOX2D(Vector point, BOX2D box) {};

	static bool LineInCircle(Line line, Circle circle) {};
};

#endif // !_INTERSECTIONDETECTOR