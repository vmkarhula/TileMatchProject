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

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    

    GLInfo::PrintOpenGLInfo();

    return true;
}

int MatchGame::Run()
{
    
    GLuint cardVB = 0;
    glGenBuffers(1, &cardVB);

    GLuint cardIB = 0;
    glGenBuffers(1, &cardIB);

    GLuint cardColorBuf = 0;
    glGenBuffers(1, &cardColorBuf);

    float cardVertices[] = {
        
        -0.4f,  0.8f,  0.1f,
        -0.4f, -0.8f,  0.1f,
         0.4f, -0.8f,  0.1f,
         0.4f,  0.8f,  0.1f,

        -0.4f,  0.8f,  -0.1f,
        -0.4f, -0.8f,  -0.1f,
         0.4f, -0.8f,  -0.1f,
         0.4f,  0.8f,  -0.1f,
        
         -0.4f,  0.8f, -0.1f,
         -0.4f, -0.8f, -0.1f,
         -0.4f, -0.8f,  0.1f,
         -0.4f,  0.8f,  0.1f,

         0.4f,  0.8f, -0.1f,
         0.4f, -0.8f, -0.1f,
         0.4f, -0.8f,  0.1f,
         0.4f,  0.8f,  0.1f,

        -0.4f, 0.8f, -0.1f,
        -0.4f, 0.8f,  0.1f,
         0.4f, 0.8f,  0.1f,
         0.4f, 0.8f, -0.1f,
          
        -0.4f, -0.8f, -0.1f,
        -0.4f, -0.8f,  0.1f,
         0.4f, -0.8f,  0.1f,
         0.4f, -0.8f, -0.1f

    };

    float cardColors[] = {

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f

    };

    unsigned int cardIndices[] = {

        // Front face
         0, 1, 2,
         3, 0, 2,

         // Back
         6, 5, 4,
         6, 4, 7,

         // Left
         8, 9, 10,
         11, 8, 10,

         // Right
         14, 13, 12,
         14, 12, 15,

         // Top
         16, 17, 18,
         19, 16, 18,

         // Bottom
         22, 21, 20,
         22, 20, 23,

    };



    GLuint CardVAO;
    glCreateVertexArrays(1, &CardVAO);

    glBindVertexArray(CardVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cardVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cardVertices), cardVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cardIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cardIndices), cardIndices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, cardColorBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cardColors), cardColors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, cardVB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, cardColorBuf);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    SimpleShader shader(".\\shader\\cardflip.vs.glsl", ".\\shader\\basic.fs.glsl");

    while (!glfwWindowShouldClose(m_Window)){
        

        glfwPollEvents();
        //update();

        float timeValue = glfwGetTime();

        glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.5f, 0.5f)); 
        model = glm::rotate(model, glm::half_pi<float>() + glm::half_pi<float>() * glm::sin(timeValue), glm::vec3(0.0f, 1.0f, 0.0f));
        
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));       
        
        float aspect = 800 / 600;

        glm::mat4 proj = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);

        shader.Bind();

        int modelLocation = glGetUniformLocation(shader.GL_ID, "modelMtx");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        int viewLocation = glGetUniformLocation(shader.GL_ID, "viewMtx");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        int projLocation = glGetUniformLocation(shader.GL_ID, "projMtx");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



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

