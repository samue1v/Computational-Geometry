// On linux compile and run with:
// g++ -std=c++17 merge.cpp -o prog_merge -lSDL2 -ldl ; ./prog_merge
#include "../graham.hpp"

int search(const std::vector<Vec2> & T, const Vec2 point){
    for (int i=0; i<T.size();i++){
        if (point == T[i]) {return i;}
    }
    return -1;
}

int addInsideTotal(std::vector<Vec2> & T, const Vec2 point){
    int searchedIndex = search(T, point);
    if (searchedIndex == -1){
        T.push_back(point);
        return T.size()-1;
    } 
    return searchedIndex;
}

int main () {
    //ler o arquivo, com todos os obj

    //leitura do obj
    std::string filename = "../fixedcat_div.obj";
    ObjUtils utils;
    utils.readFromFile2D(filename);
    std::vector<Object2D> objectList;

    //calcular o graham pra todos os obj separados 
    for (auto object : utils.obj2D){
        std::vector<Vec2> ch;
        std::cout << "====calculo fecho====\n";
        graham(object.points2D,ch);
        object.points2D.clear();
        object.points2D.resize(0);
        object.points2D = std::move(ch);
        objectList.push_back(object);
    }

    for (int i =0; i<objectList.size(); i++){
        std::cout<<"\nobjectList["<<i<<"]\n" ;
        std::cout << "nome: "<< objectList[i].name <<std::endl;
        for(auto point: objectList[i].points2D ){
            std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
        }
    }
    std::cout << "=========================== fecho sem divisões: =========================== " << std::endl;
    for (int i =0; i<objectList.size(); i++){
        for(auto point: objectList[i].points2D ){
            std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
        }
    }
    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;

    //tenta adicionar todos os pontos num grande vetor T, adicionando sua posição em uma lista de indices respectiva ao obj, para todo obj
    //caso ja existir um ponto em T, nao adicionar e adicionar na lista de indices a posiçao ja existente em T 
    std::vector<std::vector<int>> objectIndexList(objectList.size());
    std::vector<Vec2> T; 
    for (auto object : objectList){
        for (int i=0; i<object.points2D.size();i++){
            int index = addInsideTotal(T, object.points2D[i]);
            objectIndexList[i].push_back(index); 
        }
    }

    std::cout<<"\nresultado de T: \n" ;
    for(auto point : T){
        std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
    }

    std::cout<<"\nresultado das listas de indices: \n" ;
    for(auto objectIndex : objectIndexList  ){
        for (auto index : objectIndex){
            std::cout<<index <<"  ";
        }
        std::cout<<std::endl;
    }
   //criar uma matriz de adjacencia para T, considerando-o como um grafo, e adiciona true nos elementos i,j e j,i a partir do que está escrito nas listas de índice
   //caso exista o valor true em i,j ou em j,i, atribua false nessas posições.  

   //realizar a visualização com o SDL2
}