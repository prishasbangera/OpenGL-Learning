#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define BUF_SIZE (1024)

class Shader
{
private:
	char infoLog[BUF_SIZE];
	unsigned int compileSingleShader(GLenum type, const char *code) {
		// Compile
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &code, NULL);
		glCompileShader(shader);
		// Check
		checkCompileErrors(shader, std::to_string(type));
		return shader;
	}
	
	void compileShaderProgram(const char *vShadercode, const char *fShadercode) {
		unsigned int vertexShader = compileSingleShader(GL_VERTEX_SHADER, vShadercode);
		unsigned int fragmentShader = compileSingleShader(GL_FRAGMENT_SHADER, fShadercode);


		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	/// <summary>
	/// Tool to check shader compilation or linking errors
	/// Pass in shader and its type
	/// </summary>
	/// <param name="shader"></param>
	/// <param name="type"></param>
	void checkCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[BUF_SIZE];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, BUF_SIZE, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, BUF_SIZE, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;

			}
		}

	}
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) {

		// open files
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			// read file's buffer contents into streams
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		
		// compile
		compileShaderProgram(vertexCode.c_str(), fragmentCode.c_str());

	}


	void use() {
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
};
#endif

