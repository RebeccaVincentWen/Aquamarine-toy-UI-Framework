//Use the button header file along with this cpp file to create the button that allows you  to customize the
//position and the color of it. Notice that more details and functions are on the way
#pragma once

#include <iostream>
#include <array>

#include "Window.h"
#include "shaderParse.h"

class Aquamarine_Button {
private:
    std::array<float, 2> position;
    std::array<float, 4> Button_Color;
    int Button_Width, Button_height;
    
    //default button location, set to the ratio of 3:4
    std::array<float, 8> actualPosition = {
        0.3, 0.4,
        0.6, 0.4,
        0.6, 0.8,
        0.3, 0.8
    };
    
    std::array<unsigned int, 6> indices_Rectangle = {0,1,2,2,3,0};
    
    unsigned int IndexBufferObject, BufferObject, vertexArrayObject;
    
public:
    
    //api function here
    Aquamarine_Button();
    ~Aquamarine_Button();
    
    //set the position of the button, not to be necessarily called,
    //if not, the burron will be set to default color and position
    void setButtonPosition(float Position_x, float Position_y, Aquamarine_Window& window);
    void setButtonColor(float Color_R, float Color_G,float Color_B,float Color_A);
    
    //these two function needed to draw the button on the screen
    void CreateButton();
    void DrawButton();
    
    void setUniform4floats(shaderParser& shader,std::string& name, float inputFloat_01, float inputFloat_02, float inputFloat_03, float inputFloat_04);
};


