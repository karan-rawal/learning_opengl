#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}