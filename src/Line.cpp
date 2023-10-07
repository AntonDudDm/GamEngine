using namespace std;
#include <iostream>

#include "../include/Line.h"
#include "../include/Math.h"

Line::Line(Vector From, Vector To) {

	from = From;
	to = To;
};

Line::Line(Line& a) {
	from = a.getFrom();
	to = a.getTo();
};

Vector Line::getFrom() const {
	return from;
};

Vector Line::getTo() const {
	return to;
};

double Line::lengthSquared() {
	Vector vec = to - from;
	return vec.LengthSquared();
};

Line Line::lineRotate(double AngleDegree, Vector origin) {

	Vector newFrom = from;
	Math::rotate(newFrom, AngleDegree, origin);

	Vector newTo = to;
	Math::rotate(newTo, AngleDegree, origin);

	Line res(newFrom, newTo);

	return res;
};



