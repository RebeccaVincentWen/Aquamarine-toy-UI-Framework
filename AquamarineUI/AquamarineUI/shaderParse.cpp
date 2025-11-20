
#include <iostream>
#include "shaderParse.h"
#include <sstream>
#include <fstream>
#include <tuple>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

shaderParser::shaderParser(): shader_id_vertex(0), shader_id_fragment(0), program_id(0){}

shaderParser::~shaderParser(){}


std::tuple<std::string, std::string> shaderParser::shaderParse(std::string shaderPath){
    std::ifstream shaderReader(shaderPath);
    if (!shaderReader.is_open()) {
        std::cerr<<"Shader not exist"<<std::endl;
    }
    
    //restrict the type of the shader to the enumeration of this
    enum shaderType: int{
        None = -1, Vertex = 0, Fragment = 1
    };
    
    shaderType shader_type = shaderType::None;
    
    static std::stringstream stringstream[2];
    static std::string fileLine;
    
    //accept the file and put the content of the file to the string as the source code of the shader
    while (getline(shaderReader,fileLine)) {
        if (fileLine.find("#shader") != std::string::npos) {
            if (fileLine.find("vertex") != std::string::npos) {
                shader_type = shaderType::Vertex;
            }
            else if(fileLine.find("fragment") != std::string::npos){
                shader_type = shaderType::Fragment;
            }
            else{
                shader_type = shaderType::None;
            }
        }
        
        else{
            if (shader_type != shaderType::None) {
                stringstream[(int)shader_type]<<fileLine<<"\n";
            }
        }
        
    }
    
    return {stringstream[0].str(), stringstream[1].str()};
}




unsigned int shaderParser::shaderCompilation(std::string& shaderSource, unsigned int shaderType){
    //compile the shader based on the shader id and 
    unsigned int shader_id = glCreateShader(shaderType);
    const char* src = shaderSource.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);
    
    static int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        static int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message);
        std::cerr<<"Fail to compile Shader"<<message<<"\n";
        glDeleteShader(shader_id);
        return -1;
    }
    
    return shader_id;
}

unsigned int shaderParser::shaderCreation(){
    
    program_id = glCreateProgram();
    
    return program_id;
}
