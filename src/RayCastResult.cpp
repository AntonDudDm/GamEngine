

#include "../include/RayCastResult.h"


RayCastResult::RayCastResult() {

	point = Vector();
	normal = Vector();
	t = -1;
	hit = false;

};

//����� ������� ����� ����� �������� ��������� �����
void RayCastResult::init(Vector Point, Vector Normal, double T, bool Hit) {

	point = Point;
	normal = Normal;
	t = T;
	hit = Hit;

};

//����� ����������� ��������
void RayCastResult::reset(RayCastResult result) {

	if (result != NULL) {
		//TODO: ���������� � ����
	}


};