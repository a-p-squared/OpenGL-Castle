#pragma once

#include<glew.h>

#include<iostream>
#include<fstream>
#include<sstream>

#include<glm.hpp>

using namespace std;

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexPath, const char* fragmentPath)
	{
		string vertexCode;
		string fragmentCode;
		ifstream vertexFile;
		ifstream fragmentFile;

		vertexFile.exceptions(ifstream::failbit | ifstream::badbit);
		fragmentFile.exceptions(ifstream::failbit | ifstream::badbit);

		try
		{
			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);

			stringstream vshaderstream, fshaderstream;

			vshaderstream << vertexFile.rdbuf();
			fshaderstream << fragmentFile.rdbuf();

			vertexFile.close();
			fragmentFile.close();

			vertexCode = vshaderstream.str();
			fragmentCode = fshaderstream.str();
		}
		catch (ifstream::failure e)
		{
			cout << "ERROR: SHADER FILE READ FAILED" << endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		GLint vertexShader, fragmentShader;
		int success;
		char infoLog[512];

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			cout << "ERROR: VERTEX SHADER COMPILATION FAILED" << endl;
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			cout << infoLog << endl;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED" << endl;
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			cout << infoLog << endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			cout << "ERROR: PROGRAM LINKING FAILED" << endl;
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << infoLog << endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use()
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Delete()
	{
		glDeleteProgram(ID);
	}
};