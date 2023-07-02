#ifndef FRONTIERADVANCE_H
#define FRONTIERADVANCE_H
#include <iostream>
#include <random>
#include "../vec2.hpp"
#include "../objUtils.h"
#include <queue>
#include <utility>
#include <vector>
#include "../matrix.h"
#define MAX_TOLERANCE 100.0

class FrontierAdvance {
    public:
        FrontierAdvance();
        FrontierAdvance(Object2D & obj2D);
        void getAllValidVertexes(const std::pair<int,int> & edge);
        void check(const std::pair<int,int> & edge);
        bool isDone(const std::pair<int,int> & edge);
        void makeTriangulation();
        int delaunay(const std::pair<int,int> & edge);
        std::vector<std::pair<int,int>> triangulation;
        std::vector<Vec2> vertexList;
    private:
        Object2D obj2D;
        std::vector<std::vector<int>> adjacencyMatrix;
};


double angle(Vec2 p, Vec2 r, Vec2 q){
    return dot(unit(p - r),unit(q - r));
}

bool crossCompare(Vec2 p, Vec2 c, Vec2 n){
    double s = cross(c - p, n - c);
    if(s>=0){
        return true;
    }
    return false;
}

bool pointInCircle(Vec2 a, Vec2 b, Vec2 c, Vec2 p, double tolerance){
    double deter = Matrix<double,4,4>(std::vector<double>({a[0], a[1], a[0]*a[0]+a[1]*a[1], 1,
                                                b[0], b[1], b[0]*b[0]+b[1]*b[1], 1,
                                                c[0], c[1], c[0]*c[0]+c[1]*c[1], 1,
                                                p[0], p[1], p[0]*p[0]+p[1]*p[1], 1})).det();
    // if(deter>0){std::cout<<"Determiant: "<<deter<<"\n";}
    //experimentando mudar a tolerancia.
    return deter >= tolerance? true : false;
}

FrontierAdvance::FrontierAdvance(){}

FrontierAdvance::FrontierAdvance(Object2D & obj2D){
    this->obj2D = obj2D;
    this->vertexList = obj2D.points2D;
    int n = vertexList.size();
    this->adjacencyMatrix = std::vector<std::vector<int>>(n,std::vector<int>(n,0)); 
    
    std::cout<<obj2D.line.size()<<std::endl;
    std::cout<<obj2D.points2D.size()<<std::endl;
    for(int i=0;i<obj2D.line.size();i++){
        adjacencyMatrix[obj2D.line[i].first-1][obj2D.line[i].second-1] = 1;
        adjacencyMatrix[obj2D.line[i].second-1][obj2D.line[i].first-1] = 1;
        //std::cout << "("<<vertexList[obj2D.line[i].first-1][0]<<"," <<vertexList[obj2D.line[i].first-1][1] << ")"<<std::endl;
        //std::cout<<obj2D.line[i].first-1<<","<<obj2D.line[i].second-1<<std::endl;
    }
    std::cout<<"====dentro do construtor=====\n";
    //exit(-1);
}

void FrontierAdvance::check(const std::pair<int,int> & edge){
    adjacencyMatrix[edge.first][edge.second]+=1;
    adjacencyMatrix[edge.second][edge.first]+=1;
}

bool FrontierAdvance::isDone(const std::pair<int,int> & edge){
    return adjacencyMatrix[edge.first][edge.second] >= 2 ? true : false;
}

int FrontierAdvance::delaunay(const std::pair<int, int>& edge) {
    int bestVertex = -1;
    double bestAngle = 1;
    bool found = false;
    double tolerance = 0.0;
    std::cout<<"Testando aresta: "<< "(P1:"<< edge.first << ","<< "P2:"<<edge.second<<")\n";
    while (!found){
            for (int i = 0; i < vertexList.size(); i++) {
            bool valid = true;
            //std::cout<<"Ponto i testado: " << i <<"\n";
            if (crossCompare(vertexList[edge.first], vertexList[edge.second], vertexList[i])) {
                for (int j = 0; j < vertexList.size(); j++) {
                    if (i != j && vertexList[j] != vertexList[edge.first] && vertexList[j] != vertexList[edge.second] && pointInCircle(vertexList[edge.first], vertexList[edge.second], vertexList[i], vertexList[j], 0/*tolerance*/)) {
                        //std::cout<<"Ponto j invalidado: " << j << std::endl;
                        valid = false;
                        break;
                    }
                }
                if (valid){
                    double currentAngle = angle(vertexList[edge.first], vertexList[i], vertexList[edge.second]);
                    std::cout<<"validado!!\n";
                    if (currentAngle <= bestAngle) {
                        bestAngle = currentAngle;
                        bestVertex = i;
                        found = true;
                    }
                }
            }
        }
        if (!found){
            tolerance+=0.1;
        }
        if (tolerance >= MAX_TOLERANCE){
            std::cout<<"tolerancia maxima atingida\n"; 
            return bestVertex;
        }
    }
    return bestVertex;
}

void FrontierAdvance::makeTriangulation(){
    //  adiciona as arestas na fila
    std::queue<std::pair<int,int>> queue;
    for(auto e : obj2D.line){
        e.first--;
        e.second--;
        queue.push(e);
    }
    std::cout<<"tamanho da fila: "<<queue.size()<<"\n";
    // vai esvaziando a fila, enquanto vai adicionando as novas arestas geradas 
    while (!queue.empty()){
        auto currentEdge = queue.front();
        if (isDone(currentEdge)) {
            queue.pop();
            continue;
        };
        int i = delaunay(currentEdge);
        if (i<0){
            std::cout<<"erro na aresta " << currentEdge.first << ", " << currentEdge.second<<std::endl; 
        }
        std::cout<<"melhor vertice: "<<i<<"\n";

        std::pair<int,int> newEdge1(currentEdge.first, i);
        std::pair<int,int> newEdge2(i, currentEdge.second);
        check(newEdge1);
        check(newEdge2);
        check(currentEdge);
        if(!isDone(newEdge1)){
            //triangulation.push_back(newEdge1);
            queue.push(newEdge1);
        }
        if(!isDone(newEdge2)){
            //triangulation.push_back(newEdge2);
            queue.push(newEdge2);
        }
        triangulation.push_back(newEdge1);
        triangulation.push_back(newEdge2);
        triangulation.push_back(currentEdge);
    }
}

#endif