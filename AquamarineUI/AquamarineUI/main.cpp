//this is where the Aquamarine UI Example exists
//NOTICE: THIS UI FRAMEWORK IS STILL UNDER CONSTRUCTION AND IN EXPERIMENTAL PHASE
//Contribution is welcomed
//this is a toy UI Framework, if there's any bugs or problems, please report it in the issues section on GitHub

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "shaderParse.h"
#include "Button.hpp"

int main(){
    
    std::array<int, 3> RGB = {167,193,217};
    
    //this is an example window of the Aquamarine UI, be free to use it
    Aquamarine_Window exampleWindow = Aquamarine_Window();
    exampleWindow.CreateCustomizedWindow(1366, 768, RGB, 1.0f, "Default");
    
    shaderParser* shader = new shaderParser();
    (*shader).shaderCreation("./dependencies/shader/shader.glsl");
    (*shader).useShader();
    
    Aquamarine_Button exampleButton = Aquamarine_Button();
    exampleButton.CreateButton();
    exampleButton.setButtonPosition(200, 300, exampleWindow);
    
    while (!exampleWindow.getWindowStatus()) {
        
        //Add this RenderBegin to start the render process
        exampleWindow.RenderBegin();
        //the actual content render here and till the expression that says the end of the renderation
        exampleButton.DrawButton();
        
        exampleWindow.RenderEnd();
    }
    
    exampleWindow.GLFWTerminate();
    
}
