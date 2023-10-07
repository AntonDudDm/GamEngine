

using namespace std;
#include <iostream>
#include "../include/IntersectionDetector.h"
#include "../include/Math.h"



//�������� ����� �� ����� �� �����
bool IntersectionDetector::PointInLine(Vector point, Line line) {

	//��������� ����� kx+b, ������ k ��� ����������� ��� ������� ���� ������

	double dy = line.getTo().getY() - line.getFrom().getY();
	double dx = line.getTo().getX() - line.getFrom().getX();

	//���� ����� ����������� �� �� �� ������ �� 0, ������ ��� �������������� �����
	//����� ������ �������� ���������� ���� � ���� ��� ������� �� ������� ���
	if (dx == 0.0) {
		//���������� �� == � ����� ���������� �.� ����� ���� ������ � ��������� ������
		return Math::Compare(point.getX(), line.getFrom().getX());
	}

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

//������������ �� ������ � ����
bool IntersectionDetector::LineInAABB(Line line, AABB box) {
	if (IntersectionDetector::PointInAABB(line.getFrom(), box), IntersectionDetector::PointInAABB(line.getTo(), box)) {
		return true;
	}

	//������� ��������� ������ ����� ����� � ������� � ������ �����
	Vector unitVector = line.getTo() - line.getFrom();
	unitVector.normalize();
	//unitVector * (1.0 / sqrt(unitVector.LengthSquared()))

	//����� �� ����� ������ �� ��������� ������, ������� ���� ��������� ������� �� 0
	//�.� ������� ���� ��������� � �� ����� ��������, �� ������� ���������� ������ � ��� ������� 0 ������� 0 � ����� �������� �� 0
	unitVector.setX((unitVector.getX() != 0.0) ? (1 / unitVector.getX()) : 0.0);
	unitVector.setY((unitVector.getY() != 0.0) ? (1 / unitVector.getY()) : 0.0);

	//����� �� ����� �������� ���������� �������� ������ �� ������ ����� �� ������� ������ �������
	//� ������� �������� ������ �� ������ ���������� ������� (������� ������ ���������� ������� ������ �
	//��� 2 ������� (�� ���������� 1)
	Vector mini = box.getMin();
	mini = mini - (line.getFrom().mul(unitVector));

	Vector maxi = box.getMax();
	maxi = maxi - (line.getTo().mul(unitVector));

	//������ �� ���� �������������, ��� ��������� �� ������� ���������� ������ �� �������
	//� ����������� � ��������, ������ �� ����� ����������� ����������� �� ������������
	//������� �� ����� � �� ��� � ������� ����� ���������������, ������� ����� ��� ���� ��
	//��� ����� �� ������� � ������ �� ���� �������, ��� ��� �� ���� ��� �� ���������

	//����� �� ����� �������� �� �� ��������� ������������� ������ ��� ���� �� ���
	//���� �� ������� � ������ ����������� ������� �� �� �������� ������� �������

	double tmin = max(min(mini.getX(), maxi.getX()), min(mini.getY(), maxi.getY()));
	double tmax = min(max(mini.getX(), maxi.getX()), max(mini.getY(), maxi.getY()));

	if (tmax < 0 || tmin > tmax)
		return false;

	//�������� ��������������� ����������� ��������� ��������� ������
	double t = (tmin < 0.0) ? tmax : tmin;

	//���� ���� ����������� ������ 0 (�.� �� ���� ����� �����) � ���� ���������� ���������� �� ��������� ������,
	//���� ����� �� ����������� ����� ������ (��� ������ �� ����������� ������ �������� �� ����� �� ����,
	//�� ����� ��������� �������������
	//return t > 0.0 && ((unitVector * t).LengthSquared() < line.lengthSquared());
	return t > 0.0 && (t * t < line.lengthSquared()); //�.� ������ ��������� �� ������� ��� ����� ����� ��������
	//������ ���� ������� ������������ ��� ��������� t

};

//���������� ����������� �������
bool IntersectionDetector::LineInBOX2D(Line line, BOX2D box) {
	double rotation = box.getRotate();
	Vector center = box.getPosition();

	//�������� ����� � ��������� ������������ �������
	Line rotateLine = line;

	//��������� �����
	rotateLine.lineRotate(-rotation, center);

	//������� ������� �� ���������� �������
	AABB aabb(box.getMin(), box.getMax());

	//�������� ����� �� ���������� ������ � ������ �������
	return LineInAABB(rotateLine, aabb);

};

//Raycast

bool IntersectionDetector::RayCast(Circle circle, Ray ray, RayCastResult result) {

	RayCastResult::reset(result);

	//������ ����� ������� ���� � ������� ����������
	Vector originToCircle = circle.getCenter() - ray.getOrigin();

	double radiusSquared = circle.getRadius() * circle.getRadius();
	double originToCircleLengthSquared = originToCircle.LengthSquared();

	//���������� ������ �� ������ ���� �� ������ ���������� �� ����������� ����
	double a = originToCircle * ray.getDirection(); //��������� ������������

	//����� � �������� �� ��������� � ������ ���������� ����� (������� �� ����) �� ������ ����������,
	//�� ������� ��������
	double bSquared = originToCircleLengthSquared - a * a;

	//��� ������ ������ ���������� �� ����� �� ��� �������������� �� ���������� �������
	//� ���� ������ ��� ������� ����� �� ��������� ����� �� ����������� ���� � ����������� 
	//��� ������ ���� �� ������������� ��������.
	if (radiusSquared - bSquared < 0.0) {
		return false;
	}

	//�� ����� ����� �� ��������� �� ������ ���������� ����� �� ����������� ���� � �����������
	double f = sqrt(radiusSquared - bSquared); //����� ��������� �������� �����������
	//���������� ������ ����� ����� ����� ��������, �� ��� ���� �����(((
	//TODO: ��������� ��� ��� �����???? 25 ������ ����������... � 5 ��� ��������

	double t = 0;

	if (originToCircleLengthSquared < radiusSquared) {
		//Ray starts inside of circle (��� ������� �� �����)
		t = a + f;
	}
	else {
		t = a - f;
	}

	//���� ����� �������� ��������� ����������
	if (&result != NULL) {
		//�� �� ������ ������� �������� �� ���������� (�����) ���������� �� ��������� ������ ���������� ����
		//������ � ��������� ����� �� ������� ����������
		Vector point = ray.getOrigin() + (ray.getDirection() * t);
		
		//����� ���������� ������ (������) �� ����� ����� ����
		Vector normal = point - circle.getCenter(); 

		//��������� �������������� ��������� ��������
		result.init(point, normal, t, true);
		
	}	

	return true;
};

