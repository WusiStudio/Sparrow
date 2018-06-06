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
    GLFWwindow * t_window1;
    
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    t_window = glfwCreateWindow(640, 480, "init test", NULL, NULL);
    if (!t_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    t_window1 = glfwCreateWindow(640, 480, "init test1", NULL, NULL);
    if (!t_window1)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while(t_window || t_window1)
    {
        if( t_window && glfwWindowShouldClose(t_window) )
        {
            LOG.info("destroy window");
            glfwDestroyWindow(t_window);
            t_window = nullptr;
        }

        if( t_window1 && glfwWindowShouldClose(t_window1) )
        {
            LOG.info("destroy window1");
            glfwDestroyWindow(t_window1);
            t_window1 = nullptr;
        }
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}