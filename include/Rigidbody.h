#pragma once

#ifndef _RIGIDBODY

#define _RIGIDBODY

#include "Vector.hpp"

class Rigidbody {

private:

	Vector center;
	double rotate;

public:

	Rigidbody();

	Rigidbody(Vector Center, double rot = 0);

	Vector getPosition() const;

	double getRotate() const;

};

#endif // !_RIGIDBODY