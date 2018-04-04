#pragma once
#include "VertexBuffer.h"
#include "VertextBufferLayout.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	void AddBuffer(const VertexBuffer & vb, const VertextBufferLayout & layout);

private:

};

