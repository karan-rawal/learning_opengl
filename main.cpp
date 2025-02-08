#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "string"

constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 800;
std::string TITLE = "Learning Opengl 2";

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    std::cout << "Window resized" << std::endl;
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}