#include <iostream>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include <shader.h>
#include <camera.h>

#ifdef _WIN32
// For Visual Studio
const char *pVertexShaderPath   = "../../../../app/lighting/shaders/vertexshader.vert";
const char *pFragmentShaderPath = "../../../../app/lighting/shaders/fragmentshader.frag";
const char *pLightVertPath      = "../../../../app/lighting/shaders/light.vert";
const char *pLightFragPath      = "../../../../app/lighting/shaders/light.frag";
#elif __APPLE__
// For Xcode App
const char *pVertexShaderPath   = "../Resources/vertexshader.vert";
const char *pFragmentShaderPath = "../Resources/fragmentshader.frag";
const char *pLightVertPath      = "../Resources/light.vert";
const char *pLightFragPath      = "../Resources/light.frag";
// const char *pVertexShaderPath   = "../../../app/lighting/shaders/vertexshader.vert";
// const char *pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
// const char *pLightVertPath      = "../../../app/lighting/shaders/light.vert";
// const char *pLightFragPath      = "../../../app/lighting/shaders/light.frag";
#elif __linux__
// For VSCode
const char *pVertexShaderPath   = "../../../app/lighting/shaders/vertexshader.vert";
const char *pFragmentShaderPath = "../../../app/lighting/shaders/fragmentshader.frag";
const char *pLightVertPath      = "../../../app/lighting/shaders/light.vert";
const char *pLightFragPath      = "../../../app/lighting/shaders/light.frag";
#endif

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
// camera
Camera camera(vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f; // Last Frame Time

void glfwErrorHandler(int code, const char *desc)
{
	cout << "zykTest glfw Error, code:" << code << " description:" << desc << endl;
}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
void handleFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	cout << "New viewport: " << width << ", " << height << endl;
}
void handleCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
	(void)window;
	cout << "Mouse Input ==> xpos: " << xpos << ", ypos: " << ypos << endl;
	if (firstMouse)
	{
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
void handleScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)window; (void)xoffset;
	camera.ProcessMouseScroll(yoffset);
}
void handleMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	cout << "Mouse button: " << button << ", action: " << action << ", mods: " << mods << endl;
}
void handleKeyCallback(GLFWwindow *window, int key, int scancode, int action, int modsbit)
{
	cout << "Key Input: " << key << ", " << scancode << ", " << action << ", " << modsbit << endl;
	switch (key)
	{
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
			}
			break;
		default:
			break;
	}
}

int main(int argc, char* argv[])
{
	(void)argc; (void)argv;
	glfwSetErrorCallback(glfwErrorHandler);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "lighting", NULL, NULL);
	if (window == NULL)
	{
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
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	Shader ourShader(pVertexShaderPath, pFragmentShaderPath);
	Shader lightShader(pLightVertPath, pLightFragPath);
	vec3 lightPos = vec3(0.7f, 0.3f, 0.5f);
	mat4 lightModel = mat4(1.0f);
	lightModel = translate(lightModel, lightPos);
	lightModel = scale(lightModel, vec3(0.2f));
	lightShader.setMat4("model", lightModel);

	
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
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};
	unsigned int indices[] = {
		 0,  1,  2,  0,  2,  3, // In OpenGL: front, In Unity: back
		 4,  5,  6,  4,  6,  7, // In OpenGL: back, In Unity: front
		 8,  9, 10,  8, 10, 11, // left
		12, 13, 14, 12, 14, 15, // right
		16, 17, 18, 16, 18, 19, // up
		20, 21, 22, 20, 22, 23, // down
	};
	unsigned int vertexVBO, normalVBO, VAO, EBO;
	
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalDir), normalDir, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
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
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // GL_STENCIL_BUFFER_BIT
		
		// camera/view transformation
		mat4 view = camera.GetViewMatrix();
		// pass projection matrix to shader (note that in this case it could change every frame)
		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		lightShader.use();
		lightShader.setMat4("model", lightModel);
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("light", lightColor);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		ourShader.use();
		// // create transformations
		mat4 model = mat4(1.0);
		model = scale(model, vec3(0.5, 0.5, 0.5));
		ourShader.setMat4("model", model);
//		mat4 view = mat4(1.0f);
		ourShader.setMat4("view", view);
//		mat4 projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		ourShader.setMat4("projection", projection);

//		ourShader.setVec3("light", vec3(1.0f));
//		ourShader.setVec3("object", vec3(1.0f, 0.5f, 0.31f));
//		ourShader.setVec3("lightPos", lightPos);
//		ourShader.setVec3("viewPos", camera.Position);
		
		ourShader.setVec3("light.position", lightPos);
		ourShader.setVec3("viewPos", camera.Position);
		// light properties
		vec3 diffuseColor = lightColor   * vec3(0.5f); // decrease the influence
		vec3 ambientColor = diffuseColor * vec3(0.2f); // low influence
		ourShader.setVec3("light.ambient", ambientColor);
		ourShader.setVec3("light.diffuse", diffuseColor);
		ourShader.setVec3("light.specular", vec3(1.0f, 1.0f, 1.0f));		// material properties
		ourShader.setVec3("material.ambient", vec3(1.0f, 0.5f, 0.31f));
		ourShader.setVec3("material.diffuse", vec3(1.0f, 0.5f, 0.31f));
		ourShader.setVec3("material.specular", vec3(0.5f, 0.5f, 0.5f)); // specular lighting doesn't have full effect on this object's material
		ourShader.setFloat("material.shininess", 32.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
