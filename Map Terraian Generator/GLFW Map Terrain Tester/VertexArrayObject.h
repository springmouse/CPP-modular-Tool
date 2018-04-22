#pragma once
#include "VertexBuffer.h"
#include "VertextBufferLayout.h"

#include "GL_Calls.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	void AddBuffer(const VertexBuffer & vb, const VertextBufferLayout & layout);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_renderID;
};

