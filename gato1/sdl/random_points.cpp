// On linux compile and run with:
// g++ -std=c++17 random_points.cpp -o prog_random_points -lSDL2 -ldl ; ./prog_random_points
//#include "vec2.hpp"
#include <string>
//#include "objUtils.h"
#include <fstream>
#include "../graham.hpp"
#include <SDL2/SDL.h> 
#define HEIGHT 640
#define WIDTH 480

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
    window = SDL_CreateWindow("Convex Hull SDL2",0, 0, HEIGHT,WIDTH,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    std::ofstream OUT;
    OUT.open("saida.obj");
    OUT << "o gatodoido\n";

    // geração de pontos aleatórios
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    std::vector<Vec2> cloud;
    std::cout<<"pontos gerados:\n";
    for(int i=0; i<100; i++){
        //OUT << "v "<<v[0]<<" " <<v[1] << std::endl;
        cloud.push_back(Vec2(dist(mt)*440,dist(mt)*280));    
        std::cout << "("<<cloud[i][0]<<"," <<cloud[i][1] << ")"<<std::endl;
    }

    int cout=0;
    std::vector<Vec2> ch;
    graham(cloud,ch);
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
        double scale = 1;
        double dx = HEIGHT/2 - 440/2;
        double dy = WIDTH/2 - 280/2;
        // Do our drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        int size = ch.size();
        for (auto v : cloud){
        SDL_RenderDrawPoint(renderer, (v[0]*scale+dx),(v[1]*scale+dy));
        }
        SDL_Delay(1000);
        for (int i=0; i<size;i++){
            int index = i%(size);
            std::cout<<"printing "<<index<<" to "<<(index+1)%size <<" edge..."<<std::endl;
            SDL_RenderDrawLine(renderer,(ch[index][0]*scale+dx),(ch[index][1]*scale+dy),(ch[(index+1)%size][0]*scale+dx),(ch[(index+1)%size][1]*scale+dy));
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