#include "../objUtils.h"
#include <fstream>

int main(){
    //leitura do obj
    std::string filename = "entrada.obj"; //obj qualquer
    std::ofstream OUT;
    OUT.open("saida_teste.obj");
    OUT << "o gatodoido\n";
    ObjUtils bh,ah;
    bh.readFromFile2D(filename);
    int size = bh.obj2D[0].points2D.size();
    //std::cout<<"pontos lidos pelo utils:\n";
    for(int i=0; i< size;i++){
        std::cout << "("<<bh.obj2D[0].points2D[i][0]<<"," <<bh.obj2D[0].points2D[i][1] << ")"<<std::endl;
    }

    if (bh.obj2D[0].points2D[size-1] == bh.obj2D[0].points2D[size-2] ){
        std::cout << "copiou as 2 ultimas!!\nvalores dos pontos: \n"<< bh.obj2D[0].points2D[size-1] << bh.obj2D[0].points2D[size-2] ;
    } else {
        std::cout<<"2 ultimas nao sao iguais!!"<<std::endl;
    }
    return 0;
}