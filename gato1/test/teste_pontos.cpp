//#include "vec2.hpp"
#include <string>
#include <algorithm>
//#include "objUtils.h"
#include "graham.hpp"

int main(){
    std::string filename = "../gato2d_input.obj";
    ObjUtils obj;
    obj.readFromFile2D(filename);
    std::vector<Vec2> ch;
    std::vector<Object2D> tempObjList;
    int cout=0;
    for (auto object : obj.obj2D){
        std::cout << "iteração "<<cout++ << std::endl;
        graham(object.points2D, ch);
        object.points2D = ch;
        tempObjList.push_back(object);
    }
    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;
    std::copy(tempObjList.begin(), tempObjList.end(), obj.obj2D.begin());
    std::cout << "passa por aqui";
    obj.writeToFile2D("testoutput.obj");
    return 0;
}