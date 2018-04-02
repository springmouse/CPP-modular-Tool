#include "GameManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{

	if (glfwInit() == false)
	{
		//did not succed init glfw
		fprintf(stderr, "GLFW Failed to initialise");
	}

	//4 AA
	//glfwWindowHint(GLFW_SAMPLES, 8);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(640, 480, "Main GL Window", NULL, NULL);

	if (!m_window)
	{
		fprintf(stderr, "GLFW Window Failed to Init");
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "GLEW Failed to Init");
		glfwTerminate();
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//look up vao (vertex array object)
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	static const GLfloat verts[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f,	0.0f
	};

	//generate VBO (vertec buffer object)
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

}

void GameManager::GameLoop()
{

	while (glfwWindowShouldClose(m_window) == false)
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		Renderer();

		glDisableVertexAttribArray(0);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void GameManager::Renderer()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
