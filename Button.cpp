
//the implemention of the button class
#include "Button.hpp"
#include "Window.h"

#include <iostream>
#include <memory>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


//default button is set to black, position is set to the default x = 0, y = 0, from the bottom left
Aquamarine_Button::Aquamarine_Button(): position({0,0}), Button_Color({0.0f, 0.0f, 0.0f, 1.0f}), Button_Width(200), Button_height(200){}

Aquamarine_Button::~Aquamarine_Button(){}

void Aquamarine_Button::setButtonPosition(float Position_x, float Position_y,Aquamarine_Window& window){
    auto [windowWidth, windowHeight] = window.GetWindowHeightAndWidth(); // C++17 structured binding
        // If your GetWindowHeightAndWidth returns array<int,2> or similar, adjust accordingly:
        // int windowWidth = (*TempPosition)[0];
        // int windowHeight = (*TempPosition)[1];

        // Normalize pixel coordinates to [0,1] (with Y flipped)
        float ndc_left   = (2.0f * Position_x) / windowWidth - 1.0f;
        float ndc_right  = (2.0f * (Position_x + Button_Width)) / windowWidth - 1.0f;

        // Flip Y: window top=0 → OpenGL top=+1
        float ndc_top    = 1.0f - (2.0f * Position_y) / windowHeight;
        float ndc_bottom = 1.0f - (2.0f * (Position_y + Button_height)) / windowHeight;

        // Now define rectangle vertices in NDC (counter-clockwise is typical)
        actualPosition = {
            ndc_left,  ndc_top,    // top-left     → vertex 0
            ndc_left,  ndc_bottom, // bottom-left  → vertex 1
            ndc_right, ndc_bottom, // bottom-right → vertex 2
            ndc_right, ndc_top     // top-right    → vertex 3
        };

        // Make sure actualPosition has 8 elements (4 vertices × 2 floats)
        // And your indices_Rectangle = {0, 1, 2, 0, 2, 3}; for two triangles
}

void Aquamarine_Button::CreateButton(){
    
    //generate the buffer that holds the data
    glGenBuffers(1, &BufferObject);
    glBindBuffer(GL_ARRAY_BUFFER,BufferObject);
    glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), actualPosition.data(), GL_DYNAMIC_DRAW);
    
    //generate the vertex array object
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    //enable the vertex array and tell the shader the inner layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    //set the index buffer object
    glGenBuffers(1, &IndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_Rectangle.size()*sizeof(unsigned int), indices_Rectangle.data(), GL_DYNAMIC_DRAW);
    
}


void Aquamarine_Button::DrawButton(){
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Aquamarine_Button::setUniform4floats(shaderParser& shader ,std::string& name, float inputFloat_01, float inputFloat_02, float inputFloat_03, float inputFloat_04){

    //set the uniform inside the shader, should be a generic function here...
    unsigned int uniformVariableLocation = glGetUniformLocation(shader.getPorogramID(), name.c_str());
    glUniform4f(uniformVariableLocation, inputFloat_01, inputFloat_02, inputFloat_03, inputFloat_04);
}


void Aquamarine_Button::setButtonColor(shaderParser& shader,float Color_R, float Color_G,float Color_B,float Color_A){
    
    //check the avalibility when pass the value to the uniform
    //this algorithm is pretty suck, however i will find a more better one later in the program and fix that issue
    if (Color_R<0) {
        Color_R = 0;
    }
    if (Color_G<0) {
        Color_G = 0;
    }
    if (Color_B<0) {
        Color_B = 0;
    }
    
    
    //set the color of the button via RGBA form color
    std::string uniformName = "backgroundColor";
    setUniform4floats(shader, uniformName, Color_R, Color_G, Color_B, Color_A);
}

void Aquamarine_Button::getCursorPosition(Aquamarine_Window* window){
    //get the position of the cursor and store it in the position array in the class entity
    windowObject = window;
    //get the cursor position relative to the upper left corner of the screen
    glfwGetCursorPos((*window).getWindowObject(), &cursorPosition_x, &cursorPosition_y);
}

void Aquamarine_Button::PositionMoveFeedBack(shaderParser& shader){
    //add some feedback when the cursor move into the range of the button
    getCursorPosition(windowObject);
    //give the feed back to the user when the cursor move inside the area on the button
    //aka when you put the cursor on the button, the button will give you the feedback that your cursor
    //has the ability to click on the button
    if(checkPositionArea(cursorPosition_x, cursorPosition_y)){
        setButtonColor(shader, Button_Color[0] - 65, Button_Color[1] - 65, Button_Color[2] - 65, Button_Color[3]);
    }
}

bool Aquamarine_Button::checkPositionArea(double& cursorPosition_x, double& cursorPosition_y){
    static bool result = false;
    return result;
}
