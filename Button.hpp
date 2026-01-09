//Use the button header file along with this cpp file to create the button that allows you  to customize the
//position and the color of it. Notice that more details and functions are on the way
#pragma once

#include <iostream>
#include <array>

#include "Window.h"
#include "shaderParse.h"

class Aquamarine_Button {
private:
    //define the position of the button
    //the anchor point of the button is in the geometrical center
    //aka that the position is the position of the anchor point
    std::array<float, 2> position;
    
    //the color is set and stored in the RGBA format
    std::array<float, 4> Button_Color;
    
    //the width and the height of the button, stored in the integer format
    int Button_Width, Button_height;
    
    //define this two variable to make the position getting process more convinient
    double cursorPosition_x; double cursorPosition_y;
    
    //default button location, set to the ratio of 3:4
    //can be modified later in the program
    std::array<float, 8> actualPosition = {
        0.3, 0.4,
        0.6, 0.4,
        0.6, 0.8,
        0.3, 0.8
    };
    
    //the indices of the rectangle that has the vertical corner, maybe changed later if the rounded corner is needed
    std::array<unsigned int, 6> indices_Rectangle = {0,1,2,2,3,0};
    
    //the storage of the id that helps the process of the draw of the rextangle
    unsigned int IndexBufferObject, BufferObject, vertexArrayObject;
    
    //this shouldn't be used to put any real action 'cause this is only the reference of the passed in window object
    Aquamarine_Window* windowObject;
    //also to the temporary shader object
    shaderParser temporaryInsideShader;
    
public:
    
    //api function here
    Aquamarine_Button();
    ~Aquamarine_Button();
    
    //set the position of the button, not to be necessarily called,
    //if not, the burron will be set to default color and position
    void setButtonPosition(float Position_x, float Position_y, Aquamarine_Window& window);
    void setButtonColor(shaderParser& shader ,float Color_R, float Color_G,float Color_B,float Color_A);
    
    //these two function needed to draw the button on the screen
    void CreateButton();
    void DrawButton();
    
    void setUniform4floats(shaderParser& shader,std::string& name, float inputFloat_01, float inputFloat_02, float inputFloat_03, float inputFloat_04);
    
    void getCursorPosition(Aquamarine_Window* window);
    
    void PositionMoveFeedBack(shaderParser& shader);
    
    bool checkPositionArea(double& cursorPosition_x, double& cursorPosition_y);
};


