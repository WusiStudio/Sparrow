#include "GLFW/glfw3.h"
#include "log.hpp"


//========================================================================
// Print errors
//========================================================================

static void error_callback(int p_error, const char* p_description)
{
    LOG.error( "GLFW Error: [{0, d}], {1}", p_error, p_description );
}

int main( int argc, char ** argv )
{

    GLFWwindow * t_window;
    
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    t_window = glfwCreateWindow(640, 480, "init test", NULL, NULL);
    if (!t_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while(!glfwWindowShouldClose(t_window))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}