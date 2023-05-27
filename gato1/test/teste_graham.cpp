#include "graham.hpp"

bool checkHull(const std::vector<Vec2> hull){
    for (auto v : hull){
        if (!(v == Vec2(1.0,1.0) || v == Vec2(-1.0,1.0) || v == Vec2(1.0,-1.0) || v == Vec2(-1.0,-1.0))  ){
            return false;
        } 
    }
    return true;
}

int main(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    std::vector<Vec2> cloud;
    std::vector<Vec2> ch;
    int j = 0;
    while(true){
        std::cout<<"================================iteração "<< j++ << "================================================\n";
        cloud.push_back(Vec2(1,1));
        cloud.push_back(Vec2(1,-1));
        cloud.push_back(Vec2(-1,1));
        cloud.push_back(Vec2(-1,-1));
        //adição de pontos aleatórios

        for(int i=0;i<10;i++){
            cloud.push_back(Vec2(dist(mt)*2 -1,dist(mt)*2-1));    
        }
        graham(cloud,ch);

        /*for (auto v : cloud){
                std::cout<<"angulo: " << pseudoAngleSquare(v) << " Ponto: " << v;
        }*/

        if (!checkHull(ch)){
            std::cout<<"deu errado!\n";
            for (auto v : ch){
                std::cout<<"angulo: " << pseudoAngleSquare(v) << " Ponto: " << v;
            }
            break;
        }
        
        cloud.clear();
        ch.clear();
    }
    return 0;
}