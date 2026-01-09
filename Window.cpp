

#include "Window.h"
#include <iostream>
#include <math.h>


Aquamarine_Window::Aquamarine_Window(): windowWidth(800), windowHeight(600), windowColor_R(0), windowColor_G(0), windowColor_B(0), windowColor_A(0.0f){}

Aquamarine_Window::~Aquamarine_Window(){}

//Creating the default window with the default resolution (800*600)
void Aquamarine_Window::CreateDefaultWindow(){
    
    static bool glfwInitializationResult = glfwInit();
    if(!glfwInitializationResult){
        std::cerr<<"GLFW initialization Failed"<<std::endl;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    defaultWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
    if (!defaultWindow) {
        std::cerr<<"Window Creation Failed"<<std::endl;
    }
    
    glfwMakeContextCurrent(defaultWindow);
    glfwSwapInterval(1);
    
    auto glewInitializationResult  = glewInit();
    if (glewInitializationResult != GLEW_OK) {
        std::cerr<<"Failed to initialize the glew"<<std::endl;
    }
    
}





void Aquamarine_Window::CreateCustomizedWindow(double windowsWidth_in, double windowsHeight_in,std::array<int, 3>& windowRGB, double A_in_RGBA_Formatt, std::string CustomizedWindowTitle = "Default Title"){
    
    windowWidth = windowsWidth_in;
    windowHeight = windowsHeight_in;
    windowTitle = CustomizedWindowTitle;
    
    CreateDefaultWindow();
    
    windowColor_R = windowRGB[0]*std::pow(255, -1);
    windowColor_G = windowRGB[1]*std::pow(255, -1);
    windowColor_B = windowRGB[2]*std::pow(255, -1);
    windowColor_A = A_in_RGBA_Formatt;
    
    glClearColor(windowColor_R, windowColor_G, windowColor_B,windowColor_A);
    
}




void Aquamarine_Window::RenderBegin(){
    
    windowShouldClose = glfwWindowShouldClose(defaultWindow);
    glClear(GL_COLOR_BUFFER_BIT);
}



void Aquamarine_Window::RenderEnd(){
    glfwPollEvents();
    glfwSwapBuffers(defaultWindow);
}


void Aquamarine_Window::GLFWTerminate(){ glfwTerminate(); }


bool Aquamarine_Window::getWindowStatus(){
    return windowShouldClose;
}


std::array<int, 2> Aquamarine_Window::GetWindowHeightAndWidth(){
    return {windowWidth, windowHeight};
}

GLFWwindow* Aquamarine_Window::getWindowObject(){
    return defaultWindow;
}
