// On linux compile and run with:
// g++ -std=c++17 merge.cpp -o merge -lSDL2 -ldl ; ./merge
//#include "vec2.hpp"
#include <string>
//#include "objUtils.h"
#include <iostream>
#include "frontierAdvance.h"
#include <SDL2/SDL.h> 
#include <bits/stdc++.h>

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

bool sdlInit(){
if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
                  return false;
    }
     std::cout << "SDL video system is ready to go\n";
     return true;
}
int main(){
    //inicialização do sdl
    SDL_Window* window=nullptr;
    if (!(sdlInit())){
        return 0;
    }

    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("Convex Hull SDL2",0, 0, 640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    //leitura do obj
    std::string filename = "sortedcat_div_internals.obj";//"sortedcat_div_internals.obj";//"gato_samuel.obj";//"../sdl/mergedhullcat.obj";/*"triang_test.obj";*/
    std::ofstream OUT;
    //std::ofstream edges; 

    OUT.open("saida.obj");
    OUT << "o gatodoido\n";
    ObjUtils utils;
    utils.readFromFile2D(filename);
    std::vector<std::vector<std::pair<int,int>>> triangulationList;
    std::vector<Vec2> T; 
    int index=0;
    std::cout<<utils.obj2D[1].points2D.size()<<std::endl;
    int vertexUntilNow = 0;
    //exit(-1);
    //calcular a triangulação pra todos os obj separados 
    for (auto object : utils.obj2D){
        std::cout<< "entrou\n";
        index++;
        for(int p = 0;p<object.line.size();p++){
            object.line[p].first -= vertexUntilNow;
            object.line[p].second -= vertexUntilNow;
        }
        vertexUntilNow += object.points2D.size();
        FrontierAdvance frontAdv = FrontierAdvance(object);
        std::cout << "====objeto "<<index<<": calculo triangulação====\n";
        frontAdv.makeTriangulation();
        std::vector<std::pair<int,int>> triangulation = frontAdv.triangulation;
        for (int i=0;i<triangulation.size();i++) {
            triangulation[i].first = addInsideTotal(T, object.points2D[triangulation[i].first]);
            triangulation[i].second = addInsideTotal(T, object.points2D[triangulation[i].second]);
        } 
        triangulationList.push_back(triangulation);
        std::cout<< "saiu\n";
    }
    //exit(-1);

    for (auto v : T){
        OUT << "v "<<v[0]<<" " <<v[1] << std::endl;
    }

    std::vector<std::vector<bool>> adjacentMatrix(T.size(),std::vector<bool>(T.size(),false));
    for (auto triangulation : triangulationList) {
        for (auto e : triangulation){
            if (adjacentMatrix[e.first][e.second] == false){
                adjacentMatrix[e.first][e.second] = true;
                adjacentMatrix[e.second][e.first] = true;
                OUT << "l "<<e.first+1<<" " <<e.second+1<< std::endl;
            }
        }
    }

    std::cout << "=========================== fim do calculo da triangulação =========================== " << std::endl;
    //OUT << edges;
    OUT.close();

        // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop

        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        double scale = 60;
        double dx = 360;//320.0;
        double dy = 440;//340.0;
        // Do our drawing
        // todos os pontos
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        for (auto v : T){
            SDL_RenderDrawPoint(renderer, (v[0]*scale+dx),(-v[1]*scale+dy));
        }
        // todas as arestas 

        SDL_SetRenderDrawColor(renderer,27,216,100,SDL_ALPHA_OPAQUE);
        for (int i=0; i<triangulationList.size();i++){
            auto triangulation = triangulationList[i];
            for (int j=0;j<triangulation.size();j++){
                std::pair<int,int> index = triangulation[j];
                std::cout<<"printing "<<index.first<<" to "<<index.second<<" edge..."<<std::endl;
                SDL_RenderDrawLine(renderer,(T[index.first][0]*scale+dx),(-T[index.first][1]*scale+dy),(T[index.second][0]*scale+dx),(-T[index.second][1]*scale+dy));
                SDL_Delay(20);
                SDL_RenderPresent(renderer);
            }

            while(SDL_PollEvent(&event)){
                // Handle each specific event
                if(event.type == SDL_KEYDOWN){
                    gameIsRunning= false;
                }
            }
            if(!gameIsRunning){break;}
        }
        std::cout<<"===============restarting drawing...===============\n";
        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    return 0;
}