
//the implemention of the button class
#include "Button.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



Aquamarine_Button::Aquamarine_Button(): position({0,0}), Button_Color({0.0f, 0.0f, 0.0f, 1.0f}), Button_Width(0), Button_height(0){}

Aquamarine_Button::~Aquamarine_Button(){}

void Aquamarine_Button::setButtonPosition(float Position_x, float Position_y){
    position[0] = Position_x;
    position[1] = Position_y;
}

void Aquamarine_Button::DrawButton(){
    
    //generate the buffer that holds the data
    glGenBuffers(1, &BufferObject);
    glBindBuffer(GL_ARRAY_BUFFER,BufferObject);
    glBufferData(GL_ARRAY_BUFFER, position.size()*sizeof(float), position.data(), GL_DYNAMIC_DRAW);
    
    //generate the vertex array object
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    glEnableVertexAttribArray(vertexArrayObject);
    
    glGenBuffers(1, &IndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_Rectangle.size()*sizeof(float), indices_Rectangle.data(), GL_DYNAMIC_DRAW);
}


