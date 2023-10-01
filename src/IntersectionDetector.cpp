

using namespace std;
#include <iostream>
#include "../include/IntersectionDetector.h"
#include "../include/Math.h"



//ѕроверка лежит ли точка на линии
bool IntersectionDetector::PointInLine(Vector point, Line line) {

	//уравнение линии kx+b, найдем k как производную или тангенс если угодно

	double dy = line.getTo().getY() - line.getFrom().getY();
	double dx = line.getTo().getX() - line.getFrom().getX();

	double k = dy / dx;

	//зна€ тангес можно леко найти свободный коэффициент

	double b = line.getTo().getY() - k * line.getTo().getX();

	return point.getY() == k * point.getX() + b;

};

//ѕроверка лежит ли точка в окружности
bool IntersectionDetector::PointInCircle(Vector point, Circle circle) {

	Vector circleCenter = circle.getCenter();
	Vector centerToPoint = point - circleCenter;

	return centerToPoint.LengthSquared() <= circle.getRadius() * circle.getRadius();

};

//“очка в пр€моугольной коробке
bool IntersectionDetector::PointInAABB(Vector point, AABB box) {

	return (point.getX() <= box.getMax().getX()) && (point.getX() >= box.getMin().getX()) && (point.getY() <= box.getMax().getY()) && (point.getY() >= box.getMin().getY());

};

//“очка в коробке котора€ может быть повернута
bool IntersectionDetector::PointInBOX2D(Vector point, BOX2D box) {

	//2D коробка задаетс€ положением верхней правой (max) и нижней левой (min) точек и углом поворота этой коробки относительно центра тела.
	//нам нужно проверить лежит ли точка внутри коробки. “.к мы провер€ем положение точки относительно уже повернутой на угол ј коробки, то нам достаточно
	//повернуть точку в обратном направлении от поворота коробки и сравнить ее координаты с плоским положением коробки (неповернутым) точнее с координатами min и max

	Vector rotatePoint = point;

	Math::rotate(rotatePoint, -box.getRotate(), box.getPosition());

	return (rotatePoint.getX() <= box.getMax().getX()) && 
		(rotatePoint.getX() >= box.getMin().getX()) && 
		(rotatePoint.getY() <= box.getMax().getY()) && 
		(rotatePoint.getY() >= box.getMin().getY());

};


//ѕересекаетс€ ли точка и окружнность
bool IntersectionDetector::LineInCircle(Line line, Circle circle) {

	if ( (IntersectionDetector::PointInCircle(line.getFrom(), circle)) || (IntersectionDetector::PointInCircle(line.getTo(), circle)) ) {

		return true;
	}

	//вектор между началом и концом линии
	Vector ab = line.getTo() - line.getFrom();

	Vector circleCenter = circle.getCenter();

	//вектор от начала линии до центра круга
	Vector centerToLineStart = circleCenter - line.getFrom();

	//«десь мы вычисл€ем отношение проекции вектора от начала линии до центра окружности
	//на вектор AB к самому вектору AB
	double part = (centerToLineStart * ab) / (ab * ab);

	if (part < 0.0 || part > 1.0)
		return false;

	//Ѕлижайща€ к центру круга точка
	Vector ClosesdPoint = line.getFrom() + (ab * part);

	return IntersectionDetector::PointInCircle(ClosesdPoint, circle);

};

