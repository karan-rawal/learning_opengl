#include <fstream>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "string"
#include "sstream"

constexpr unsigned int WIDTH = 800;
constexpr unsigned int HEIGHT = 800;
std::string TITLE = "Learning Opengl 2";

std::string readFile(const char* filePath) {
    std::ifstream file;
    file.open(filePath);
    std::string data;
    if (file.is_open()) {
        std::stringstream fileStreamData;
        fileStreamData << file.rdbuf();
        data = fileStreamData.str();
    } else {
        std::cerr << "Failed to open shader file: " << filePath;
    }
    return data;
}

unsigned int createShader(const char* shaderSource, unsigned int shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        int logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        char log[logLength];
        glGetShaderInfoLog(shader, logLength, nullptr, log);

        std::cout << "Failed to compile shader: " << shaderSource << ":" << log;
    }
    return shader;
}

unsigned int createShaderProgram(const char* fragmentShaderPath, const char* vertexShaderPath) {
    std::string fragmentShaderSource = readFile(fragmentShaderPath);
    unsigned int fragmentShader = createShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);

    std::string vertexShaderSource = readFile(vertexShaderPath);
    unsigned int vertexShader = createShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    int status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

    if (!status) {
        int infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        char infoLog[infoLogLength];
        glGetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog);
        std::cout << "Failed to link shader program: " << infoLog;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

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

    unsigned int shaderProgram = createShaderProgram("../shader1.frag", "../shader1.vert");

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