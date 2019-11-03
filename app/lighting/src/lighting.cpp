#include "lighting.h"

#include <iostream>
using namespace std;

#include <math.h>

#include <stb_image.h>

LightingApp lightingMain;

LightingApp::LightingApp(/* args */) {
  this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
  this->lastX = SCR_WIDTH / 2.0f;
  this->lastY = SCR_HEIGHT / 2.0f;
  this->firstMouse = true;

  this->deltaTime = 0.0f;
  this->lastFrame = 0.0f; // Last Frame Time
}

LightingApp::~LightingApp() {
  delete this->camera;
}

void glfwErrorHandler(int code, const char* desc) {
  cout << "zykTest glfw Error, code:" << code << " description:" << desc << endl;
}
void LightingApp::InitializeGLFW() {
  // glfw: initialize and configure
  // ------------------------------
  glfwSetErrorCallback(glfwErrorHandler);
  if (!glfwInit()) {
    cout << "zykTest: glfw init Error" << endl;
    exit(-1);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void handleFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  (void)window;
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void handleCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  lightingMain.HandleCursorPosCallback(window, xpos, ypos);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void handleScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  lightingMain.HandleScrollCallback(window, xoffset, yoffset);
}
void handleMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  (void)window;
  cout << "Mouse button: " << button << ", action: " << action << ", mods: " << mods << endl;
}
void handleKeyCallback(GLFWwindow* window, int key, int scancode, int action, int modsbit) {
  lightingMain.HandleKeyCallback(window, key, scancode, action, modsbit);
}
void LightingApp::CreateWinAndSetWinCallback(const char* winName) {
  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, winName, NULL, NULL);
  if (window == NULL) {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, handleFramebufferSizeCallback);
  glfwSetCursorPosCallback(window, handleCursorPosCallback);
  glfwSetScrollCallback(window, handleScrollCallback);
  glfwSetMouseButtonCallback(window, handleMouseButtonCallback);
  glfwSetKeyCallback(window, handleKeyCallback);

  this->mainWin = window;
}

void LightingApp::LoadOpenGLFunctions() {
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD" << endl;
    exit(-1);
  }
}

void LightingApp::BuildAndCompileBoxShader(const char* vertexPath, const char* fragmentPath) {
  // build and compile our shader program
  // ------------------------------------
  this->boxShader = new Shader(vertexPath, fragmentPath);
}
void LightingApp::BuildAndCompileLightShader(const char* vertexPath, const char* fragmentPath) {
  this->lightShader = new Shader(vertexPath, fragmentPath);
  lightPosition = vec3(0.0f, 0.0f, 3.2f);
  lightModel = mat4(1.0f);
  lightModel = translate(lightModel, lightPosition);
  lightModel = scale(lightModel, vec3(0.2f));
  lightShader->setMat4("model", lightModel);
}

void LightingApp::LoadAllTextures(const char* container2Path, const char* container2SpecularPath) {
  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
  this->textureContainer2 = this->CreateTexture(container2Path, GL_RGBA);
  this->textureContainer2Specular = this->CreateTexture(container2SpecularPath, GL_RGBA);
}

void LightingApp::SetTexturesToBoxShader() {
  // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
  // -------------------------------------------------------------------------------------------
  this->boxShader->use(); // don't forget to activate/use the shader before setting uniforms!
  // either set it manually like so:
  // glUniform1i(glGetUniformLocation(this->boxShader.ID, "ourTexture"), 0);
  // or set it via the texture class
  this->boxShader->setInt("material.diffuse", 0); // set which sampler use which ActiveTexture
  this->boxShader->setInt("material.specular", 1); // the same with fragment shader
  // this->boxShader.use();
  // this->boxShader.setFloat("xOffset", 0.0);
}

void LightingApp::ConfigOpenGLUtil() {
  glfwSwapInterval(1); // 1 means 60fps
  glEnable(GL_CULL_FACE); // default is disable
  glCullFace(GL_BACK); // GL_FRONT, GL_FRONT_AND_BACK, default is GL_BACK
  glEnable(GL_FRONT_FACE); // default is disable
  glFrontFace(GL_CCW); // GL_CW, default is GL_CCW
  //	glPolygonOffset
  glEnable(GL_DEPTH_TEST);
  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void LightingApp::CreateVertexArrayObject() {
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  // clang-format off
  float vertices[] = {
      -0.5f, -0.5f,  0.5f, // In OpenGL: front
       0.5f, -0.5f,  0.5f, // In Unity : back
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f, // In OpenGL: back
       0.5f,  0.5f, -0.5f, // In Unity : front
       0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f, // left
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f, // right
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f, // up
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f, // down
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
  };
  float normalDir[] = {
       0.0f,  0.0f,  1.0f,
       0.0f,  0.0f,  1.0f,
       0.0f,  0.0f,  1.0f,
       0.0f,  0.0f,  1.0f,
       0.0f,  0.0f, -1.0f,
       0.0f,  0.0f, -1.0f,
       0.0f,  0.0f, -1.0f,
       0.0f,  0.0f, -1.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       0.0f,  1.0f,  0.0f,
       0.0f,  1.0f,  0.0f,
       0.0f,  1.0f,  0.0f,
       0.0f,  1.0f,  0.0f,
       0.0f, -1.0f,  0.0f,
       0.0f, -1.0f,  0.0f,
       0.0f, -1.0f,  0.0f,
       0.0f, -1.0f,  0.0f,
  };
  float texCoord[] = {
      0.0f, 0.0f, // In OpenGL: front
      1.0f, 0.0f, // In Unity : back
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f, // In OpenGL: back
      1.0f, 0.0f, // In Unity : front
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f, // left
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f, // right
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f, // up
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f, // down
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
  };
  unsigned int indices[] = {
      0,  1,  2,  0,  2,  3, // In OpenGL: front, In Unity: back
      4,  5,  6,  4,  6,  7, // In OpenGL: back, In Unity: front
      8,  9,  10, 8,  10, 11, // left
      12, 13, 14, 12, 14, 15, // right
      16, 17, 18, 16, 18, 19, // up
      20, 21, 22, 20, 22, 23, // down
  };
  // clang-format on

  unsigned int vertexVBO, normalVBO, texCoordVBO, VAO, EBO;
  vertexVBO = CreateVertexBufferObject(sizeof(vertices), vertices);
  normalVBO = CreateVertexBufferObject(sizeof(normalDir), normalDir);
  texCoordVBO = CreateVertexBufferObject(sizeof(texCoord), texCoord);
  EBO = CreateElementBufferObject(sizeof(indices), indices);

  glGenVertexArrays(1, &VAO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  // position attribute
  glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
  // ShaderLocation, PerVertexSize, Type, Normalize, Stride, Offset
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); // the same with vertex shader
  // color attribute
  glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  // texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(2);
  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex
  // buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens.
  // Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when
  // it's not directly necessary.
  glBindVertexArray(0);
  // Unbind EBO Must after unbind the VAO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  this->boxVAO = VAO;
  this->boxVertexVBO = vertexVBO;
  this->boxNormalVBO = normalVBO;
  this->boxTexCoordVBO = texCoordVBO;
  this->boxEBO = EBO;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void LightingApp::ProcessInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera->ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera->ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera->ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera->ProcessKeyboard(RIGHT, deltaTime);
}

void LightingApp::RenderLoop() {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f),
  };

  // render loop
  // -----------
  while (!glfwWindowShouldClose(this->mainWin)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    ProcessInput(mainWin);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_STENCIL_BUFFER_BIT

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureContainer2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureContainer2Specular);

    // Light box
    // camera/view transformation
    mat4 view = camera->GetViewMatrix();
    // pass projection matrix to shader (note that in this case it could change every frame)
    mat4 projection = perspective(radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    vec3 lightColor;
    // lightColor.x = sin(glfwGetTime() * 2.0f);
    // lightColor.y = sin(glfwGetTime() * 0.7f);
    // lightColor.z = sin(glfwGetTime() * 1.3f);
    lightColor.x = 1.0f;
    lightColor.y = 1.0f;
    lightColor.z = 1.0f;

    lightShader->use();
    lightShader->setMat4("model", lightModel);
    lightShader->setMat4("view", view);
    lightShader->setMat4("projection", projection);
    lightShader->setVec3("light", lightColor);

    glBindVertexArray(boxVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    boxShader->use();
    // // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    // model = scale(model, vec3(0.5, 0.5, 0.5));
    // ourShader.setMat4("model", model);
    // pass projection matrix to shader (note that in this case it could change every frame)
    projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    boxShader->setMat4("projection", projection);

    // camera/view transformation
    // glm::mat4 view = camera->GetViewMatrix();
    boxShader->setMat4("view", view);

    boxShader->setVec3("light.position", lightPosition);
    // boxShader->setVec3("light.direction", vec3(-0.2f, -1.0f, -0.3f));
    boxShader->setFloat("light.constant", 1.0f);
    boxShader->setFloat("light.linear", 0.09f);
    boxShader->setFloat("light.quadratic", 0.032f);
    boxShader->setVec3("light.position", camera->Position);
    boxShader->setVec3("light.direction", camera->Front);
    boxShader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
    boxShader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

    boxShader->setVec3("viewPos", camera->Position);
    // light properties
    vec3 diffuseColor = lightColor * vec3(0.8f); // decrease the influence
    vec3 ambientColor = diffuseColor * vec3(0.5f); // low influence
    boxShader->setVec3("light.ambient", ambientColor);
    boxShader->setVec3("light.diffuse", diffuseColor);
    boxShader->setVec3("light.specular", vec3(2.0f, 2.0f, 2.0f)); // material properties
    // boxShader->setVec3("material.ambient", vec3(1.0f, 0.5f, 0.31f));
    // boxShader->setVec3("material.diffuse", vec3(1.0f, 0.5f, 0.31f));
    // boxShader->setVec3("material.specular", vec3(0.7f, 0.7f, 0.7f));
    // specular lighting doesn't have full effect on this object's material
    boxShader->setFloat("material.shininess", 32.0f);

    glBindVertexArray(boxVAO);
    for (unsigned int i = 0; i < 10; i++) {
      model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      boxShader->setMat4("model", model);

      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(mainWin);
    glfwPollEvents();
  }
}

void LightingApp::Terminate() {
  glDeleteVertexArrays(1, &this->boxVAO);
  glDeleteBuffers(1, &this->boxVertexVBO);
  glDeleteBuffers(1, &this->boxNormalVBO);
  glDeleteBuffers(1, &this->boxTexCoordVBO);
  glDeleteBuffers(1, &this->boxEBO);

  delete this->boxShader;
  delete this->lightShader;

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
}

GLObject LightingApp::CreateVertexBufferObject(GLsizeiptr size, const void* vertices) {
  GLObject VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return VBO;
}

GLObject LightingApp::CreateElementBufferObject(GLsizeiptr size, const void* indices) {
  GLObject EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  return EBO;
}

GLObject LightingApp::CreateTexture(const char* imagePath, GLenum format) {
  GLObject texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Texture arround
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  int width, height, nrChannels;
  unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
  if (data == NULL) {
    cout << "Failed to load texture: " << imagePath << endl;
    exit(-1);
  }
  // note that the awesomeface.png has transparency and thus an alpha channel,
  // so make sure to tell OpenGL the data type is of GL_RGBA
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  //   cout << endl << endl;
  //   cout << "zykTest Image Path:" << imagePath << endl << "Image Data:"; //<<data<<endl;
  //   for (int i = 0; i < width * height * nrChannels; i++) {
  //     if (i % nrChannels == 0) {
  //       cout << endl;
  //     }
  //     cout << int(data[i]) << " ";
  //   }
  //   cout << endl << endl;

  // cout << "width: " << width << "  height: " << height << " nrChannels: " << nrChannels << endl;
  stbi_image_free(data);
  return texture;
}

void LightingApp::HandleCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  (void)window;
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
  lastX = xpos;
  lastY = ypos;
  camera->ProcessMouseMovement(xoffset, yoffset);
}

void LightingApp::HandleScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  (void)window;
  (void)xoffset;
  camera->ProcessMouseScroll(yoffset);
}
void LightingApp::HandleKeyCallback(GLFWwindow* window, int key, int scancode, int action, int modsbit) {
  cout << "Key Input: " << key << ", " << scancode << ", " << action << ", " << modsbit << endl;
  switch (key) {
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
      }
      break;
    case GLFW_KEY_Z:
      if (action == GLFW_PRESS) {
        cout << "zykTest Key Z Pressed" << endl;
      }
      break;
    default:
      break;
  }
}
