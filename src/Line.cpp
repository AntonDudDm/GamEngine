using namespace std;
#include <iostream>

#include "../include/Line.h"

Line::Line(Vector From, Vector To) {

	from = From;
	to = To;
};



Vector Line::getFrom() const {
	return from;
};

Vector Line::getTo() const {
	return to;
};



