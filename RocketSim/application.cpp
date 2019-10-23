#include "utils/window.h"

#include "rendering/renderer.h"

#include "utils/Log.h"

#include <iostream>


int main(int argc, char** argv) {
    Log::Init();
    LOG_CORE_WARN("Initialized Log!");
    LOG_INFO("Initialized");
    Window window;

    std::cout << "Using OpenGL Version " << glGetString(GL_VERSION) << std::endl;
    {
        while (!window.should_close())
        {
            if (window.get_error() != Window::WINDOW_ERROR_NONE)
            {
                std::cout << "Error!: " << window.get_error() << std::endl;
                window.clear_error();
            }
            else
            {
                window.newImGuiFrame();

                ImGui::Begin("test");
                ImGui::End();

                window.renderImGuiFrame();

                window.swapBuffer();
                window.pollEvents();
            }
        }
    }
}