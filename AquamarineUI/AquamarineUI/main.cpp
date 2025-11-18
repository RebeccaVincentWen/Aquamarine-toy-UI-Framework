//this is where the Aquamarine UI Example exists
//NOTICE: THIS UI FRAMEWORK IS STILL UNDER CONSTRUCTION AND IN EXPERIMENTAL PHASE
//Contribution is welcomed

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

int main(){
    bool Initilization = glfwInit();
    if (!Initilization) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    static float ScreenWidth, ScreenHeight;
    ScreenWidth = 800.0f;
    ScreenHeight = 600.0f;

    GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Aquamarine UI", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    //this initialization of glew is critical to the later program, 'cause if not, the glGenBuffers will throw bad memory access error
    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to init glew"<<std::endl;
        return -1;
    }
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapInterval(1);
        glfwPollEvents();
    }
    
    glfwTerminate();
}
