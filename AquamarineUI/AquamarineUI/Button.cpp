
//the implemention of the button class
#include "Button.hpp"
#include "Window.h"

#include <iostream>
#include <memory>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



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
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &IndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_Rectangle.size()*sizeof(unsigned int), indices_Rectangle.data(), GL_DYNAMIC_DRAW);
    
}


void Aquamarine_Button::DrawButton(){
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


