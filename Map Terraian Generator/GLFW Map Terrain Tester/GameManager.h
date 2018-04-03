#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

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

	static void GLClearError();
	static bool GLLogCall(const char * function, const char* file, int line);

	static unsigned int CreateShader(const std::string & vertexShader, const std::string & FragmentShader);
	static unsigned int  CompileShader(unsigned int type, const std::string & source);
	static ShaderProgramSource ParseShader(const std::string & filePath);

private:
	GLFWwindow * m_window;

	GLuint m_vaoID;
	GLuint vboID;
	unsigned int ibo;
		
	unsigned int shader;

	bool m_running;

	float r, g, b;
	int location;
	float incermeant;
};


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GameManager::GLClearError();\
	x;\
	ASSERT(GameManager::GLLogCall(#x, __FILE__, __LINE__));