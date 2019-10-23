/**
 ******************************************************************************
 * @addtogroup utils
 * @{
 * @file    window.h
 * @author  Samuel Martel
 * @brief   Header for the window module.
 *
 * @date 2019/10/23
 *
 ******************************************************************************
 */
#ifndef _WINDOW_H
#define _WINDOW_H

/*****************************************************************************/
/* Includes */
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"


/*****************************************************************************/
/* Exported defines */


/*****************************************************************************/
/* Exported macro */


/*****************************************************************************/
/* Exported types */

/*****************************************************************************/
/* Exported functions */

class Window
{
public:
    typedef enum
    {
        WINDOW_ERROR_NONE = 0,
        WINDOW_ERROR_INVALID_WINDOW,
        WINDOW_ERROR_GLFW_INIT,
        WINDOW_ERROR_GLEW_INIT,
        WINDOW_ERROR_WINDOW_INIT,
        WINDOW_ERROR_RESIZE_CALLBACK,
    }WindowError_t;

    Window();
    Window(int w, int h, const char* title);
    Window(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    ~Window();

    void newImGuiFrame(void);
    void renderImGuiFrame(void);

    inline bool should_resize(void) { return m_shouldResize; }
    inline bool should_close(void) { return glfwWindowShouldClose(m_window); }

    inline WindowError_t get_error(void) { return m_error; }
    inline int get_width(void) { return m_width; }
    inline int get_height(void) { return m_height; }
    inline int get_swapInterval(void) { return m_swapInterval; }
    inline GLFWwindow* get_window(void) { return m_window; }

    inline void clear_error(void) { m_error = WINDOW_ERROR_NONE; }
    inline void set_width(int w) { m_width = w; m_shouldResize = true; }
    inline void set_height(int h) { m_height = h; m_shouldResize = true; }
    inline void set_swapInterval(int s) { m_swapInterval = s; glfwSwapInterval(m_swapInterval); }
    
    inline void makeContextCurrent(void) { glfwMakeContextCurrent(m_window); }
    inline void swapBuffer(void) { glfwSwapBuffers(m_window); }
    inline void pollEvents(void) { glfwPollEvents(); }

    static void window_size_callback(GLFWwindow* window, int w, int h);
    static void init_imgui(void);

private:
    WindowError_t m_error;
    bool m_shouldResize;
    int m_width;
    int m_height;
    int m_swapInterval;
    const char* m_name;
    GLFWwindow* m_window;
};

/* Have a wonderful day :) */
#endif /* _WINDOW_H */
/**
 * @}
 */
/****** END OF FILE ******/
