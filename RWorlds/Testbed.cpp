#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Geom/Triangle.h"
#include "Math/Vec.h"

int main()
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "RWorlds", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set up mesh
    rworlds::geom::Triangle tri;
    tri.a.pos = { -1.f, -1.f, 0 };
    tri.a.color = { 1.f, 0, 0 };
    tri.b.pos = { 0, 1.f, 0 };
    tri.b.color = { 0, 1.f, 0 };
    tri.c.pos = { 1.f, -1.f, 0 };
    tri.c.color = { 0, 0, 1.f };

    // set up shader

    // set up camera


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;

    return EXIT_SUCCESS;
}

