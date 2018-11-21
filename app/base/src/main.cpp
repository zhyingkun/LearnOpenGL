#include "main.h"

int main()
{
    printf("zykTest\n");
    // Init glfw window
    GLFWwindow *window = glfwComInitAndConfig();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glmCoordinateTranslation(); //for test

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader(pVertexShaderPath, pFragmentShaderPath);

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    //firefox-icon.png container.jpg
    unsigned int texture1 = configTexture(pContainerJpgPath, GL_RGB);
    unsigned int texture2 = configTexture(pAwesomefacePngPath, GL_RGBA);

    // Config Vertex Data
    unsigned int VAO = configVertexData();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    // glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
    // or set it via the texture class
    ourShader.setInt("ourTexture", 0);
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
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    // render loop
    // -----------
    // int RenderIndex = 0;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // std::cout<<"zykTest: RenderLoop "<<RenderIndex<<std::endl;
        // RenderIndex++;

        // input
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // ourShader.use();
        // float timeValue = glfwGetTime();
        // float xOffset = (sin(timeValue) / 2.0f);
        // ourShader.setFloat("xOffset", xOffset);

        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        // glm::mat4 trans = glm::mat4(1.0f);
        // displaysMartix(trans);
        // trans = glm::translate(trans, glm::vec3(0.3f, -0.3f, -0.2f));
        // displaysMartix(trans);

        // trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
        // unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        ourShader.use();
        // // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        // glm::mat4 view = glm::mat4(1.0f);
        // glm::mat4 projection = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -30.0f));
        // // view = glm::rotate(view, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // ourShader.setMat4fv("model", model);
        // ourShader.setMat4fv("view", view);
        // ourShader.setMat4fv("projection", projection);

        // retrieve the matrix uniform locations
        // unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        // unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        // ourShader.setMat4("projection", projection);

        // view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // ourShader.setMat4fv("view", view);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // float radius = 10.0f;
            // float camX = sin(glfwGetTime()) * radius;
            // float camZ = cos(glfwGetTime()) * radius;
            // view = glm::mat4(1.0f);
            // view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // glm::mat4 trans2 = glm::mat4(1.0f);
        // trans2 = glm::translate(trans2, glm::vec3(-0.3f, 0.3f, 0.0f));
        // trans2 = glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // trans2 = glm::scale(trans2, glm::vec3(xOffset + 0.5, xOffset + 0.5, xOffset + 0.5));
        // unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans2));

        // glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // draw our first triangle
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    // int width = 800;
    // int height = 600;
    // glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    // displaysMartix(proj);

    // glm::mat4 trans = glm::mat4(1.0f);
    // displaysMartix(trans);
    // trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
    // displaysMartix(trans);
    // glm::vec4 point = glm::vec4(1, 1, 0, 1);
    // displaysVec4(point);
    // displaysVec4(trans * point);

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // float cameraSpeed = 0.05f; // adjust accordingly
    // float cameraSpeed = 2.5f * deltaTime;
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     cameraPos += cameraSpeed * cameraFront;
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     cameraPos -= cameraSpeed * cameraFront;
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

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
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
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
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
GLFWwindow *glfwComInitAndConfig()
{
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
    {
        std::cout << "zykTest: glfw init Error" << std::endl;
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
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    return window;
}

unsigned int configTexture(const char *imagePath, GLenum format)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Texture arround
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(-2);
    }
    std::cout << "width: " << width << "  height: " << height << " nrChannels: " << nrChannels << std::endl;
    stbi_image_free(data);
    return texture;
}

unsigned int configVertexData()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        //-- Position --  ---- Color ----  - Texture Coordinate -
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // right up
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // right down
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left down
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // left up

        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // right up
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // right down
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left down
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // left up
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle

        0, 4, 5,
        0, 5, 1,

        2, 6, 3,
        6, 7, 3,

        4, 5, 6,
        4, 6, 7,

        0, 3, 7,
        0, 7, 4,

        1, 2, 5,
        2, 5, 6
        // 0, 1, 2
    };

    unsigned int VBO, VAO, EBO;
    VBO = configVertexBufferObj(sizeof(vertices), vertices);
    EBO = configElementBufferObj(sizeof(indices), indices);

    glGenVertexArrays(1, &VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    return VAO;
}

unsigned int configVertexBufferObj(GLsizeiptr size, const void *vertices)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return VBO;
}

unsigned int configElementBufferObj(GLsizeiptr size, const void *indices)
{
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return EBO;
}

void glmCoordinateTranslation()
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // glm::mat4 trans = glm::mat4(1.0f)
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    // std::cout << trans.to_string() << std::endl;
    vec = trans * vec;
    std::cout << "vec.x: " << vec.x << " vec.y: " << vec.y << " vec.z: " << vec.z << " vec.w: " << vec.w << std::endl;
}

void displaysMartix(glm::mat4 trans)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << (float)trans[j][i] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void displaysVec4(glm::vec4 point)
{
    for (int i = 0; i < 4; i++)
        std::cout << point[i] << " ";
    std::cout << std::endl;
}
