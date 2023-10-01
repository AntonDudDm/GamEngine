

using namespace std;
#include <iostream>
#include "../include/IntersectionDetector.h"



//Проверка лежит ли точка на линии
bool IntersectionDetector::PointInLine(Vector point, Line line) {

	//уравнение линии kx+b, найдем k как производную или тангенс если угодно

	double dy = line.getTo().getY() - line.getFrom().getY();
	double dx = line.getTo().getX() - line.getFrom().getX();

	double k = dy / dx;

	//зная тангес можно леко найти свободный коэффициент

	double b = line.getTo().getY() - k * line.getTo().getX();

	return point.getY() == k * point.getX() + b;

};

//Проверка лежит ли точка в окружности
bool IntersectionDetector::PointInCircle(Vector point, Circle circle) {

	Vector circleCenter = circle.getCenter();
	Vector centerToPoint = point - circleCenter;

	return centerToPoint.LengthSquared() <= circle.getRadius() * circle.getRadius();

};

//Точка в прямоугольной коробке
bool IntersectionDetector::PointInAABB(Vector point, AABB box) {

	return (point.getX() <= box.getMax().getX()) && (point.getX() >= box.getMin().getX()) && (point.getY() <= box.getMax().getY()) && (point.getY() >= box.getMin().getY());

};

//Точка в коробке которая может быть повернута
bool IntersectionDetector::PointInBOX2D(Vector point, BOX2D box) {

	return (point.getX() <= box.getMax().getX()) && (point.getX() >= box.getMin().getX()) && (point.getY() <= box.getMax().getY()) && (point.getY() >= box.getMin().getY());

};

