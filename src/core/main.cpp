#include "iostream"
#include "fstream"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

// vertices for quad that covers the whole screen
float quadVertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,

};
// indices for the quad above
unsigned int quadIndices[] = {
    0, 1, 2,
    0, 2, 3
};

// glfw error callback
void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

int main()
{
    // initialize glfw
    glfwInit();

    // set glfw error callback
    glfwSetErrorCallback(glfwErrorCallback);

    // set opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "voxerra", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set window resize callback
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        std::cout << "window resized to " << width << "x" << height << std::endl;
        glViewport(0, 0, width, height);
    });

    // set the mouse move callback
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
    {
       std::cout << "mouse x: " << xpos << " y: " << ypos << std::endl;
    });

    // create vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // create element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind vertex array object
    glBindVertexArray(0);

    // create shader program
    unsigned int shaderProgram = glCreateProgram();

    // create vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // load vertex shader source from file
    std::ifstream vertexShaderFile("shaders/vertex.glsl");
    std::string vertexShaderSource((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
    const char* vertexShaderSourceCStr = vertexShaderSource.c_str();
    // compile vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED";
        std::cout << infoLog << std::endl;
    }
    // attach vertex shader to shader program
    glAttachShader(shaderProgram, vertexShader);

    // create fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // load fragment shader source from file
    std::ifstream fragmentShaderFile("shaders/fragment.glsl");
    std::string fragmentShaderSource((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
    const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
    // compile fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED";
        std::cout << infoLog << std::endl;
    }
    // attach fragment shader to shader program
    glAttachShader(shaderProgram, fragmentShader);

    // link shader program
    glLinkProgram(shaderProgram);
    // check for shader program link errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED";
        std::cout << infoLog << std::endl;
    }
    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // main loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        glfwPollEvents();

        // clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // swap buffers
        glfwSwapBuffers(window);
    }

    // terminate glfw
    glfwTerminate();

    return EXIT_SUCCESS;
}