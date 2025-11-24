//Use the button header file along with this cpp file to create the button that allows you  to customize the
//position and the color of it. Notice that more details and functions are on the way
#pragma once

#include <iostream>
#include <array>

class Aquamarine_Button {
private:
    std::array<float, 2> position;
    std::array<float, 4> Button_Color;
    int Button_Width, Button_height;
    
    std::array<unsigned int, 6> indices_Rectangle = {0,1,2,2,3,0};
    
    unsigned int IndexBufferObject, BufferObject, vertexArrayObject;
    
public:
    Aquamarine_Button();
    ~Aquamarine_Button();
    
    void setButtonPosition(float Position_x, float Position_y);
    void setButtonColor(float Color_R, float Color_G,float Color_B,float Color_A);
    
    void DrawButton();
    
};


