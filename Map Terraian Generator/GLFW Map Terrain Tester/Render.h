#pragma once

#include "VertexArrayObject.h"
#include "IndexBuffer.h"
#include "CustomShader.h"

#include <GL/glew.h>

#include <string>

class Render
{
public:
	Render() {};
	~Render() {};

	void Draw(const VertexArrayObject& vao, const IndexBuffer& ib, const CustomShader& shader);

};