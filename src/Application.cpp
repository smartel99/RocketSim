#include "Application.h"
#include "utils/Fonts.h"
#include "utils/Config.h"
#include "widgets/MainMenu.h"
#include "widgets/Logger.h"
#include "widgets/Options.h"
#include "widgets/Popup.h"
#include <iostream>
#include <windows.h>

#include "utils/rendering/Meshes.h"

static Renderer::Mesh mesh;

Application::Application()
{
    // Get size of main display.
    m_width = float(GetSystemMetrics(SM_CXSCREEN));
    m_heigth = float(GetSystemMetrics(SM_CYSCREEN));
    /* Initialize GLFW library */
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "Unable to initialize GLFW!" << std::endl;
        return;
    }

    /* Set openGL and GLSL version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGl context */
    m_window = glfwCreateWindow(int(m_width), int(m_heigth),
                                "Rocket Simulator", nullptr, nullptr);
    if (m_window == nullptr)
    {
        /* Unable to create window */
        std::cout << "Unable to create window!" << std::endl;
        return;
    }

    /* Make the newly created window the current context */
    glfwMakeContextCurrent(m_window);

    /* Unlock the framerate */
    glfwSwapInterval(1);

    /* Initialize the GLEW library */
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Unable to initialize GLEW!" << std::endl;
        m_window = nullptr;
        return;
    }
    else
    {
        std::cout << "Using OpenGL Version " << glGetString(GL_VERSION)
            << std::endl;
    }


    /* Initialize ImGui related stuff */
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load all fonts found.
    int fontSize = DEFAULT_FONT_SIZE;
    try
    {
        fontSize = Config::GetField<int>("FontSize");
    }
    catch (std::invalid_argument)
    {
        Config::SetField<int>("FontSize", fontSize);
    }
    Fonts::Load(fontSize);

    /* --------------  Initialize widgets  -------------- */
    // Logger
    AddWidget(Logging::Draw);

    // Options
    Options::Init();
    AddWidget(Options::Render);

    // Popup
    AddWidget(Popup::Render);

    // Main menu.
    MainMenu mainMenu;
    std::function<void(void)> func = std::bind(&MainMenu::Process, mainMenu);
    AddWidget(func);

    m_error = false;

    std::vector<Renderer::Triangle> tris = { Renderer::Triangle({ 0, 0 }, { 1, 0 }, { 0, 1 }, 0xFFFFFFFF),
                                             Renderer::Triangle({ 0, 1 }, { 0.5f, 0.5f }, { 1, 1 }, 0xFF0000FF) };
    mesh = Renderer::Mesh(tris, ImVec2(100, 100), ImVec2(m_width / 2, m_heigth / 2));
}

Application::~Application()
{
    /* Terminate OpenGL, GLFW, GLEW and ImGui */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void Application::AddWidget(std::function<void()> widgetFunction)
{
    m_widgets.push_back(widgetFunction);
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        GLCall(glClearColor(RENDER_COLOR_BLACK));

        /* Start the Dear ImGui frame */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Set the size and position of the main window (the next one that will be created) */
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(m_width, m_heigth), ImGuiCond_Once);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::PopStyleVar();

        ImGui::ShowMetricsWindow();
        static float size[2] = { 100, 100 };
        static float pos[2] = { m_width / 2, m_heigth / 2 };
        static float anchor[2] = { 0.5f, 0.5f };
        static float rot = 0.0f;
        if (ImGui::SliderFloat2("Size", size, 0, 1000))
        {
            mesh.Size(ImVec2(size[0], size[1]));
        }
        if (ImGui::SliderFloat2("Position", pos, 0, m_width))
        {
            mesh.Pos(ImVec2(pos[0], pos[1]));
        }
        if (ImGui::SliderFloat2("Anchor", anchor, 0, 1))
        {
            mesh.Anchor(ImVec2(anchor[0], anchor[1]));
        }
        if (ImGui::SliderFloat("Rotation", &rot, 0, 360.f))
        {
            mesh.Rotation(rot);
        }

        mesh.Draw();
        for (const std::function<void()>& widget : m_widgets)
        {
            /* Process all widgets */
            widget();
        }

        ImGui::End();

        /* Render and draw the frame */
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }
}

void Application::windowSizeCallback(GLFWwindow* win, int w, int h)
{
    glViewport(0, 0, w, h);
    m_width = float(w);
    m_heigth = float(h);
}
