#include "GameManager.h"

#include <stdio.h>
#include <stdlib.h>




GameManager::GameManager()
{
	m_vbo = nullptr;
	m_ibo = nullptr;
	m_vao = nullptr;
	m_vbl = nullptr;
	m_shader = nullptr;

	m_vbo2 = nullptr;
	m_vao2 = nullptr;
	m_shader2 = nullptr;

	m_renderer = new Render();
}


GameManager::~GameManager()
{
	delete(m_vbo);
	delete(m_ibo);
	delete(m_vao);
	delete(m_vbl);

	delete(m_shader);
	delete(m_renderer);

	delete(m_vao2);
	delete(m_vbo2);
}

void GameManager::Init()
{

	if (glfwInit() == false)
	{
		//did not succed init glfw
		fprintf(stderr, "GLFW Failed to initialise");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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


	static const GLfloat verts[] = 
	{
		-0.5f, -0.5f,	//0
		0.5f, -0.5f,	//1
		0.5f, 0.5f,		//2
		-0.5f, 0.5f,	//3
	};

	unsigned int indicies[] =
	{
		0,1,2,
		2,3,0
	};

	static const GLfloat verts2[] =
	{
		0.75, -0.5f,	//0
		0.95f, -0.5f,	//1
		0.95f, 0.5f,		//2
		0.75f, 0.5f,	//3
	};

	m_vao = new VertexArrayObject();
	m_vbo = new VertexBuffer(verts, sizeof(verts));
	m_vbl = new VertextBufferLayout();


	m_vbl->Push<float>(2);
	m_vao->AddBuffer(*m_vbo, *m_vbl);

	m_vao2 = new VertexArrayObject();
	m_vbo2 = new VertexBuffer(verts2, sizeof(verts2));
	m_vao2->AddBuffer(*m_vbo2, *m_vbl);

	m_ibo = new IndexBuffer(indicies, 6);

	//implameant shader here
	m_shader = new CustomShader("Resources/Shaders/Basic.shader");
	m_shader->Bind();
	m_shader->SetUniform("u_color", glm::vec4(0.8f, 0.3f, 0.8f, 1.0f));

	m_shader2 = new CustomShader("Resources/Shaders/Basic2.shader");
	m_shader2->Bind();
	m_shader2->SetUniform("u_color", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	r = 0.0f;
	g = 1.0f;
	b = 1.0f;

	m_vao->Unbind();
	m_vbo->Unbind();
	m_ibo->Unbind();
	m_shader->Unbind();

	m_vao2->Unbind();
	m_vbo2->Unbind();
	m_shader2->Unbind();
}

void GameManager::GameLoop()
{
	while (glfwWindowShouldClose(m_window) == false)
	{

		Renderer();

		if (r >= 1.0f)
		{
			incermeant = -0.05f;
		}
		else if (r <= 0.0f)
		{
			incermeant = 0.05f;
		}
		
		r += incermeant;

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void GameManager::Renderer()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->Bind();
	m_shader->SetUniform("u_color", glm::vec4(r, g, b, 1.0f));
	
	m_renderer->Draw(*m_vao, *m_ibo, *m_shader);
	m_renderer->Draw(*m_vao2, *m_ibo, *m_shader2);
}


