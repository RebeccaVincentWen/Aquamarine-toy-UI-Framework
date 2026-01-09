
#pragma once

class shaderParser{
private:
    unsigned int shader_id_vertex;
    unsigned int shader_id_fragment;
    unsigned int program_id;
    
    std::string shader_Source_Vertex;
    std::string shader_Source_fragment;
    
public:
    shaderParser();
    ~shaderParser();
    
    std::tuple<std::string, std::string> shaderParse(std::string shaderPath);
    unsigned int shaderCompilation(std::string& shaderSource, unsigned int shaderType);
    unsigned int  shaderCreation(std::string shaderFilePath);
    
    void useShader();
    
    void SetUniformVariables1i(std::string& nameOfUniformVariable, int data);
    
    unsigned int getPorogramID();
};
