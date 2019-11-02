#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include <camera.h>
#include <shader.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

typedef unsigned int GLObject;

class LightingApp {
private:
  GLFWwindow* mainWin;
  Shader* boxShader;
  Shader* lightShader;

  GLObject textureContainer2;
  GLObject textureContainer2Specular;

  GLObject boxVAO;
  GLObject boxVertexVBO;
  GLObject boxNormalVBO;
  GLObject boxTexCoordVBO;
  GLObject boxEBO;

  Camera* camera;
  float lastX;
  float lastY;
  bool firstMouse;

  float deltaTime;
  float lastFrame; // Last Frame Time

  vec3 lightPosition;
  mat4 lightModel;

public:
  LightingApp(/* args */);
  ~LightingApp();

  void InitializeGLFW();
  void CreateWinAndSetWinCallback(const char* winName);
  void LoadOpenGLFunctions();
  void BuildAndCompileBoxShader(const char* vertexPath, const char* fragmentPath);
  void BuildAndCompileLightShader(const char* vertexPath, const char* fragmentPath);
  void LoadAllTextures(const char* containerPath, const char* awesomeFacePath);
  void SetTexturesToBoxShader();
  void ConfigOpenGLUtil();
  void CreateVertexArrayObject();
  void RenderLoop();
  void Terminate();

  GLObject CreateVertexBufferObject(GLsizeiptr size, const void* vertices);
  GLObject CreateElementBufferObject(GLsizeiptr size, const void* indices);
  GLObject CreateTexture(const char* imagePath, GLenum format);

  void HandleCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
  void HandleScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
  void HandleKeyCallback(GLFWwindow* window, int key, int scancode, int action, int modsbit);

  void ProcessInput(GLFWwindow* window);
};

#endif // _LIGHTING_H_
