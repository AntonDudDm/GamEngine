
using namespace std;

#include "../include/Ray.h"

Ray::Ray(Vector Origin, Vector Direction) {
	origin = Origin;
	direction = Direction;

	direction = direction.normalize();
};

Vector Ray::getOrigin() const{
	return origin;
};

Vector Ray::getDirection() const {
	return direction;
}