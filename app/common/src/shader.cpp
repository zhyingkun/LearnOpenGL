#include <shader.h>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		exit(-1);
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// int success;
	// char infoLog[512];
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	if (vertex == 0)
	{
		std::cout << "Create Shader Error!" << std::endl;
		exit(-1);
	}
	else
	{
		std::cout << "vertex shader reference: " << vertex << std::endl;
		std::cout << "glIsShader(vertexShader): " << (int)glIsShader(vertex) << std::endl;
		std::cout << "glIsShader(GL_VERTEX_SHADER): " << (int)glIsShader(GL_VERTEX_SHADER) << std::endl;
	}
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	int success = 0;
	glGetShaderiv(vertex, GL_DELETE_STATUS, &success);
	std::cout << "GL_DELETE_STATUS: " << success << std::endl;
	glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &success);
	std::cout << "INFO_LOG_LENGTH: " << success << std::endl;
	glGetShaderiv(vertex, GL_SHADER_SOURCE_LENGTH, &success);
	std::cout << "SHADER_SOURCE_LENGTH: " << success << std::endl;
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glGetShaderiv(vertex, GL_DELETE_STATUS, &success);
	std::cout << "after call glDeleteShader, GL_DELETE_STATUS: " << success << std::endl;
}
// activate the shader
// ------------------------------------------------------------------------
void Shader::use()
{
	glUseProgram(ID);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::set4Float(const std::string &name, float value1, float value2, float value3, float value4) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}
// ------------------------------------------------------------------------
void Shader::setMat4fv(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			exit(-2);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			exit(-2);
		}
	}
}
