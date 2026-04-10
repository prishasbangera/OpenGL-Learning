#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourcolor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(position,1.0);\n"
" ourcolor = color;\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourcolor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
" color = vec4(ourcolor,1.0f);\n"
"}\n\0";

int main() {
	glfwInit();

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "hello world", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (window == NULL) {
        cout << "Failed to create glfw window" << endl;
        glfwTerminate();
        return -1;
    }

    // GLAD load all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // Compile shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Set up vertex data, VBO, VAO

    float vertices[] = {
        0.0f, 0.5f, 0.0f, // Top
        -0.5f, 0.5f, 0.0f, // Bottom left
        0.5f, -0.5f, 0.0f, // Bottom right
        0.0f, 0.5f, 0.0f, // bottom
        -0.5f, -0.7f, 0.0f, // tl
        0.5f, -0.7f, 0.0f // tr
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Render Loop
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }





}
