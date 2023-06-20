#include <iostream>
#include <random>
#include "../vec2.hpp"
#include "../objUtils.h"
#include <queue>
#include <utility>
#include <vector>

bool checkIntersection(const std::pair<int,int> edge, Vec2 vertex, std::vector<std::vector<int>> & adjacencyMatrix){
    //checa se existe alguma interseção com alguma aresta antiga com as arestas geradas pela aresta atual e o vértice
    //segmentIntersect do Vec2 checa pra gente se há interseção entre 2 arestas 
}

bool check(const std::pair<int,int> edge, std::vector<std::vector<int>> & adjacencyMatrix){
    adjacencyMatrix[edge.first][edge.second]++;
    adjacencyMatrix[edge.second][edge.first]++;
    return true;
}

bool invalidate(const std::pair<int,int> edge, std::vector<std::vector<int>> & adjacencyMatrix){
    adjacencyMatrix[edge.first][edge.second] = -1;
    adjacencyMatrix[edge.second][edge.first] = -1;
}

bool isInvalid(const std::pair<int,int> & edge, const std::vector<std::vector<int>> & adjacencyMatrix){
    return adjacencyMatrix[edge.first][edge.second] == -1 ? true : false;
}

bool isChecked(const std::pair<int,int> & edge, const std::vector<std::vector<int>> & adjacencyMatrix){
    return adjacencyMatrix[edge.first][edge.second] == 2 ? true : false;
}

void buildAdjacencyMatrix (const std::vector<Vec2> & pointCloud, std::vector<Vec2> & convexHull ){

}

void frontierAdvance(std::vector<std::vector<int>> & adjacencyMatrix, std::vector<std::vector<int>> triangulation){
    //  adiciona as arestas na fila
    std::queue<std::pair<int,int>> queue;

    // vai esvaziando a fila, enquanto vai adicionando as novas arestas geradas 
    while (!queue.empty()){
        auto currentEdge = queue.front();
        bool foundVertex = false;
        int i = 0;
        while(!foundVertex || i >= vertexList.size()){
            //condição 1: o ponto está no lado esquerdo da aresta
            //condição 2: as novas arestas geradas não interceptam arestas existentes (circulo de delaunay)
            if (crossCompare(vertexList[currentEdge.first],vertexList[currentEdge.second], vertexList[i]) && !(checkIntersection(currentEdge, vertexList[i], adjacencyMatrix))){
                check(currentEdge, adjacencyMatrix);
                //check(std::pair<int,int> (currentEdge.first, i),adjacencyMatrix);
                //check(std::pair<int,int> (i, currentEdge.second),adjacencyMatrix);
                //queue.push() pra ambas as arestas
                foundVertex = true;
            }
            // invalida a aresta, pq existe interseção entre alguma coisa e ela
            // invalidate(currentEdge, adjacencyMatrix);
            i++;
        }
        
        if (isChecked(currentEdge, adjacencyMatrix)) {
            queue.pop();
        }
    }
}