#pragma once

#ifndef _MATH

#define _MATH

using namespace std;

#include "../include/Vector.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>


class Math {


public:

	//������� �������� ��������:
	/*
	 ________________
	|                |
	|cos(a)    sin(a)|
	|				 |
	|sin(a)    cos(a)|
	|________________|

	������� �������� ������� ������� ������� ������������ � �����,
	����� ������������, ����� �������� ��������� ������� �������.
	
	*/
	
	
	// origin - ����� ������ ������� ���������� ��������
	void rotate(Vector vector, double AngleDegree, Vector origin) {};

	double toRadians(double angle) {};

	bool Compare(double x, double y, double epsilon = _EPSILON) {};

	bool Compare(Vector vec1, Vector vec2, double epsilon = _EPSILON) {};
};

#endif // !_MATH

