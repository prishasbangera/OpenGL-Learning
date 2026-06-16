#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define OURCOLOR "ourColor"

using namespace std;

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
    
    Shader shaderProgram("vertex.vert", "fragment.frag");

    // Set up vertex data, VBO, VAO

    // coordinates are in ndc
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

//#region TEXTURES

    // Texture coordinates
    /*float texCoord[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f
    };*/

    // creating the texture
    unsigned int texture;
    glGenTextures(1, &texture); // how many textures, stores in array

    glBindTexture(GL_TEXTURE_2D, texture);

    // Default behavior -> repeat texture when outside (ignore int part)
    // GL_REPEAT: default
    // GL_MIRRORED_REPEAT: mirrors the image with each repeat
    // GL_CLAMP_TO_EDGE: clamps the coord between 0 and 1, stretched edge
    // GL_CLAMP_TO_BORDER: clamps without stretched edge

    // texture target, what option (S vs T axis)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // When using clamp to border
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // Texture Filtering
    // GL_NEAREST - default, selects closes texel
    // GL_LINEAR - bilinear -> interpolated value based on dist from texture coorod
    // etc
    // minifying: use nearest when textures scaled down
    // mag: use linear when textures scaled up
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Mipmaps:
    // texture images which each is twidxe as small
    // glGenerateeMipmap
    // can specify filter method between mipmap levels
    /*
        GL_NEAREST_MIPMAP_NEAREST
        GL_LINEAR_MIPMAP_NEAREST
        cannot set mipmap filter option as mag field - miopmaps used when downscalinf, texture mag doesnt use mipmaps

    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Creating a texture 
    string filename = "image.jpg";
    int twidth, theight, numClrChannels;
    unsigned char* data = stbi_load(filename.c_str(), &twidth, &theight, &numClrChannels, 0);

    if (data) {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // can generate mipmaps here
    }
    else {
        std::cout << "Failed to load texture." << std::endl;
    }

    stbi_image_free(data);


//#end region

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
    // position
  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // vertexe attrib location as argument

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // vertexe attrib location as argument

    // texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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

        // Passing in a unforim
        float timeValue = glfwGetTime();
        float greenVal = (sin(timeValue) / 2.0f) + 0.5f;
        
        int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");

        shaderProgram.use();
        glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, texture);
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
    
    glDeleteProgram(shaderProgram.ID);

    // Get number of vertex attribs available
    int numAttribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
    std::cout << "Max vertex attribs: " << numAttribs << std::endl;

    glfwTerminate();
    return 0;

}
