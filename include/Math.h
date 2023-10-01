#pragma once

#ifndef _MATH

#define _MATH


#include "../include/Vector.hpp"


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
	static void rotate(Vector vector, double AngleDegree, Vector origin) {};

	static double toRadians(double angle) {};

	static bool Compare(double x, double y, double epsilon = DBL_MIN) {};

	static bool Compare(Vector vec1, Vector vec2, double epsilon = DBL_MIN) {};
};

#endif // !_MATH

