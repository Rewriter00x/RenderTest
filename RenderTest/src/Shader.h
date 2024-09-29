#pragma once

#include <string>
#include <unordered_map>

#include "RenderObjectBase.h"

#include "glm/glm.hpp"

class Shader : public RenderObjectBase
{
public:
	Shader(const std::string& filepath);
	~Shader();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform4f(const std::string& name, float v[4]) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

private:
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	static ShaderProgramSource ParseShader(const std::string& filepath);
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name) const;

	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	
#if _DEBUG
	std::string m_Filepath;
#endif
};
