#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject()
{
	GLCall(glGenVertexArrays(1, &m_renderID));
}


VertexArrayObject::~VertexArrayObject()
{
	GLCall(glDeleteVertexArrays(1, & m_renderID))
}

void VertexArrayObject::AddBuffer(const VertexBuffer & vb, const VertextBufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, 
										element.normalised, layout.GetStride(), (const void *)offset));
		offset += element.count * VertexBufferElemnt::GetSizeOfType(element.type);
	}

}

void VertexArrayObject::Bind() const
{
	GLCall(glBindVertexArray(m_renderID));
}

void VertexArrayObject::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
