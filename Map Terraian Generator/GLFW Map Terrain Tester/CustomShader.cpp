#include "CustomShader.h"

CustomShader::CustomShader(const std::string& filename) 
{
	m_filePath = filename;
	m_renderID = 0;


	ShaderProgramSource source = ParseShader(filename);
	m_renderID = CreateShader(source.vertexSource, source.fragmentSource);
}

CustomShader::~CustomShader()
{
	GLCall(glDeleteProgram(m_renderID));
}

void CustomShader::Bind() const
{
	GLCall(glUseProgram(m_renderID));
}

void CustomShader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void CustomShader::SetUniform(const std::string & name, glm::vec4 values)
{
	GLCall(glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w));
}

int CustomShader::GetUniformLocation(const std::string & name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
	{
		return m_uniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_renderID, name.c_str()));

	if (location == -1)
	{
		std::cout << "WARNING: Uniform " << name << " Does not exist" << std::endl;
	}
	
	m_uniformLocationCache[name] = location;
	
	return location;
}

unsigned int CustomShader::CompileShader(unsigned int type, const std::string & source)
{
	GLCall(unsigned int id = glCreateShader(type));

	const char * src = source.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));

	GLCall(glCompileShader(id));

	int resault;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &resault));

	if (resault == GL_FALSE)
	{
		int leangth;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &leangth);
		char * message = (char *)alloca(leangth * sizeof(char));
		glGetShaderInfoLog(id, leangth, &leangth, message);
		std::cout << "Failed To Compile Shader" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragmeant") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}


unsigned int CustomShader::CreateShader(const std::string & vertexShader, const std::string & FragmentShader)
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

ShaderProgramSource CustomShader::ParseShader(const std::string & filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
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