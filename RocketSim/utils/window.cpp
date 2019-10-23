/**
 ******************************************************************************
 * @addtogroup utils
 * @{
 * @file    window.cpp
 * @author  Samuel Martel
 * @brief   Source for the window module.
 *
 * @date 2019/10/23
 *
 ******************************************************************************
 */

/*****************************************************************************/
/* File includes */
#include "window.h"
#include "../rendering/renderer.h"

#include <iostream>


/*****************************************************************************/
/* Constants and Defines */

/*****************************************************************************/
/* Types */

/*****************************************************************************/
/* Private function declarations */

/*****************************************************************************/
/* Function pointers */

/*****************************************************************************/
/* Private Variables */
thread_local ImGuiContext* threadCTX;
/*****************************************************************************/
/* Public function definitions */
Window::Window()
{
    m_error = WINDOW_ERROR_NONE;
    m_width = 960;
    m_height = 540;
    m_shouldResize = false;
    m_swapInterval = 0;
    m_name = "Window";
    m_window = NULL;

    /* Init GLFW */
    if (!glfwInit())
    {
        /* If init is bad */
        m_error = WINDOW_ERROR_GLFW_INIT;
        m_window = NULL;
    }
    else
    {
        /* If init is good */
        /* Create a windowed mode window and its OpenGl context */
        m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
        if (!m_window)
        {
            /* If window creation failed */
            m_error = WINDOW_ERROR_WINDOW_INIT;
            glfwTerminate();
        }
        else
        {
            /* Set the callback for window resize */
            glfwSetWindowSizeCallback(m_window, window_size_callback);

            /* Make the window's context current */
            glfwMakeContextCurrent(m_window);

            /* Set the frame buffer swap interval */
            glfwSwapInterval(m_swapInterval);
        }
    }

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error at glewInit!" << std::endl;
        m_error = WINDOW_ERROR_GLEW_INIT;
    }
    /* Init ImGui */
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Window::Window(int w, int h, const char* title)
{
    m_error = WINDOW_ERROR_NONE;
    m_width = w;
    m_height = h;
    m_shouldResize = false;
    m_swapInterval = 0;
    m_window = NULL;

    if (title != NULL)
    {
        m_name = title;
    }
    else
    {
        m_name = "Window";
    }

    /* Init GLFW */
    if (!glfwInit())
    {
        /* If init is bad */
        m_error = WINDOW_ERROR_GLFW_INIT;
        m_window = NULL;
    }
    else
    {
        /* If init is good */
        /* Create a windowed mode window and its OpenGl context */
        m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
        if (!m_window)
        {
            /* If window creation failed */
            m_error = WINDOW_ERROR_WINDOW_INIT;
            glfwTerminate();
        }
        else
        {
            /* Set the callback for window resize */
            glfwSetWindowSizeCallback(m_window, window_size_callback);

            /* Make the window's context current */
            glfwMakeContextCurrent(m_window);

            /* Set the frame buffer swap interval */
            glfwSwapInterval(m_swapInterval);
        }
    }

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error at glewInit!" << std::endl;
        m_error = WINDOW_ERROR_GLEW_INIT;
    }

    /* Init ImGui */
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Window::Window(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    m_error = WINDOW_ERROR_NONE;
    m_width = w;
    m_height = h;
    m_shouldResize = false;
    m_swapInterval = 0;
    m_window = NULL;

    if (title != NULL)
    {
        m_name = title;
    }
    else
    {
        m_name = "Window";
    }

    /* Init GLFW */
    if (!glfwInit())
    {
        /* If init is bad */
        m_error = WINDOW_ERROR_GLFW_INIT;
        m_window = NULL;
    }
    else
    {
        /* If init is good */
        /* Create a windowed mode window and its OpenGl context */
        m_window = glfwCreateWindow(m_width, m_height, m_name, monitor, share);
        if (!m_window)
        {
            /* If window creation failed */
            m_error = WINDOW_ERROR_WINDOW_INIT;
            glfwTerminate();
        }
        else
        {
            /* Set the callback for window resize */
            glfwSetWindowSizeCallback(m_window, window_size_callback);

            /* Make the window's context current */
            glfwMakeContextCurrent(m_window);

            /* Set the frame buffer swap interval */
            glfwSwapInterval(m_swapInterval);
        }
    }

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error at glewInit!" << std::endl;
        m_error = WINDOW_ERROR_GLEW_INIT;
    }

    /* Init ImGui */
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void Window::newImGuiFrame(void)
{
    GlCall(glClearColor(RENDER_COLOR_BLACK));
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
    /* Start the Dear ImGui frame */
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::renderImGuiFrame(void)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::window_size_callback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
}
void Window::init_imgui(void)
{
    
}
/*****************************************************************************/
/* Private functions definitions */

/* Have a wonderful day! :) */
/**
 * @}
 */
/* END OF FILE */
