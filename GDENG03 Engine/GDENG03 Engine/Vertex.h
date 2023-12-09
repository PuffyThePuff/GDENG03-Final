#pragma once
#include"Vector3D.h"

class Vertex
{
public:
	Vertex();
	Vertex(Vector3D vertex_position_0, Vector3D vertex_color_0, Vector3D vertex_color_1);
	~Vertex();

	Vector3D position;
	Vector3D color;
	Vector3D color1;
};