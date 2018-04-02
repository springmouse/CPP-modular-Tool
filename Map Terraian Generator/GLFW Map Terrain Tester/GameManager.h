#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


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

	GLuint m_vaoID;
	GLuint vboID;
		

	bool m_running;
};

