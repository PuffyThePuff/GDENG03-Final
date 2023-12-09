#pragma once

class Vector4
{
public:
	Vector4();
	Vector4(float vector_x, float vector_y, float vector_z, float vector_w);
	Vector4(const Vector4& vector);
	~Vector4() {}

	void cross(Vector4& v1, Vector4& v2, Vector4& v3);

	float x;
	float y;
	float z;
	float w;
};