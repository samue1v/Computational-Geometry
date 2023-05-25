#include "vec2.hpp"
#include <string>
#include "objUtils.h"

int main(){
    std::string filename = "gato2d_input.obj";
    ObjUtils obj;
    obj.readFromFile2D(filename);
    //std::cout<<obj.obj2D[obj.obj2D.size()-1].name;
    obj.writeToFile2D("testoutput.obj");

}