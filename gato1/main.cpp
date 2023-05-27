#include "graham.hpp"
#include <fstream>
#include <string>

int main(){


    //std::vector<Vec2> cloud = {Vec2(1,1),Vec2(-1,-1),Vec2(1,-1),Vec2(-1,1)};
    //std::vector<Vec2> cloud = {Vec2(0.259385,-0.345199),Vec2(1,-1),Vec2(0.810757,0.276404),Vec2(1,1),Vec2(-1,1),Vec2(-1,-1),Vec2(-0.459101,-0.82045)};
    /*std::vector<Vec2> cloud = {Vec2(1,1),Vec2(-1,-1),Vec2(1,-1),Vec2(-1,1),  
        Vec2(-0.992587, -0.816825), 
        Vec2(-0.937301, 0.14279), 
        Vec2(-0.344649, -0.0237413), 
        Vec2(-0.301262, -0.0451829), 
        Vec2(-0.529533, 0.442845), 
        Vec2(-0.446829, 0.331714)};
        
    */
    std::string filename = "gatojoin.obj";
    std::ofstream OUT;
    OUT.open("saida.obj");
    OUT << "o gatodoido\n";
    ObjUtils bh,ah;
    bh.readFromFile2D(filename);
    
    int cout=0;
    std::vector<Vec2> ch;
    graham(bh.obj2D[0].points2D,ch);
    for(auto v: ch){
        OUT << "v "<<v[0]<<" " <<v[1] << std::endl;
    }
    OUT.close();
    return 0;
}