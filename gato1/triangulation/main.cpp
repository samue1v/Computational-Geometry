// On linux compile and run with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl ; ./prog
//#include "vec2.hpp"
#include <string>
//#include "objUtils.h"
#include <fstream>
#include "frontierAdvance.h"
#include <SDL2/SDL.h> 

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
    std::string filename = "newHand3TESTE.obj";//"sortedcat_internals.obj";//"gato_samuel.obj";//"../sdl/mergedhullcat.obj";/*"triang_test.obj";*/
    std::ofstream OUT;
    OUT.open("saida.obj");
    OUT << "o gatodoido\n";
    ObjUtils bh,ah;
    bh.readFromFile2D(filename);

    std::cout<<"pontos lidos pelo utils:\n";
    for(auto v: bh.obj2D[0].points2D){
        //OUT << "v "<<v[0]<<" " <<v[1] << std::endl;
        std::cout << "("<<v[0]<<"," <<v[1] << ")"<<std::endl;
    }

    FrontierAdvance frontAdv = FrontierAdvance(bh.obj2D[0]);
    frontAdv.makeTriangulation();
    std::vector<std::pair<int,int>> triangulation = frontAdv.triangulation;
    std::vector<Vec2> vertexList = frontAdv.vertexList;
    /*std::cout<<"pontos do fecho:\n";
    for(auto v: ){
        OUT << "v "<<v[0]<<" " <<v[1] << std::endl;
        std::cout << "("<<v[0]<<"," <<v[1] << ")"<<std::endl;
    }*/

    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;
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
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        int size = triangulation.size();
        for (auto v : bh.obj2D[0].points2D){
        SDL_RenderDrawPoint(renderer, (v[0]*scale+dx),(-v[1]*scale+dy));
        }
        for (int i=0; i<size;i++){
            std::pair<int,int> index = triangulation[i];
            std::cout<<"printing "<<index.first<<" to "<<index.second<<" edge..."<<std::endl;
            SDL_RenderDrawLine(renderer,(vertexList[index.first][0]*scale+dx),(-vertexList[index.first][1]*scale+dy),(vertexList[index.second][0]*scale+dx),(-vertexList[index.second][1]*scale+dy));
            SDL_Delay(100);
            
            SDL_RenderPresent(renderer);
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