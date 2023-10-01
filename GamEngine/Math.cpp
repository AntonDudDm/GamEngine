

#include "Math.h"

double Math::toRadians(double angle) {

	return angle * M_PI;
};

void Math::rotate(Vector vector, double AngleDegree, Vector origin) 
{
	//transfer vector in (0;0)
	double x = vector.getX() - origin.getX();
	double y = vector.getY() - origin.getY();

	double Cos = cos(toRadians(AngleDegree));
	double Sin = sin(toRadians(AngleDegree));

	//ѕовернули матрицей поворота
	double xPrime = (x * Cos) - (y * Sin);
	double yPrime = (x * Cos) + (y * Sin);

	//переместили обратно
	xPrime += origin.getX();
	yPrime += origin.getY();

	//»зменили координаты но новые - повернутые
	vector.setX(xPrime);
	vector.setY(yPrime);
};

//нужно переопредилить сравнение т.к машинный эпсилон может давать ошибки при сравнении

bool Math::Compare(double x, double y, double epsilon = _EPSILON) {
	return abs(x - y) <= epsilon * max(1.0, max(abs(x), abs(y)));
};

bool Math::Compare(Vector vec1, Vector vec2, double epsilon = _EPSILON) {
	return Compare(vec1.getX(), vec2.getX(), epsilon) && Compare(vec1.getY(), vec2.getY(), epsilon);
}