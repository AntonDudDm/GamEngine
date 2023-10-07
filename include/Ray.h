#pragma once

#ifndef _RAY
#define _RAY

#include "../include/Vector.hpp"

class Ray {

private:
	//������ �������
	Vector origin;

	//���������� ���������� ������� �����
	Vector direction;

public:

	Ray(Vector Origin, Vector Direction);

	Vector getOrigin() const;

	Vector getDirection() const;
};



#endif // !_RAY
