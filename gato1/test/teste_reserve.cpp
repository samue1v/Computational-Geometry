//#include "vec2.hpp"
#include <string>
#include <algorithm>
//#include "objUtils.h"
#include "graham.hpp"

int main(){
    std::string filename = "../gato2d_input.obj";
    ObjUtils util, utilOutput;
    util.readFromFile2D(filename);
    utilOutput.obj2D.reserve(util.obj2D.size());
    utilOutput.obj2D.resize(util.obj2D.size());
    // utilOutput.obj2D[0] = util.obj2D[0];
    std::vector<Vec2> points;
    for (int i = 0; i<util.obj2D.size(); i++){
        points = util.obj2D[i].points2D;
        utilOutput.obj2D[i].points2D = points;
    }
    std::cout << "passa por aqui";
    // util.writeToFile2D("testoutput.obj");
    return 0;
}