#include "VertexArrayObject.h"

#include "Render.h"


VertexArrayObject::VertexArrayObject()
{
}


VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::AddBuffer(const VertexBuffer & vb, const VertextBufferLayout & layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, e
									lement.normalised ? , sizeof(float) * 2, (void*)0));
	}

}
