// On linux compile and run with:
// g++ -std=c++17 merge.cpp -o prog_merge -lSDL2 -ldl ; ./prog_merge
#include "../graham.hpp"

int main () {
    //ler o arquivo, com todos os obj

    //leitura do obj
    std::string filename = "../fixedcat_div.obj";
    ObjUtils utils;
    utils.readFromFile2D(filename);
    std::vector<Object2D> objectList;

    for (auto object : utils.obj2D){
        std::vector<Vec2> ch;
        graham(object.points2D,ch);
        object.points2D.clear();
        object.points2D.resize(0);
        object.points2D = std::move(ch);
        objectList.push_back(object);
    }
    for (int i =0; i<objectList.size(); i++){
        std::cout<<"\nobjectList["<<i<<"]\n" ;
        for(auto point: objectList[i].points2D ){
            std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
        }
        std::cout << "nome: "<< objectList[i].name <<std::endl;
    }

    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;
    //calcular o graham pra todos os obj separados

    //tenta adicionar todos os pontos num grande vetor T, adicionando sua posição em uma lista de indices respectiva ao obj, para todo obj
    //caso ja existir um ponto em T, nao adicionar e adicionar na lista de indices a posiçao ja existente em T 

   //criar uma matriz de adjacencia para T, considerando-o como um grafo, e adiciona true nos elementos i,j e j,i a partir do que está escrito nas listas de índice
   //caso exista o valor true em i,j ou em j,i, atribua false nessas posições.  

   //realizar a visualização com o SDL2
}