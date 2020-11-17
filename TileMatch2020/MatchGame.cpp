#include "MatchGame.h"
#include "SimpleShader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// For std::cout and std::cerr
#include <iostream>

MatchGame::MatchGame()
{
}

MatchGame::~MatchGame()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);

    if (m_Deck)
        delete(m_Deck);
}

bool MatchGame::Init()
{
    
    if(!glfwInit()){
    
        std::cerr << "Error initializing GLFW! \n";
        return false;
    }

    glfwSetErrorCallback(ErrorCallbacks::GLFW_ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Tile Match 2020!", nullptr, nullptr);
    
    if (!m_Window) {

        std::cerr << "Error creating GLFW Window! \n";
        return false;
    }
    
    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(ErrorCallbacks::Callback_OpenGL_Error, 0);

    glfwSwapInterval(1);

    glClearColor(0.15f, 0.15f, 0.4f, 1.0f);
    
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    

    GLInfo::PrintOpenGLInfo();

    m_Deck = new Deck();

    glfwSetWindowUserPointer(m_Window, reinterpret_cast<void*>(this));

    glfwSetMouseButtonCallback(m_Window, InputCallbacks::I_MouseButtonForwarder);
    glfwSetCursorPosCallback(m_Window, InputCallbacks::I_MousePositionForwarder);

    return true;
}

int MatchGame::Run()
{


    while (!glfwWindowShouldClose(m_Window)){
        

        glfwPollEvents();
        //update();

        double currTick = glfwGetTime();
        double dt = currTick - m_PrevTick;
        m_PrevTick = currTick;

        m_Deck->Update(dt);
        

        glViewport(0, 0, m_windowWidth, m_windowHeight);
        glScissor(0, 0, m_windowWidth, m_windowHeight);

        glClearColor(0.15f, 0.15f, 0.4f, 1.0f);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        


        // Render the play area
        glViewport(50, 50, m_windowWidth - 300, m_windowHeight - 100);
        glScissor(50, 50, m_windowWidth - 300, m_windowHeight - 100);
        m_Deck->Draw();

        // Render the timer
        glViewport(m_windowWidth - 200, m_windowHeight - 100, 150, 50);
        glScissor(m_windowWidth - 200, m_windowHeight - 100, 150, 50);
        RenderClock(); 

        // Render the information screens  
        

        glfwSwapBuffers(m_Window);
    }

    return 0;
}

void MatchGame::I_MouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
        m_Deck->Click(m_MouseX, m_MouseY, 1);
}

void MatchGame::I_MousePosition(GLFWwindow* window, double xpos, double ypos)
{
    m_MouseX = xpos;
    m_MouseY = ypos;
}

void MatchGame::RenderClock()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ErrorCallbacks::GLFW_ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void GLAPIENTRY ErrorCallbacks::Callback_OpenGL_Error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (severity > GL_DEBUG_SEVERITY_NOTIFICATION) {
        fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    }
}

void GLInfo::PrintOpenGLInfo()
{
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL VENDOR:			%s\n", vendor);
    printf("GL RENDERER:			%s\n", renderer);
    printf("GL VERSION (string):		%s\n", version);
    printf("GL VERSION (integer):		%i.%i\n", major, minor);
    printf("GLSL VERSION:			%s\n", glslVersion);

}

void InputCallbacks::I_MouseButtonForwarder(GLFWwindow* window, int button, int action, int mods)
{
    MatchGame* app = reinterpret_cast<MatchGame*>(glfwGetWindowUserPointer(window));
    if (app) {

        app->I_MouseButton(window, button, action, mods);
    }
}

void InputCallbacks::I_MousePositionForwarder(GLFWwindow* window, double xpos, double ypos)
{
    MatchGame* app = reinterpret_cast<MatchGame*>(glfwGetWindowUserPointer(window));
    if (app) {

        app->I_MousePosition(window, xpos, ypos);

    }

}
