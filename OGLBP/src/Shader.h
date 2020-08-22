#pragma once
#include <string>
#include <unordered_map>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_VertFilePath;
	std::string m_FragFilePath;
	unsigned int m_Renderer;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader() {};
	Shader(const std::string& vertexFile, const std::string& FragmentFile);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void GetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void GetUniform3f(const std::string& name, glm::vec3 vecValue);
	void GetUniform3f(const std::string& name, float v0, float v1, float v2);
	void GetUniform1i(const std::string& name, int value);
	void GetUniform1f(const std::string& name, float value);
	void GetUniformMat4f(const std::string& name, glm::mat4& matValue);

private:
	ShaderProgramSource ParseShader(const std::string& vShaderSource, const std::string& fShaderSource);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(const std::string& shader, unsigned int type);
	int GetUniformLoc(const std::string& name);
};
