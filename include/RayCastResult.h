#pragma once

#ifndef _RAYCASTRESULT
#define _RAYCASTRESULT

#include "../include/Vector.hpp"


class RayCastResult {

private:

	//����� ����������� � ���� � ��������
	Vector point;
	//������� ��������� ���� �� �������
	Vector normal;
	//���������� ���������� �� ���������� �� ����� ���������� ���� �� �������
	double t;
	//���������� ���������� ����� �� ��� �� ������� ��� ���
	bool hit;

public:

	RayCastResult();

	//����� ������� ����� ����� �������� ��������� �����
	void init(Vector Point, Vector Normal, double T, bool Hit);

	//����� ����������� ��������
	static void reset(RayCastResult result);


};


#endif // !_RAYCASTRESULT
