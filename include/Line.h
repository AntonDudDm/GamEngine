#pragma once


#ifndef _LINE

#define _LINE

#include "Vector.hpp"


class Line {

private:

	Vector from;
	Vector to;

public:

	Line(Vector From, Vector To) {};

	Vector getFrom() const {};

	Vector getTo() const {};

	bool PointInLine(Vector point, Line line) {};

};


#endif // !_LINE
