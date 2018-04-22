#include "Render.h"
#include <iostream>

void Render::Draw(const VertexArrayObject & vao, const IndexBuffer & ib, const CustomShader & shader)
{
	shader.Bind();
	vao.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
