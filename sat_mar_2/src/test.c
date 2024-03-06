#include "glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "shader.h"

#define SHADER_FILES_DIR "/home/madrajib/workspace/Courses/opengl/sat_mar_2/src" 
#define VERTEX_SHADER_PATH SHADER_FILES_DIR "/vertex.vs"
#define FRAGMENT_SHADER_PATH SHADER_FILES_DIR "/fragment.fs"

void framebuffer_size_callback(GLFWwindow* win, int width, int height);
void processInput(GLFWwindow *win);

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(800, 600,"HelloOpenGl", NULL, NULL);
    if (win == NULL) {
        printf("Failed to open win\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to init GLAD\n");
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
       
    shader_t shader;
    shader_parse_compile(&shader, VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    // set up vertex data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, //left
         0.5f, -0.5f, 0.0f, //right
         0.0f,  0.5f, 0.0f, //top
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(win)) {
        // inputs
        processInput(win);
        // rendering functions

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_use(&shader);

        float timeval = glfwGetTime();
        float green =  sin(timeval) / 2.0f + 0.5f;
        int vertexColorLoc = glGetUniformLocation(shader.ID, "myColor");
        glUniform4f(vertexColorLoc, 0.0f, green, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // check and call events and swap the buffers
        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader_delete(&shader);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* win, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *win) {
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, 1);
    }
}
