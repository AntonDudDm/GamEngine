using namespace std;
#include <iostream>

#include "/Users/1/Desktop/Âóç/Programm progect/GitHub/GamEngine/include/Rigidbody.h"



	Rigidbody::Rigidbody() {
		center = Vector();
		rotate = 0;
	}

	Rigidbody::Rigidbody(Vector Center = Vector(), double rot = 0) {
		center = Center;
		rotate = rot;
	}

	//Center of body
	Vector Rigidbody::getPosition() const{
		return center;
	}

	//
	float Rigidbody::getRotate() const{
		return rotate;
	}


};