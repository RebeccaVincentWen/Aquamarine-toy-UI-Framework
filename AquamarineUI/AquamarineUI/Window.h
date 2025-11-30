
#pragma once
//this header file contains the Creation of the Window and the property behind it.

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Aquamarine_Window{
private:
    int windowWidth, windowHeight;
    float windowColor_R, windowColor_G, windowColor_B;
    double windowColor_A;
    std::string windowTitle = "Default Title";
    bool windowShouldClose = false;
    GLFWwindow* defaultWindow;
    
public:
    
    Aquamarine_Window();
    ~Aquamarine_Window();
    
    //Call this function if you want to explicitly manage the window status
    //no need to call this function if you decide to let the program automatically
    bool getWindowStatus();
    
    void CreateDefaultWindow();
    void CreateCustomizedWindow(double windowsWidth_in, double windowsHeight_in,std::array<int, 3>& windowRGB, double A_in_RGBA_Formatt, std::string CustomizedWindowTitle);
    
    void RenderBegin();
    void RenderEnd();
    
    std::array<int, 2> GetWindowHeightAndWidth();
    
    void GLFWTerminate();
    
    GLFWwindow* getWindowObject();
};
