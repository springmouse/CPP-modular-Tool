#include "GameManager.h"

#include <stdio.h>
#include <stdlib.h>




GameManager::GameManager()
{
	m_vbo = nullptr;
	m_ibo = nullptr;
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

	//look up vao (vertex array object)
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glBindVertexArray(m_vaoID));

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

	//generate VBO (vertec buffer object)
	m_vbo = new VertexBuffer(verts, sizeof(verts));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0));

	m_ibo = new IndexBuffer(indicies, 6);

	ShaderProgramSource source = ParseShader("Resources/Shaders/Basic.shader");

	shader = CreateShader(source.vertexSource, source.fragmentSource);
	
	GLCall(glUseProgram(shader));

	r = 0.0f;
	g = 1.0f;
	b = 1.0f;

	GLCall(location = glGetUniformLocation(shader, "u_color"));
	ASSERT(location != -1);
	GLCall(glUniform4f(location, r, g, b, 1.0f));

	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
	m_ibo->Unbind();

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

	GLCall(glDeleteProgram(shader));
	glfwTerminate();
}

void GameManager::Renderer()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLCall(glUseProgram(shader));
	GLCall(glUniform4f(location, r, g, b, 1.0f));

	GLCall(glBindVertexArray(m_vaoID));
	m_ibo->Bind();


	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

unsigned int GameManager::CreateShader(const std::string & vertexShader, const std::string & FragmentShader)
{
	GLCall(unsigned int programe = glCreateProgram());

	GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
	GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader));

	GLCall(glAttachShader(programe, vs));
	GLCall(glAttachShader(programe, fs));
	GLCall(glLinkProgram(programe));
	GLCall(glValidateProgram(programe));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return programe;
}

unsigned int GameManager::CompileShader(unsigned int type, const std::string & source)
{
	GLCall(unsigned int id = glCreateShader(type));

	const char * src = source.c_str();

	GLCall(glShaderSource(id, 1, & src, nullptr));

	GLCall(glCompileShader(id));

	int resault;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &resault));

	if (resault == GL_FALSE)
	{
		int leangth;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, & leangth);
		char * message = (char *)alloca(leangth * sizeof(char));
		glGetShaderInfoLog(id, leangth, &leangth, message);
		std::cout << "Failed To Compile Shader" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragmeant") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

ShaderProgramSource GameManager::ParseShader(const std::string & filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT =1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}
