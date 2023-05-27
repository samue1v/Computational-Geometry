//#include "vec2.hpp"
#include <string>
//#include "objUtils.h"
#include <fstream>
#include "../graham.hpp"

int main(){
    //std::string filename = "../gato2d_input.obj";
    std::string filename = "../fixedcat.obj";
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

    //for (int i = 0;i<bh.obj2D.size();i++/*auto object : obj.obj2D*/){
    //    std::cout << "iteração "<<cout++ << std::endl;
    //    graham(bh.obj2D[i].points2D, ch);
    //    for(auto v : ch){
    //        std::cout<<v<<std::endl;
    //    }
    //    ch.reserve(0);
    //    ch.resize(0);
    //    ah.obj2D[i].points2D = std::move(ch);
    //    ah.obj2D[i].name = bh.obj2D[i].name;
    //}
    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;
    OUT.close();
    //ah.writeToFile2D("testoutput.obj");
    return 0;
}