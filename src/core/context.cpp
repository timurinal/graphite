#include "core/context.hpp"

#include <stdexcept>

#include "utility/logger.hpp"

graphite::Context::Context(const std::string &title, const int width, const int height)
{
    if (glfwInit() != GLFW_TRUE)
    {
        throw std::runtime_error("Failed to initialise GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (mWindow == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(mWindow);

    // V-Sync is handled by a custom frame limiter
    glfwSwapInterval(0);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Failed to initialise GLAD");
    }

    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

    glViewport(0, 0, width, height);

    glClearColor(1.0, 0.0, 1.0, 1.0);
}

GLFWwindow* graphite::Context::getWindow() const
{
    return mWindow;
}

void graphite::Context::start()
{
    mainLoop();
}

void graphite::Context::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void graphite::Context::mainLoop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        update();
        render();
        glfwPollEvents();
    }
}

void graphite::Context::update()
{
    // onUpdate.invoke();
}

void graphite::Context::render()
{
    onRender.invoke();
}
