#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Render.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h";
#include "VertextBufferLayout.h"
#include "CustomShader.h"

#include "GL_Calls.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();

	void GameLoop();

	void Renderer();
	
private:
	GLFWwindow * m_window;
	
	VertexArrayObject * m_vao;
	VertextBufferLayout * m_vbl;
	VertexBuffer * m_vbo;

	VertexArrayObject * m_vao2;
	VertexBuffer * m_vbo2;

	IndexBuffer * m_ibo;

	CustomShader * m_shader;
	CustomShader * m_shader2;

	Render * m_renderer;

	bool m_running;

	float r, g, b;
	int location;
	float incermeant;
};

