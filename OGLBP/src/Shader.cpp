#include "Shader.h"
#include<glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "ErrorHandling.h"

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
	: m_VertFilePath(vertexFile), m_FragFilePath(fragmentFile), m_Renderer(0)
{
	ShaderProgramSource source = ParseShader(vertexFile, fragmentFile);
	m_Renderer = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_Renderer));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

ShaderProgramSource Shader::ParseShader(const std::string& vShaderSource, const std::string& fShaderSource) {
	std::ifstream vertStream(vShaderSource);
	std::ifstream fragStream(fShaderSource);

	std::stringstream vertShader, fragShader;
	std::string line;
	
	while (getline(vertStream, line)) {
		vertShader << line << "\n";
	}
	while (getline(fragStream, line)) {
		fragShader << line << "\n";
	}

	return { vertShader.str(), fragShader.str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
	
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));

	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

unsigned int Shader::CompileShader(const std::string& shader, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = shader.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	return id;
}

void Shader::GetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLoc(name), v0, v1, v2, v3));
}

void Shader::GetUniform3f(const std::string& name, glm::vec3 vecValue)
{
	GLCall(glUniform3f(GetUniformLoc(name), vecValue.x, vecValue.y, vecValue.z));
}

void Shader::GetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLoc(name), v0, v1, v2));
}

void Shader::GetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLoc(name), value));
}

void Shader::GetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLoc(name), value));
}

void Shader::GetUniformMat4f(const std::string& name, glm::mat4& matValue)
{
	GLCall(glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &matValue[0][0]));
}

int Shader::GetUniformLoc(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}
	GLCall(int location = glGetUniformLocation(m_Renderer, name.c_str()));
	m_UniformLocationCache[name] = location;
	return location;
}
