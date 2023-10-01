

using namespace std;
#include <iostream>
#include "../include/IntersectionDetector.h"
#include "../include/Math.h"



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

	//2D ������� �������� ���������� ������� ������ (max) � ������ ����� (min) ����� � ����� �������� ���� ������� ������������ ������ ����.
	//��� ����� ��������� ����� �� ����� ������ �������. �.� �� ��������� ��������� ����� ������������ ��� ���������� �� ���� � �������, �� ��� ����������
	//��������� ����� � �������� ����������� �� �������� ������� � �������� �� ���������� � ������� ���������� ������� (������������) ������ � ������������ min � max

	Vector rotatePoint = point;

	Math::rotate(rotatePoint, -box.getRotate(), box.getPosition());

	return (rotatePoint.getX() <= box.getMax().getX()) && 
		(rotatePoint.getX() >= box.getMin().getX()) && 
		(rotatePoint.getY() <= box.getMax().getY()) && 
		(rotatePoint.getY() >= box.getMin().getY());

};


//������������ �� ����� � �����������
bool IntersectionDetector::LineInCircle(Line line, Circle circle) {

	if ( (IntersectionDetector::PointInCircle(line.getFrom(), circle)) || (IntersectionDetector::PointInCircle(line.getTo(), circle)) ) {

		return true;
	}

	//������ ����� ������� � ������ �����
	Vector ab = line.getTo() - line.getFrom();

	Vector circleCenter = circle.getCenter();

	//������ �� ������ ����� �� ������ �����
	Vector centerToLineStart = circleCenter - line.getFrom();

	//����� �� ��������� ��������� �������� ������� �� ������ ����� �� ������ ����������
	//�� ������ AB � ������ ������� AB
	double part = (centerToLineStart * ab) / (ab * ab);

	if (part < 0.0 || part > 1.0)
		return false;

	//��������� � ������ ����� �����
	Vector ClosesdPoint = line.getFrom() + (ab * part);

	return IntersectionDetector::PointInCircle(ClosesdPoint, circle);

};

