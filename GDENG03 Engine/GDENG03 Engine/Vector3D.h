#pragma once

class Vector3D
{
public:
	Vector3D();
	Vector3D(float vector_x, float vector_y, float vector_z);
	Vector3D(const Vector3D& vector);
	~Vector3D() {}

	static Vector3D lerp(const Vector3D& vector_a, const Vector3D& vector_b, float coefficient);

	void operator =(const Vector3D& vector);
	void operator +=(const Vector3D& vector);
	Vector3D operator +(Vector3D vector);
	Vector3D operator *(float scalar);

	float x;
	float y;
	float z;
};