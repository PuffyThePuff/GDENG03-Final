#pragma once
#include "AVertexBuffer.h"
class TexturedVertexBuffer : public AVertexBuffer
{
public:
	TexturedVertexBuffer();
	~TexturedVertexBuffer();

	bool load(void* vertex_list, UINT vertex_size, UINT vertex_count, void* shader_byte_code, UINT shader_byte_size) override;
};