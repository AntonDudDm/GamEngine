#pragma once


#ifndef _INTERSECTIONDETECTOR

#define _INTERSECTIONDETECTOR

#include "Vector.hpp"
#include "Line.h"
#include "Figures.h"

class IntersectionDetector {

private:


public:

	bool PointInLine(Vector point, Line line) {};

	bool PointInCircle(Vector point, Circle cirle) {};

	bool PointInAABB(Vector point, AABB box) {};

	bool PointInBOX2D(Vector point, BOX2D box) {};
};

#endif // !_INTERSECTIONDETECTOR