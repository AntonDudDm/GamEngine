
using namespace std;
#include <iostream>

#include "/Users/1/Desktop/Вуз/Programm progect/GitHub/GamEngine/include/Figures.h"


//КРУГ
Circle::Circle(double rad = 0) {
	radius = rad;
}


//AABB =========================--------------------------------------------------------
AABB::AABB() 
{
	size = Vector();
}

AABB::AABB(Vector min, Vector max) 
{
	size = max - min;
}

//Low Left
Vector AABB::getMin()  const
{
	return (body.getPosition() - (size * 0.5));
};


//High Right
Vector AABB::getMax()  const
{
	return (body.getPosition() + (size * 0.5));
};


//BOX2D =========================--------------------------------------------------------
BOX2D::BOX2D()
{
	size = Vector();
}

BOX2D::BOX2D(Vector min, Vector max)
{
	size = max - min;
}

//Low Left
Vector BOX2D::getMin()  const
{
	return (body.getPosition() - (size * 0.5));
};


//High Right
Vector BOX2D::getMax()  const
{
	return (body.getPosition() + (size * 0.5));
};

//four vertices
vector<Vector> BOX2D::getVertices() const 
{
	Vector min = getMin();
	Vector max = getMax();

	vector<Vector> vertices = {

		Vector(min.getX(), min.getY()), Vector(min.getX(), max.getY()),
		Vector(max.getX(), min.getY()), Vector(max.getX(), max.getY())

	};

	if (body.getRotate() != 0) {
		for (int i = 0; i < 4; i++) {

			//TODO: повернуть вектора вокруг центра на угол
			//Math.rotate(vertices[i], body.getPosition(), body.getRotate());
		}
	}

	return vertices;

};



