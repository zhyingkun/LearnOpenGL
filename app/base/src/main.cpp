#include <iostream>
using namespace std;

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
float awesomeAlpha = 0.5f;
float colorAlpha = 0.2f;

void glfwErrorHandler(int code, const char *desc)
{
	cout << "zykTest glfw Error, code:" << code << " description:" << desc << endl;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
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
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void handleFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	(void)window;
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void handleCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
	(void)window;
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
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
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
		case GLFW_KEY_Z:
			if (action == GLFW_PRESS)
			{
				cout << "zykTest Key Z Pressed" << endl;
			}
			break;
		case GLFW_KEY_UP:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				awesomeAlpha += 0.1f;
				if (awesomeAlpha > 1.0){
					awesomeAlpha = 1.0;
				}
			}
			break;
		case GLFW_KEY_DOWN:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				awesomeAlpha -= 0.1f;
				if (awesomeAlpha < 0.0){
					awesomeAlpha = 0.0;
				}
			}
			break;
		case GLFW_KEY_RIGHT:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				colorAlpha += 0.1f;
				if (colorAlpha > 1.0){
					colorAlpha = 1.0;
				}
			}
			break;
		case GLFW_KEY_LEFT:
			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				colorAlpha -= 0.1f;
				if (colorAlpha < 0.0){
					colorAlpha = 0.0;
				}
			}
			break;
		default:
			break;
	}
}

GLFWwindow* initAndConfigGLFW()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwSetErrorCallback(glfwErrorHandler);
	if (!glfwInit())
	{
		cout << "zykTest: glfw init Error" << endl;
		return NULL;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, handleFramebufferSizeCallback);
	glfwSetCursorPosCallback(window, handleCursorPosCallback);
	glfwSetScrollCallback(window, handleScrollCallback);
	glfwSetMouseButtonCallback(window, handleMouseButtonCallback);
	glfwSetKeyCallback(window, handleKeyCallback);
	return window;
}

GLuint configVertexBufferObj(GLsizeiptr size, const GLvoid *vertices)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VBO;
}

GLuint configTexture(const GLchar *imagePath, GLenum format)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Texture arround
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GLint width, height, nrChannels;
	GLubyte *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// cout<<endl<<endl;
		// cout<<"zykTest Image Path:"<<imagePath<<endl<<"Image Data:";//<<data<<endl;
		// for(int i=0; i<width*height*nrChannels; i++){
		// 	if(i%nrChannels == 0){
		// 		cout<<endl;
		// 	}
		// 	cout<<int(data[i])<<" ";
		// }
		// cout<<endl<<endl;
	}
	else
	{
		cout << "Failed to load texture" << endl;
		exit(-2);
	}
	cout << "width: " << width << "  height: " << height << " nrChannels: " << nrChannels << endl;
	stbi_image_free(data);
	return texture;
}

GLuint configElementBufferObj(GLsizeiptr size, const GLvoid *indices)
{
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return EBO;
}

GLuint configVertexData()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	GLfloat vertices[] = {
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
	GLfloat texColor[] = {
		1.0f, 0.0f, 0.0f, // first
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, // second
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, // third
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, // fourth
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, // fifth
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, // sixth
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};
	GLfloat texCoord[] = {
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
	GLuint indices[] = {
		 0,  1,  2,  0,  2,  3, // In OpenGL: front, In Unity: back
		 4,  5,  6,  4,  6,  7, // In OpenGL: back, In Unity: front
		 8,  9, 10,  8, 10, 11, // left
		12, 13, 14, 12, 14, 15, // right
		16, 17, 18, 16, 18, 19, // up
		20, 21, 22, 20, 22, 23, // down
	};

	GLuint vertexVBO, colorVBO, texCoordVBO, VAO, EBO;
	vertexVBO = configVertexBufferObj(sizeof(vertices), vertices);
	colorVBO = configVertexBufferObj(sizeof(texColor), texColor);
	texCoordVBO = configVertexBufferObj(sizeof(texCoord), texCoord);
	EBO = configElementBufferObj(sizeof(indices), indices);

	glGenVertexArrays(1, &VAO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// position attribute
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	// ShaderLocation, PerVertexSize, Type, Normalize, Stride, Offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	// texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(2);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// Unbind EBO Must after unbind the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return VAO;
}

int main(int argc, char* argv[])
{
	(void)argc; (void)argv;
	printf("zykTest\n");
	// Init glfw window
	GLFWwindow *window = initAndConfigGLFW();
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;
	
	// build and compile our shader program
	// ------------------------------------
	Shader ourShader(pVertexShaderPath, pFragmentShaderPath);
	
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	//firefox-icon.png container.jpg
	GLuint texture1 = configTexture(pContainerJpgPath, GL_RGB);
	GLuint texture2 = configTexture(pAwesomefacePngPath, GL_RGBA);
	
	// Config Vertex Data
	GLuint VAO = configVertexData();
	
	// uncomment this call to draw in wireframe polygons.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	// glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
	// or set it via the texture class
	ourShader.setInt("texture1", 0); // set which sampler use which ActiveTexture
	ourShader.setInt("texture2", 1);
	// ourShader.use();
	// ourShader.setFloat("xOffset", 0.0);
	
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
	
	glfwSwapInterval(1); // 1 means 60fps
	glEnable(GL_CULL_FACE); // default is disable
	glCullFace(GL_BACK); // GL_FRONT, GL_FRONT_AND_BACK, default is GL_BACK
	glEnable(GL_FRONT_FACE); // default is disable
	glFrontFace(GL_CCW); // GL_CW, default is GL_CCW
//	glPolygonMode
//	glPolygonOffset
	glEnable(GL_DEPTH_TEST);

	// render loop
	// -----------
	int RenderIndex = 1;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		if (currentFrame >= 2.0 && currentFrame <= 3.0)
		{
			cout << "zykTest: RenderLoop " << RenderIndex++ << endl;
		}
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// input
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		ourShader.use();
		// // create transformations
		glm::mat4 model = glm::mat4(1.0f);
		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		
		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);
		
		ourShader.setFloat("awesomeAlpha", awesomeAlpha);
		ourShader.setFloat("colorAlpha", colorAlpha);
		
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);
			
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
