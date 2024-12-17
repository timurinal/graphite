#include <iostream>

#include "core/context.hpp"
#include "includes/core/glhandle.hpp"

graphite::Context* context;

void onRender()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(context->getWindow());
}

int main()
{
    context = new graphite::Context();
    context->onRender.subscribe(onRender);
    context->start();
    
    return 0;
}