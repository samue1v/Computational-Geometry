#include <iostream>
#include <random>
#include "../vec2.hpp"
#include "../objUtils.h"
#include <queue>
#include <utility>
#include <vector>

bool isChecked(const std::pair<int,int> & edge, const std::vector<std::vector<int>> & adjacencyMatrix){
    return adjacencyMatrix[std::get<0>(edge)][std::get<1>(edge)] == 2 ? true : false;
}

void frontierAdvance(const std::vector<std::vector<int>> & adjacencyMatrix, std::vector<std::vector<int>> triangulation){
    //  adiciona as arestas na fila
    std::queue<std::pair<int,int>> queue;

    // vai esvaziando a fila, enquanto vai adicionando as novas arestas geradas 
    while (!queue.empty()){
        auto currentEdge = queue.front();

        // coisas

        if (isChecked(currentEdge, adjacencyMatrix)) {
            queue.pop();
        }
    }
}