#pragma once


#ifndef _LINE

#define _LINE

#include "Vector.hpp"


class Line {

private:

	Vector from;
	Vector to;

public:

	Line(Vector From, Vector To);

	Line(Line& a);

	Vector getFrom() const;

	Vector getTo() const;

	double lengthSquared();

	Line lineRotate(double AngleDegree, Vector origin);

};


#endif // !_LINE
