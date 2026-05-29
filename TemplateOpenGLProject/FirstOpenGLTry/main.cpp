#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos,1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0, 0.0, 0.0,1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

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

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check vertex success
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // frag shader

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check frag success
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Set up vertex data, VBO, VAO

    // coordinates are in ndc
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };


    // VBO: stores verdex data in GPU memory
    unsigned int VBO, VAO, EBO; // vertex buffer object, vertex array object
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO); // generate VBO with buffer id
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); // VAO BIND

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO to vertex buffer object type
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // also dynamic draw and stream draw

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // location = 0, vec3, floating point, normaled?, stride, offset 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // vertexe attrib location as argument

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // VAO UNBIND

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); Or GL Fill

    // Render Loop
    
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // technically no need
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0); no need to unbind it every time
        //glDrawArrays(GL_TRIANGLES, 0, 6); // start index, how many vertices

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Get number of vertex attribs available
    int numAttribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
    std::cout << "Max vertex attribs: " << numAttribs << std::endl;

    glfwTerminate();
    return 0;

}
