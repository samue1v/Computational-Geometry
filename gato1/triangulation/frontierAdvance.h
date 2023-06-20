#include <iostream>
#include <random>
#include "../vec2.hpp"
#include "../objUtils.h"
#include <queue>
#include <utility>
#include <vector>

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
        for (int i=0; i<adjacencyMatrix.size(); i++ ){
            for (int j=0; j<adjacencyMatrix.size(); j++ ){
                    //condição 1: o ponto está no lado esquerdo da aresta
                    //condição 2: as novas arestas geradas não interceptam arestas existentes (circulo de delaunay)
                    if (crossCompare(currentEdge.first, currentEdge.second,adjacencyMatrix[i][j]) && ){

                    }
            }
        }
        
        if (isChecked(currentEdge, adjacencyMatrix)) {
            queue.pop();
        }
    }
}