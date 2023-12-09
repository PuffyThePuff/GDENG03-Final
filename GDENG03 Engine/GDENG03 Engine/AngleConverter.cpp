#include"AngleConverter.h"
#include<cmath>

float AngleConverter::toRadians(float theta_in_degrees) {
	return theta_in_degrees * acos(0.f) / 90.f;
}

float AngleConverter::toDegrees(float theta_in_radians) {
	return 90.f * theta_in_radians / acos(0.f);
}