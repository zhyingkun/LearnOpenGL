#include <iostream>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void glfwErrorHandler(int code, const char *desc)
{
	cout << "zykTest glfw Error, code:" << code << " description:" << desc << endl;
}
void handleFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	cout << "New viewport: " << width << ", " << height << endl;
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
void handleCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	cout << "Mouse Input ==> xpos: " << xpos << ", ypos: " << ypos << endl;
}
void handleMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	cout << "Mouse button: " << button << ", action: " << action << ", mods: " << mods << endl;
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

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, handleFramebufferSizeCallback);
	glfwSetKeyCallback(window, handleKeyCallback);
	glfwSetCursorPosCallback(window, handleCursorPosCallback);
	glfwSetMouseButtonCallback(window, handleMouseButtonCallback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
