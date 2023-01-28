#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLDefine.h"

#include <string>

namespace OGL
{
	class LearnOGLShader
	{
	public:
		LearnOGLShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		~LearnOGLShader();
	
		void Use();

		void SetTexUnit(std::string locStr, uint32_t texUni) const;

		void SetBool(const std::string &name, bool value) const;

		void SetInt(const std::string &name, int value) const;

		void SetFloat(const std::string &name, float value) const;

		void SetVec2(const std::string &name, const glm::vec2 &value) const;
	
		void SetVec2(const std::string &name, float x, float y) const;

		void SetVec3(const std::string &name, const glm::vec3 &value) const;
	
		void SetVec3(const std::string &name, float x, float y, float z) const;

		void SetVec4(const std::string& name, const glm::vec4& value) const;
	
		void SetVec4(const std::string &name, float x, float y, float z, float w) const;

		void SetMat2(const std::string &name, const glm::mat2 &value) const;

		void SetMat3(const std::string &name, const glm::mat3 &value) const;

		void SetMat4(const std::string &name, const glm::mat4 &value) const;

		GLuint GetUniformLocation(std::string locName) const;

		GLuint GetAttribID(std::string locName) const;

	public:
		GLuint mID{ 0 };

	private:
		void CheckCompileErrors(GLuint shader, CompileType type);

	};
}

