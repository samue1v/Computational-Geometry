#include "graham.hpp"

bool checkHull(const std::vector<Vec2> hull){
    for (auto v : hull){
        if (v == Vec2(1.0,1.0) || v == Vec2(-1.0,1.0) v == Vec2(1.0,-1.0) v == Vec2(-1.0,-1.0)  ){
            
        }
    }
}

int main(){
    int i=0;
    while(i<100){
    i++;
    std::vector<Vec2> cloud = {Vec2(1,1),Vec2(-1,-1),Vec2(1,-1),Vec2(-1,1)};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    //adição de pontos aleatórios
    for(int i;i<10;i++){
        cloud.push_back(Vec2(dist(mt)*2 -1,dist(mt)*2-1));    
    }

    std::vector<Vec2> ch;
    graham(cloud,ch);
    for (auto v : ch){
        std::cout << "angulo: " << pseudoAngleSquare(v) << " pontos: "<< v ;
    }
    return 0;
    }
}