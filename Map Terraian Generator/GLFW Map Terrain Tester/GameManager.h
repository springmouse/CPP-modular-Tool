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

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};


class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();

	void GameLoop();

	void Renderer();
	
	static unsigned int CreateShader(const std::string & vertexShader, const std::string & FragmentShader);
	static unsigned int  CompileShader(unsigned int type, const std::string & source);
	static ShaderProgramSource ParseShader(const std::string & filePath);

private:
	GLFWwindow * m_window;

	unsigned int m_vaoID;

	VertexBuffer * m_vbo;
	IndexBuffer * m_ibo;

	unsigned int shader;

	bool m_running;

	float r, g, b;
	int location;
	float incermeant;
};

