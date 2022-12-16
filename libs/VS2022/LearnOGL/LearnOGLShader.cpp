#include "LearnOGLShader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace OGL
{
	LearnOGLShader::LearnOGLShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath/* = nullptr*/)
		: mID(0)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "Error::Shader::Read: " << e.what() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		
		uint32_t vertex, fragment;
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, CompileType::Vertex);
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, CompileType::Fragment);
		
		uint32_t geometry;
		if (geometryPath)
		{
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			CheckCompileErrors(geometry, CompileType::Geometry);
		}
		
		mID = glCreateProgram();
		glAttachShader(mID, vertex);
		glAttachShader(mID, fragment);
		if (geometryPath)
		{
			glAttachShader(mID, geometry);
		}
		glLinkProgram(mID);
		CheckCompileErrors(mID, CompileType::Program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath)
		{
			glDeleteShader(geometry);
		}
	}

	LearnOGLShader::~LearnOGLShader()
	{
		std::cout << "LearnOGLShader::~LearnOGLShader" << std::endl;
	}

	void LearnOGLShader::Use()
	{
		glUseProgram(mID);
	}

	void LearnOGLShader::SetTexUnit(std::string locStr, uint32_t texUnit) const
	{
		glUniform1i(GetUniformLocation(locStr), texUnit);
	}

	GLuint LearnOGLShader::GetUniformLocation(std::string locStr) const
	{
		GLuint location = glGetUniformLocation(mID, locStr.c_str());
		if (location == INVALID_UNIFORM_LOCATION)
		{
			std::cout << "Warning: Unable to get the location of uniform " << locStr << std::endl;
		}
		return location;
	}

	void LearnOGLShader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(GetUniformLocation(name), (int)value);
	}

	void LearnOGLShader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void LearnOGLShader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void LearnOGLShader::SetVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(GetUniformLocation(name), 1, &value[0]);
	}

	void LearnOGLShader::SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(GetUniformLocation(name), x, y);
	}

	void LearnOGLShader::SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(GetUniformLocation(name), 1, &value[0]);
	}

	void LearnOGLShader::SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(GetUniformLocation(name), x, y, z);
	}

	void LearnOGLShader::SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(GetUniformLocation(name), 1, &value[0]);
	}

	void LearnOGLShader::SetVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(GetUniformLocation(name), x, y, z, w);
	}

	void LearnOGLShader::SetMat2(const std::string& name, const glm::mat2& value) const
	{
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}

	void LearnOGLShader::SetMat3(const std::string& name, const glm::mat3& value) const
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}

	void LearnOGLShader::SetMat4(const std::string& name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}

	void LearnOGLShader::CheckCompileErrors(GLuint shader, CompileType type)
	{
		GLint success;
		GLchar infoLog[1024];
		switch (type)
		{
			case CompileType::Vertex:
			case CompileType::Fragment:
			case CompileType::Geometry:
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
					std::cout << "Error::Shader_Link of type: " << (int)type << "\n" << infoLog << "\n -- --------------------------------------- --" << std::endl;
				}
			}
			break;
			case CompileType::Program:
			{
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
					std::cout << "Error::Shader_compile of type: " << (int)type << "\n" << infoLog << "\n -- --------------------------------------- --" << std::endl;
				}
			}
			break;
		default:
			break;
		}
	}
}