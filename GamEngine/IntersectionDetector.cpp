

using namespace std;
#include <iostream>
#include "../include/IntersectionDetector.h"



//�������� ����� �� ����� �� �����
bool IntersectionDetector::PointInLine(Vector point, Line line) {

	//��������� ����� kx+b, ������ k ��� ����������� ��� ������� ���� ������

	double dy = line.getTo().getY() - line.getFrom().getY();
	double dx = line.getTo().getX() - line.getFrom().getX();

	double k = dy / dx;

	//���� ������ ����� ���� ����� ��������� �����������

	double b = line.getTo().getY() - k * line.getTo().getX();

	return point.getY() == k * point.getX() + b;

};

//�������� ����� �� ����� � ����������
bool IntersectionDetector::PointInCircle(Vector point, Circle circle) {

	Vector circleCenter = circle.getCenter();
	Vector centerToPoint = point - circleCenter;

	return centerToPoint.LengthSquared() <= circle.getRadius() * circle.getRadius();

};

//����� � ������������� �������
bool IntersectionDetector::PointInAABB(Vector point, AABB box) {

	return (point.getX() <= box.getMax().getX()) && (point.getX() >= box.getMin().getX()) && (point.getY() <= box.getMax().getY()) && (point.getY() >= box.getMin().getY());

};

//����� � ������� ������� ����� ���� ���������
bool IntersectionDetector::PointInBOX2D(Vector point, BOX2D box) {

	return (point.getX() <= box.getMax().getX()) && (point.getX() >= box.getMin().getX()) && (point.getY() <= box.getMax().getY()) && (point.getY() >= box.getMin().getY());

};

