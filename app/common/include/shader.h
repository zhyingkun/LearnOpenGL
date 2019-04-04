#ifndef SHADER_H
#define SHADER_H

#include <iostream>
using namespace std;

#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
  public:
	GLuint ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(const char *vertexPath, const char *fragmentPath);
	// activate the shader
	// ------------------------------------------------------------------------
	void use();
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const string &name, bool value) const;
	// ------------------------------------------------------------------------
	void setInt(const string &name, int value) const;
	// ------------------------------------------------------------------------
	void setFloat(const string &name, float value) const;
	// ------------------------------------------------------------------------
	void set4Float(const string &name, float value1, float value2, float value3, float value4) const;
	// ------------------------------------------------------------------------
	void setVec3(const string &name, glm::vec3 value) const;
	// ------------------------------------------------------------------------
	void setVec4(const string &name, glm::vec4 value) const;
	// ------------------------------------------------------------------------
	void setMat4fv(const string &name, glm::mat4 value) const;
	// ------------------------------------------------------------------------
	void setMat4(const string &name, const glm::mat4 &mat) const;

  private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, string type);
};

#endif // SHADER_H
