
//this header file contains the Creation of the Window and the property behind it.

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Aquamarine_Window{
private:
    int64_t windowWidth, windowHeight;
    int64_t windowColor_R, windowColor_G, windowColor_B;
    double windowColor_A;
    
public:
    
    Aquamarine_Window();
    ~Aquamarine_Window();
    
    inline void CreateDefaultWindow();
    inline void CreateCustomizedWindow();
};
