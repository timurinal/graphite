#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utility/event.hpp"

namespace graphite
{
    class Context
    {
    public:
        explicit Context(const std::string& title = "Graphite Window", const int width = 1280, const int height = 720);

        Event onRender;
        
        GLFWwindow* getWindow() const;

        void start();

    private:
        GLFWwindow* mWindow;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        void mainLoop();
        void update();
        void render();
    };
}

#endif //CONTEXT_H
