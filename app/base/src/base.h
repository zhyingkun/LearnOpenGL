#ifndef _BASE_H_
#define _BASE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <camera.h>
#include <shader.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

typedef unsigned int GLObject;

class BaseApp {
private:
  GLFWwindow* mainWin;
  Shader* boxShader;

  GLObject textureContainer;
  GLObject textureAwesomeFace;

  GLObject boxVAO;
  GLObject boxVertexVBO;
  GLObject boxColorVBO;
  GLObject boxTexCoordVBO;
  GLObject boxEBO;

  Camera* camera;
  float lastX;
  float lastY;
  bool firstMouse;

  float deltaTime;
  float lastFrame; // Last Frame Time

  float awesomeAlpha;
  float colorAlpha;

public:
  BaseApp(/* args */);
  ~BaseApp();

  void InitializeGLFW();
  void CreateWinAndSetWinCallback();
  void LoadOpenGLFunctions();
  void BuildAndCompileBoxShader(const char* vertexPath, const char* fragmentPath);
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

#endif // _BASE_H_
