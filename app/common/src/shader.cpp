#include <shader.h>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
//	string prefixStr = string(prefix);
//	string vertexStr = prefixStr + string(vert);
//	string fragmentStr = prefixStr + string(frag);
//	const char* vertexPath = vertexStr.c_str();
//	const char* fragmentPath = fragmentStr.c_str();

	// 1. retrieve the vertex/fragment source code from filePath
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
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
	catch (ifstream::failure e)
	{
		cout << "zykTest Error: Shader files read error!" << endl;
		exit(-1);
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	// 2. compile shaders

	// int success;
	// char infoLog[512];
	// vertex shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	if (vertex == 0)
	{
		cout << "Create Shader Error!" << endl;
		exit(-1);
	}
	cout << "vertex shader reference: " << vertex << endl;
	cout << "glIsShader(vertexShader): " << (int)glIsShader(vertex) << endl;
	cout << "glIsShader(GL_VERTEX_SHADER): " << (int)glIsShader(GL_VERTEX_SHADER) << endl;
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	int success = 0;
	glGetShaderiv(vertex, GL_DELETE_STATUS, &success);
	cout << "GL_DELETE_STATUS: " << success << endl;
	glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &success);
	cout << "INFO_LOG_LENGTH: " << success << endl;
	glGetShaderiv(vertex, GL_SHADER_SOURCE_LENGTH, &success);
	cout << "SHADER_SOURCE_LENGTH: " << success << endl;
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	// glBindAttribLocation(this->ID, 0, "aPos"); // same as 'layout' keyword in vertex shader program
	// glBindAttribLocation(this->ID, 1, "aColor");
	// glBindAttribLocation(this->ID, 2, "aTexCoord");
	// glGetAttribLocation
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glGetShaderiv(vertex, GL_DELETE_STATUS, &success);
	cout << "after call glDeleteShader, GL_DELETE_STATUS: " << success << endl;
}
// activate the shader
// ------------------------------------------------------------------------
void Shader::use()
{
	glUseProgram(this->ID);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const string &name, float value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::set4Float(const string &name, float value1, float value2, float value3, float value4) const
{
	glUniform4f(glGetUniformLocation(this->ID, name.c_str()), value1, value2, value3, value4);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const string &name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
// ------------------------------------------------------------------------
void Shader::setVec4(const string &name, glm::vec4 value) const
{
	glUniform4fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
// ------------------------------------------------------------------------
void Shader::setMat4fv(const string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
// ------------------------------------------------------------------------
void Shader::setMat4(const string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			cout << "zykTest: Shader compile with error of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			exit(-2);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			cout << "zykTest: Shader compile with error of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			exit(-2);
		}
	}
}
