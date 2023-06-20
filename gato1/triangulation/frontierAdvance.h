#ifndef FRONTIERADVANCE_H
#define FRONTIERADVANCE_H
#include <iostream>
#include <random>
#include "../vec2.hpp"
#include "../objUtils.h"
#include <queue>
#include <utility>
#include <vector>
#include "matrix.h"

class FrontierAdvance {
    public:
        void getAllValidVertexes(const std::pair<int,int> & edge);
        bool checkIntersection(const std::pair<int,int> & edge, Vec2 vertex);
        bool check(const std::pair<int,int> & edge);
        bool invalidate(const std::pair<int,int> & edge);
        bool isInvalid(const std::pair<int,int> & edge);
        bool isDone(const std::pair<int,int> & edge);
        void buildAdjacencyMatrix(const std::vector<Vec2> & vertexList);
        void frontierAdvance();
        int delaunay(const std::pair<int,int> & edge);
        //bool crossCompare(Vec2 p, Vec2 c, Vec2 n);

    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        std::vector<Vec2> vertexList;
        std::vector<std::pair<int,int>> triangulation;
};

void FrontierAdvance::getAllValidVertexes(const std::pair<int,int> & edge){

}

bool FrontierAdvance::checkIntersection(const std::pair<int,int> & edge, Vec2 vertex){
    //checa se existe alguma interseção com alguma aresta antiga com as arestas geradas pela aresta atual e o vértice
    //segmentIntersect do Vec2 checa pra gente se há interseção entre 2 arestas 
}

bool FrontierAdvance::check(const std::pair<int,int> & edge){
    adjacencyMatrix[edge.first][edge.second]++;
    adjacencyMatrix[edge.second][edge.first]++;
    return true;
}

bool FrontierAdvance::invalidate(const std::pair<int,int> & edge){
    adjacencyMatrix[edge.first][edge.second] = -1;
    adjacencyMatrix[edge.second][edge.first] = -1;
}

bool FrontierAdvance::isInvalid(const std::pair<int,int> & edge){
    return adjacencyMatrix[edge.first][edge.second] == -1 ? true : false;
}

bool FrontierAdvance::isDone(const std::pair<int,int> & edge){
    return adjacencyMatrix[edge.first][edge.second] == 2 ? true : false;
}

void FrontierAdvance::buildAdjacencyMatrix (const std::vector<Vec2> & vertexList){

}

int FrontierAdvance::delaunay(const std::pair<int,int> & edge){

}

bool crossCompare(Vec2 p, Vec2 c, Vec2 n){
    double s = cross(c - p, n - c);
    if(s>=0){
        return true;
    }
    return false;
}



void FrontierAdvance::frontierAdvance(){
    //  adiciona as arestas na fila
    std::queue<std::pair<int,int>> queue;

    // vai esvaziando a fila, enquanto vai adicionando as novas arestas geradas 
    while (!queue.empty()){
        auto currentEdge = queue.front();
        int i = delaunay(currentEdge);
        std::pair<int,int> newEdge1(currentEdge.first, i);
        std::pair<int,int> newEdge2(i, currentEdge.second);
        queue.push(newEdge1);
        queue.push(newEdge2);
        check(currentEdge);
        /*while(!foundVertex || i >= vertexList.size()){
            //condição 1: o ponto está no lado esquerdo da aresta
            //condição 2: as novas arestas geradas não interceptam arestas existentes (circulo de delaunay)
            //condição 3: o ponto escolhido não possui nenhum ponto interno a algum circulo que contém a aresta atual e ele
            if (crossCompare(vertexList[currentEdge.first],vertexList[currentEdge.second], vertexList[i]) && !(checkIntersection(currentEdge, vertexList[i]))){
                check(currentEdge);
                //check(std::pair<int,int> (currentEdge.first, i));
                //check(std::pair<int,int> (i, currentEdge.second));
                //queue.push() pra ambas as arestas
                foundVertex = true;
            }
            // invalida a aresta, pq existe interseção entre alguma coisa e ela
            // invalidate(currentEdge);
            i++;
        }*/
        triangulation.push_back(currentEdge);
        triangulation.push_back(newEdge1);
        triangulation.push_back(newEdge2);
        if (isDone(currentEdge)) {
            queue.pop();
        }
    }
}

#endif