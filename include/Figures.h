#pragma once

#ifndef _FIGURES

#define _FIGURES

using namespace std;
#include <iostream>
#include "Vector.hpp"
#include "Rigidbody.h"
#include <vector>


//
class Circle {

private:

	double radius;
	Rigidbody body;

public:

	Circle(double rad = 0) {}

	double getRadius() const{
		return radius;
	}

	Vector getCenter() const {
		return body.getPosition();
	}

};


//AABB
class AABB {

private:

	
	Vector size;
	Rigidbody body;

public:

	AABB() {}

	AABB(Vector min, Vector max) {};

	Vector getMin() const {};

	Vector getMax() const {};

};


class BOX2D {

private:


	Vector size;
	Rigidbody body;

public:

	BOX2D() {}

	BOX2D(Vector min, Vector max) {};

	Vector getMin() const {};

	Vector getMax() const {};

	double getRotate() const {};

	Vector getPosition() const {};

	vector<Vector> getVertices() const{};



};

#endif // !_FIGURES

