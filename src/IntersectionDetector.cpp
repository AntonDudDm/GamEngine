

using namespace std;
#include <iostream>
#include "../include/IntersectionDetector.h"
#include "../include/Math.h"



//Проверка лежит ли точка на линии
bool IntersectionDetector::PointInLine(Vector point, Line line) {

	//уравнение линии kx+b, найдем k как производную или тангенс если угодно

	double dy = line.getTo().getY() - line.getFrom().getY();
	double dx = line.getTo().getX() - line.getFrom().getX();

	//Если линия вертикальна то мы бы делили на 0, значит при вертикальности линии
	//нужно просто сравнить координаты икса и если они совпали то вернуть тру
	if (dx == 0.0) {
		//пользуемся не == а своим сравнением т.к могут быть ошибки с плавающей точкой
		return Math::Compare(point.getX(), line.getFrom().getX());
	}

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

	//2D коробка задается положением верхней правой (max) и нижней левой (min) точек и углом поворота этой коробки относительно центра тела.
	//нам нужно проверить лежит ли точка внутри коробки. Т.к мы проверяем положение точки относительно уже повернутой на угол А коробки, то нам достаточно
	//повернуть точку в обратном направлении от поворота коробки и сравнить ее координаты с плоским положением коробки (неповернутым) точнее с координатами min и max

	Vector rotatePoint = point;

	Math::rotate(rotatePoint, -box.getRotate(), box.getPosition());

	return (rotatePoint.getX() <= box.getMax().getX()) && 
		(rotatePoint.getX() >= box.getMin().getX()) && 
		(rotatePoint.getY() <= box.getMax().getY()) && 
		(rotatePoint.getY() >= box.getMin().getY());

};


//Пересекается ли линия и окружнность
bool IntersectionDetector::LineInCircle(Line line, Circle circle) {

	if ( (IntersectionDetector::PointInCircle(line.getFrom(), circle)) || (IntersectionDetector::PointInCircle(line.getTo(), circle)) ) {

		return true;
	}

	//вектор между началом и концом линии
	Vector ab = line.getTo() - line.getFrom();

	Vector circleCenter = circle.getCenter();

	//вектор от начала линии до центра круга
	Vector centerToLineStart = circleCenter - line.getFrom();

	//Здесь мы вычисляем отношение проекции вектора от начала линии до центра окружности
	//на вектор AB к самому вектору AB
	double part = (centerToLineStart * ab) / (ab * ab);

	if (part < 0.0 || part > 1.0)
		return false;

	//Ближайщая к центру круга точка
	Vector ClosesdPoint = line.getFrom() + (ab * part);

	return IntersectionDetector::PointInCircle(ClosesdPoint, circle);

};

//Пересекается ли линиия и ААВВ
bool IntersectionDetector::LineInAABB(Line line, AABB box) {
	if (IntersectionDetector::PointInAABB(line.getFrom(), box), IntersectionDetector::PointInAABB(line.getTo(), box)) {
		return true;
	}

	//создаем еденичный вектор вдоль линии с началом в начале линии
	Vector unitVector = line.getTo() - line.getFrom();
	unitVector.normalize();
	//unitVector * (1.0 / sqrt(unitVector.LengthSquared()))

	//далее мы будем делить на еденичный вектор, поэтому надо проверить деление на 0
	//т.е деление хуже умножения и мы будем умножать, то заранее перевернем вектор а при наличии 0 оставим 0 и будем умножать на 0
	unitVector.setX((unitVector.getX() != 0.0) ? (1 / unitVector.getX()) : 0.0);
	unitVector.setY((unitVector.getY() != 0.0) ? (1 / unitVector.getY()) : 0.0);

	//здесь мы хотим получить разложение векторов идущих от начала линии до крайних левого нижнего
	//и правого верхнего уголов по базису еденичного вектора (сколько частей еденичного вектора влезет в
	//эти 2 вектора (СМ ПРИЛОЖЕНИЕ 1)
	Vector mini = box.getMin();
	mini = mini - (line.getFrom().mul(unitVector));

	Vector maxi = box.getMax();
	maxi = maxi - (line.getTo().mul(unitVector));

	//теперь мы ищем коэффифциенты, при умножение на которые еденичного вктора мы попадем
	//в пересечение с коробкой, точнее мы берем минимальный коэффициент их максимумувом
	//сдвигов по игрек и по икс в стороны краев прямоугольнника, минимум потом что один их
	//них лежит на коробке а второй на краю коробки, тот что на краю нам не интересен

	//далее мы берем максимум из из минимумов коэффициентов потому что один из них
	//лежи на коробке а второй коэффициент выводит на на обратную границу коробки

	double tmin = max(min(mini.getX(), maxi.getX()), min(mini.getY(), maxi.getY()));
	double tmax = min(max(mini.getX(), maxi.getX()), max(mini.getY(), maxi.getY()));

	if (tmax < 0 || tmin > tmax)
		return false;

	//выбираем неотрицательный коэффициент умножения едениного вектор
	double t = (tmin < 0.0) ? tmax : tmin;

	//если этот коэффициент больше 0 (т.е мы едем вдоль линии) и этот коэффциент умноженный на еденичный вектор,
	//дает длину не привышающую длину прямой (что прямая не закончилась внутри квадрата не выйдя из него,
	//то линия пересекла прямоугольник
	//return t > 0.0 && ((unitVector * t).LengthSquared() < line.lengthSquared());
	return t > 0.0 && (t * t < line.lengthSquared()); //т.е вектор еденичный то квадрат его длины можно получить
	//просто взяв квадрат коэффициента его удлинения t

};

//пересекаем наклоненную коробку
bool IntersectionDetector::LineInBOX2D(Line line, BOX2D box) {
	double rotation = box.getRotate();
	Vector center = box.getPosition();

	//повернем линию в локальном пространстве коробки
	Line rotateLine = line;

	//повернули линию
	rotateLine.lineRotate(-rotation, center);

	//создали коробку из повернутой коробки
	AABB aabb(box.getMin(), box.getMax());

	//прверили лежит ли повернутая линиия в прямой коробке
	return LineInAABB(rotateLine, aabb);

};

//Raycast

bool IntersectionDetector::RayCast(Circle circle, Ray ray, RayCastResult result) {

	RayCastResult::reset(result);

	//вектор между началом луча и центром окружности
	Vector originToCircle = circle.getCenter() - ray.getOrigin();

	double radiusSquared = circle.getRadius() * circle.getRadius();
	double originToCircleLengthSquared = originToCircle.LengthSquared();

	//Проецируем веетор из начала луча до центра окружности на направление луча
	double a = originToCircle * ray.getDirection(); //скалярное произведение

	//Длина в квадрате от ближайщей к центру окружности точки (лежащей на луче) до центра окружности,
	//по теореме Пифагора
	double bSquared = originToCircleLengthSquared - a * a;

	//Ели радикс короче расстояния до точки то луч гарантированно не пересекает предмет
	//в этом случае при расчете длины от ближайщей точки до пересечения луча с окружностью 
	//под корнем было бы отрицательное значение.
	if (radiusSquared - bSquared < 0.0) {
		return false;
	}

	//та самая длина от ближайщей до центра окружности точки до пересечения луча с окружностью
	double f = sqrt(radiusSquared - bSquared); //самая затратная операция рэйкастинга
	//квадартный корень берет очень много мощности, но без него никак(((
	//TODO: придумать как без корня???? 25 циклов процессора... в 5 раз медленне

	double t = 0;

	if (originToCircleLengthSquared < radiusSquared) {
		//Ray starts inside of circle (луч полетел из сферы)
		t = a + f;
	}
	else {
		t = a - f;
	}

	//если нужно записать результат записываем
	if (&result != NULL) {
		//мы от начала вектора скакнули на коэффицент (длину) умноженную на еденичный вектор напрвления луча
		//точнее в точкности дошли до границы окружности
		Vector point = ray.getOrigin() + (ray.getDirection() * t);
		
		//берем нормальный вектор (радиус) из точки удара луча
		Vector normal = point - circle.getCenter(); 

		//врезались инициализируем результат рэйкаста
		result.init(point, normal, t, true);
		
	}	

	return true;
};

