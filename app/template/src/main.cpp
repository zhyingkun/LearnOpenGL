#include <iostream>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <shader.h>
#include <camera.h>

#ifdef _WIN32
// For Visual Studio
const char* pVertexShaderPath = "../../../../app/template/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../../app/template/shaders/fragmentshader.frag";
#elif __APPLE__
// For Xcode App
const char* pVertexShaderPath = "../Resources/vertexshader.vert";
const char* pFragmentShaderPath = "../Resources/fragmentshader.frag";
// const char *pVertexShaderPath   = "../../../app/template/shaders/vertexshader.vert";
// const char *pFragmentShaderPath = "../../../app/template/shaders/fragmentshader.frag";
#elif __linux__
// For VSCode
const char* pVertexShaderPath = "../../../app/template/shaders/vertexshader.vert";
const char* pFragmentShaderPath = "../../../app/template/shaders/fragmentshader.frag";
#endif

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

void glfwErrorHandler(int code, const char* desc) {
  cout << "zykTest glfw Error, code:" << code << " description:" << desc << endl;
}
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}
void handleFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);
  cout << "New viewport: " << width << ", " << height << endl;
}
void handleCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  (void)window;
  cout << "Mouse Input ==> xpos: " << xpos << ", ypos: " << ypos << endl;
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
  lastX = xpos;
  lastY = ypos;
  camera.ProcessMouseMovement(xoffset, yoffset);
}
void handleScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  (void)window;
  (void)xoffset;
  camera.ProcessMouseScroll(yoffset);
}
void handleMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  (void)window;
  cout << "Mouse button: " << button << ", action: " << action << ", mods: " << mods << endl;
}
void handleKeyCallback(GLFWwindow* window, int key, int scancode, int action, int modsbit) {
  cout << "Key Input: " << key << ", " << scancode << ", " << action << ", " << modsbit << endl;
  switch (key) {
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
      }
      break;
    default:
      break;
  }
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  glfwSetErrorCallback(glfwErrorHandler);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Template", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, handleFramebufferSizeCallback);
  glfwSetCursorPosCallback(window, handleCursorPosCallback);
  glfwSetScrollCallback(window, handleScrollCallback);
  glfwSetMouseButtonCallback(window, handleMouseButtonCallback);
  glfwSetKeyCallback(window, handleKeyCallback);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  Shader ourShader(pVertexShaderPath, pFragmentShaderPath);
  ourShader.use();
  glm::mat4 model = glm::mat4(1.0f);
  ourShader.setMat4("model", model);
  glm::mat4 view = camera.GetViewMatrix();
  ourShader.setMat4("view", view);
  glm::mat4 projection =
      glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
  ourShader.setMat4("projection", projection);

  float vertices[] = {
      -0.5f,
      -0.5f,
      0.0f,
      0.5f,
      -0.5f,
      0.0f,
      0.0f,
      0.5f,
      0.0f,
  };
  float texColor[] = {
      1.0f,
      0.0f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      0.0f,
      1.0f,
  };
  unsigned int indices[] = {
      0,
      1,
      2,
  };
  unsigned int vertexVBO, colorVBO, VAO, EBO;

  glGenBuffers(1, &vertexVBO);
  glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &colorVBO);
  glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texColor), texColor, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  //	glEnable(GL_CULL_FACE); // default is disable
  //	glCullFace(GL_FRONT); // GL_FRONT, GL_FRONT_AND_BACK, default is GL_BACK
  //	glEnable(GL_FRONT_FACE); // default is disable
  //	glFrontFace(GL_CCW); // GL_CW, default is GL_CCW
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_STENCIL_BUFFER_BIT

    ourShader.use();
    // // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    ourShader.setMat4("model", model);
    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("view", view);
    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection =
        glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &vertexVBO);
  glDeleteBuffers(1, &colorVBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}
