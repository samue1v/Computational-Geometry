// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl
//#include "vec2.hpp"
#include <string>
//#include "objUtils.h"
#include <fstream>
#include "../graham.hpp"
#include <SDL2/SDL.h> 

bool sdlnit(){
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
    if (!(sdlnit())){
        return 0;
    }

    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("Convex Hull SDL2",0, 0, 640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    //leitura do obj
    std::string filename = "../fixedcat.obj";
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

    int cout=0;
    std::vector<Vec2> ch;
    graham(bh.obj2D[0].points2D,ch);
    std::cout<<"pontos do fecho:\n";
    for(auto v: ch){
        OUT << "v "<<v[0]<<" " <<v[1] << std::endl;
        std::cout << "("<<v[0]<<"," <<v[1] << ")"<<std::endl;
    }

    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;
    OUT.close();

        // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        double scale = 30;
        double dx = 320.0;
        double dy = 340.0;
        // Do our drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        int size = ch.size();
        for (auto v : bh.obj2D[0].points2D){
        SDL_RenderDrawPoint(renderer, (v[0]*scale+dx),(-v[1]*scale+dy));
        }
        for (int i=0; i<size;i++){
            int index = i%(size);
            std::cout<<"printing "<<index<<" to "<<(index+1)%size <<" edge..."<<std::endl;
            SDL_RenderDrawLine(renderer,(ch[index][0]*scale+dx),(-ch[index][1]*scale+dy),(ch[(index+1)%size][0]*scale+dx),(-ch[(index+1)%size][1]*scale+dy));
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
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