#include "MatchGame.h"

// For std::cout and std::cerr
#include <iostream>

MatchGame::MatchGame()
{
}

MatchGame::~MatchGame()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);
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

    GLInfo::PrintOpenGLInfo();

    return true;
}

int MatchGame::Run()
{
    
    GLuint cardVB = 0;
    glGenBuffers(1, &cardVB);

    float cardVertices[] = {

        -0.4f, -0.8f,  0.1f,
         0.4f, -0.8f,  0.1f,
        -0.4f,  0.8f,  0.1f,
         0.4f,  0.8f,  0.1f,

        -0.4f, -0.8f, -0.1f,
         0.4f, -0.8f, -0.1f,
        -0.4f,  0.8f, -0.1f,
         0.4f,  0.8f, -0.1f,

        -0.4f, -0.8f, -0.1f,
        -0.4f, -0.8f,  0.1f,
        -0.4f,  0.8f, -0.1f,
        -0.4f,  0.8f,  0.1f,

         0.4f, -0.8f, -0.1f,
         0.4f, -0.8f,  0.1f,
         0.4f,  0.8f, -0.1f,
         0.4f,  0.8f,  0.1f,

         -0.4f, 0.8f,  0.1f,
         -0.4f, 0.8f, -0.1f,
          0.4f, 0.8f,  0.1f,
          0.4f, 0.8f, -0.1f,
          
         -0.4f, -0.8f,  0.1f,
         -0.4f, -0.8f, -0.1f,
          0.4f, -0.8f,  0.1f,
          0.4f, -0.8f, -0.1f

    };

    unsigned int indices[] = {

        0, 1, 2,
        3, 0, 2,
        
        4, 5, 6,
        7, 4, 6,



    };

    
    
    while (!glfwWindowShouldClose(m_Window)){
        glfwPollEvents();
        //update();
        //draw();
        glfwSwapBuffers(m_Window);
    }

    return 0;
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

