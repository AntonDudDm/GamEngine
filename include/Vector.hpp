#pragma once

#ifndef _VECTOR
#define _VECTOR

#define _EPSILON 0.000001

class Vector {

private:

	double x, y;

public:

	Vector(double X = 0, double Y = 0) {
		x = X;
		y = Y;
	}

	double getX() const
	{
		return x;
	}

	double getY() const
	{
		return y;
	}

	double setX(double X) {
		x = X;
	}

	double setY(double Y) {
		y = Y;
	}


	Vector(Vector& a) {
		x = a.getX();
		y = a.getY();
	}


	Vector(const Vector& a) {
		x = a.getX();
		y = a.getY();
	}

	Vector& operator=(Vector& a) {
		x = a.getX();
		y = a.getY();

		return *this;
	}


	Vector& operator=(const Vector& a) {
		x = a.getX();
		y = a.getY();

		return *this;
	}


	Vector& operator-(Vector a) const{

		Vector Res;

		Res.setX(x - a.getX());
		Res.setY(y - a.getY());

		return Res;
	}

	Vector& operator*(double c) const {
		Vector Res;

		Res.setX(x * c);
		Res.setY(y * c);

		return Res;
	}

	bool operator==(Vector a) {
		return abs(x - a.getX()) <= _EPSILON * max(1.0, max(abs(x), abs(a.getX()))) &&
			abs(y - a.getY()) <= _EPSILON * max(1.0, max(abs(y), abs(a.getY())));
	}


	Vector& operator+(Vector a) const{
		Vector Res;

		Res.setX(x + a.getX());
		Res.setY(y + a.getY());

		return Res;
	}

	double LengthSquared() const {
		return x * x + y * y;
	}

};

#endif // !_VECTOR