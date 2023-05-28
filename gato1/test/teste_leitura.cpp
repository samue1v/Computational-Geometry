#include "../objUtils.h"
#include <fstream>

int main(){
    /*
    //leitura do obj
    std::string filename = "entrada.obj"; //obj qualquer
    std::ofstream OUT;
    OUT.open("saida_teste.obj");
    OUT << "o gatodoido\n";
    ObjUtils bh,ah;
    bh.readFromFile2D(filename);
    int size = bh.obj2D[0].points2D.size();
    //std::cout<<"pontos lidos pelo utils:\n";
    Vec2 prev;
    Vec2 atual;
    for(int i=0; i< size;i++){
        bool repetiu = false;
        atual = bh.obj2D[0].points2D[i];
        std::cout << "("<<atual[0]<<"," <<atual[1] << ")"<<std::endl;
        if (prev == atual){
            std::cout<<"2 pontos iguais!! " << i <<" e " <<i-1;
        }
    }

    if (bh.obj2D[0].points2D[size-1] == bh.obj2D[0].points2D[size-2] ){
        std::cout << "copiou as 2 ultimas!!\nvalores dos pontos: \n"<< bh.obj2D[0].points2D[size-1] << bh.obj2D[0].points2D[size-2] ;
    } else {
        std::cout<<"2 ultimas nao sao iguais!!"<<std::endl;
    }*/

    ObjUtils util;
    util.readFromFile2D("../fixedcat_div.obj");
    util.writeToFile2D("testesaida.obj");

    return 0;
}