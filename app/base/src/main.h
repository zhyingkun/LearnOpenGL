#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>
#include <stb_image.h>

#ifdef _WIN32
// For Visual Studio
const char *pVertexShaderPath   = "../../../../app/base/shaders/vertexshader.vert";
const char *pFragmentShaderPath = "../../../../app/base/shaders/fragmentshader.frag";
const char *pContainerJpgPath   = "../../../../app/base/textures/container.jpg";
const char *pAwesomefacePngPath = "../../../../app/base/textures/awesomeface.png";
#elif __APPLE__
// For Xcode App
const char *pVertexShaderPath   = "../Resources/vertexshader.vert";
const char *pFragmentShaderPath = "../Resources/fragmentshader.frag";
const char *pContainerJpgPath   = "../Resources/container.jpg";
const char *pAwesomefacePngPath = "../Resources/awesomeface.png";
// const char *pVertexShaderPath   = "../../../app/base/shaders/vertexshader.vert";
// const char *pFragmentShaderPath = "../../../app/base/shaders/fragmentshader.frag";
// const char *pContainerJpgPath   = "../../../app/base/textures/container.jpg";
// const char *pAwesomefacePngPath = "../../../app/base/textures/awesomeface.png";
#elif __linux__
// For VSCode
const char *pVertexShaderPath   = "../../../app/base/shaders/vertexshader.vert";
const char *pFragmentShaderPath = "../../../app/base/shaders/fragmentshader.frag";
const char *pContainerJpgPath   = "../../../app/base/textures/container.jpg";
const char *pAwesomefacePngPath = "../../../app/base/textures/awesomeface.png";
#endif


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow *glfwComInitAndConfig();
unsigned int configTexture(const char *imagePath, GLenum format);
unsigned int configVertexBufferObj(GLsizeiptr size, const void *vertices);
unsigned int configElementBufferObj(GLsizeiptr size, const void *indices);
unsigned int configVertexData();
void glmCoordinateTranslation();
void displaysMartix(glm::mat4 trans);
void displaysVec4(glm::vec4 point);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f; // Last Frame Time
