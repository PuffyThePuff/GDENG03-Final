#include "Vertex.h"

Vertex::Vertex() {
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color.x = 0;
	color.y = 0;
	color.z = 0;

	color1.x = 0;
	color1.y = 0;
	color1.z = 0;
}

Vertex::Vertex(Vector3D vertex_position_0, Vector3D vertex_color_0, Vector3D vertex_color_1) {
	position.x = vertex_position_0.x;
	position.y = vertex_position_0.y;
	position.z = vertex_position_0.z;

	color.x = vertex_color_0.x;
	color.y = vertex_color_0.y;
	color.z = vertex_color_0.z;

	color1.x = vertex_color_1.x;
	color1.y = vertex_color_1.y;
	color1.z = vertex_color_1.z;
}

Vertex::~Vertex() {}