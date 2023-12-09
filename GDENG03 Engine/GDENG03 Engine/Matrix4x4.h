#pragma once
#include<memory>
#include"Vector3D.h"
#include"Vector4.h"

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	void setIdentity();
	void setTranslation(float delta_x, float delta_y, float delta_z);
	void setTranslation(const Vector3D& translate_vector);
	void setScale(float factor_x, float factor_y, float factor_z);
	void setScale(const Vector3D& scale_vector);
	void setRotationX(float theta);
	void setRotationY(float theta);
	void setRotationZ(float theta);
	void setOrthographicProjection(float width, float height, float near_plane, float far_plane);
	void setPerspectiveProjection(float field_of_view, float aspect, float near_plane, float far_plane);

	void translate(float delta_x, float delta_y, float delta_z);
	void translate(const Vector3D& translate_vector);
	void scale(float factor_x, float factor_y, float factor_z);
	void scale(const Vector3D& scale_vector);
	void rotate(int axis, float theta);

	void operator *=(const Matrix4x4& matrix);
	void setMatrix(const Matrix4x4& matrix);

	float* getMatrix();
	Vector3D getRightVector();
	Vector3D getUpVector();
	Vector3D getForwardVector();
	Vector3D getTranslation();
	float getDeterminant();
	void inverse();

	float mMatrix[4][4] = {};
};