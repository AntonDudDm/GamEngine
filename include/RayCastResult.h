#pragma once

#ifndef _RAYCASTRESULT
#define _RAYCASTRESULT

#include "../include/Vector.hpp"


class RayCastResult {

private:

	//Точка пересечения с луча с объектом
	Vector point;
	//нормаль отражения луча от объекта
	Vector normal;
	//переменная отвечающая за расстояние от точки испускания луча до объекта
	double t;
	//логическая переменная попал ли дуч по объекту или нет
	bool hit;

public:

	RayCastResult();

	//после каждого каста нужно обновить результат каста
	void init(Vector Point, Vector Normal, double T, bool Hit);

	//сброс результатов рейкаста
	static void reset(RayCastResult result);


};


#endif // !_RAYCASTRESULT
