
#include <iostream>
#include "shaderParse.h"
#include <sstream>
#include <fstream>
#include <tuple>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Make the default id to 0 to avoid initilization issue and other potiential issues
shaderParser::shaderParser(): shader_id_vertex(0), shader_id_fragment(0), program_id(0){}

shaderParser::~shaderParser(){}

//parse the pre-customized shader from the file in the dependencies folder
std::tuple<std::string, std::string> shaderParser::shaderParse(std::string shaderPath){
    //Open the shader file from the specific filepath
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
    
    //return the string file to the tuple to hold the shader source
    return {stringstream[0].str(), stringstream[1].str()};
}



//compile the shader with the shader read from the shader file
unsigned int shaderParser::shaderCompilation(std::string& shaderSource, unsigned int shaderType){
    //compile the shader based on the shader id
    unsigned int shader_id = glCreateShader(shaderType);
    const char* src = shaderSource.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);
    
    //the error handling if the shader failed to compile
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

unsigned int shaderParser::shaderCreation(std::string shaderFilePath){
    
    //get the shader source to the string to hold it temporarily hold the source code
    static std::tuple<std::string,std::string>(TempShaderSource) = shaderParse(shaderFilePath);
    shader_Source_Vertex = std::get<0>(TempShaderSource);
    shader_Source_fragment = std::get<1>(TempShaderSource);
    
    
    //create the program that use the shader instead of the system generic shader
    program_id = glCreateProgram();
    shader_id_vertex = shaderCompilation(shader_Source_Vertex, GL_VERTEX_SHADER);
    shader_id_fragment = shaderCompilation(shader_Source_fragment, GL_FRAGMENT_SHADER);
    
    //attach the shader to the program
    glAttachShader(program_id, shader_id_vertex);
    glAttachShader(program_id, shader_id_fragment);
    
    //link and validate the program before the program is executed
    glLinkProgram(program_id);
    glValidateProgram(program_id);
    
    //delete the unused shader to ensure the memory safety and efficiency
    glDeleteShader(shader_id_vertex);
    glDeleteShader(shader_id_fragment);
    
    return program_id;
}


void  shaderParser::useShader(){
    glUseProgram(program_id);
}



void shaderParser::SetUniformVariables1i(std::string& UniformVariableName, int data){
    static unsigned int Location_temp = glGetUniformLocation(program_id, UniformVariableName.c_str());
    glUniform1i(Location_temp ,data);
}

