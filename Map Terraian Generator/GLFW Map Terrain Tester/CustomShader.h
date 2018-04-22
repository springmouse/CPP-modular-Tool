#pragma once

#include "GL_Calls.h"

#include <vec4.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class CustomShader
{
public:
	CustomShader(const std::string& filename);
	~CustomShader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform(const std::string & name, glm::vec4 values);

private:
	std::string m_filePath;
	unsigned int m_renderID;
	std::unordered_map<std::string, int> m_uniformLocationCache;

	int GetUniformLocation(const std::string & name);

	unsigned int CompileShader(unsigned int type, const std::string & source);
	unsigned int CreateShader(const std::string & vertexShader, const std::string & FragmentShader);
	ShaderProgramSource ParseShader(const std::string & filePath);
};

