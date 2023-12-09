#include"Vector4.h"

Vector4::Vector4() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float vector_x, float vector_y, float vector_z, float vector_w) {
	x = vector_x;
	y = vector_y;
	z = vector_z;
	w = vector_w;
}

Vector4::Vector4(const Vector4& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
}

void Vector4::cross(Vector4& v1, Vector4& v2, Vector4& v3) {
	x = (v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v3.y * v2.z));
	y = (v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z)) * -1.f;
	z = (v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y));
	w = (v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y)) * -1.f;
}