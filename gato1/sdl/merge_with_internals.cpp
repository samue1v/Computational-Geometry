// On linux compile and run with:
// g++ -std=c++17 merge.cpp -o prog_merge -lSDL2 -ldl ; ./prog_merge
#include "../graham.hpp"
#include <SDL2/SDL.h> 
#include <fstream>
#include <string>


bool sdlnit(){
if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
                  return false;
    }
     std::cout << "SDL video system is ready to go\n";
     return true;
}

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

int main () {
    //sdl2
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
    

    //ler o arquivo, com todos os obj

    //leitura do obj
    std::string filename = "../fixedcat_div_with_internals.obj";
    ObjUtils utils;
    utils.readFromFile2D(filename);
    std::vector<Object2D> objectList;

    //calcular o graham pra todos os obj separados 
    for (auto object : utils.obj2D){
        std::vector<Vec2> ch;
        std::cout << "====calculo fecho====\n";
        graham(object.points2D,ch);
        object.points2D.clear();
        object.points2D.resize(0);
        object.points2D = std::move(ch);
        objectList.push_back(object);
    }

    for (int i =0; i<objectList.size(); i++){
        std::cout<<"\nobjectList["<<i<<"]\n" ;
        std::cout << "nome: "<< objectList[i].name <<std::endl;
        for(auto point: objectList[i].points2D ){
            std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
        }
    }
    std::cout << "=========================== fecho sem divisões: =========================== " << std::endl;
    for (int i =0; i<objectList.size(); i++){
        for(auto point: objectList[i].points2D ){
            std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
        }
    }
    std::cout << "=========================== fim do calculo do fecho =========================== " << std::endl;

    //tenta adicionar todos os pontos num grande vetor T, adicionando sua posição em uma lista de indices respectiva ao obj, para todo obj
    //caso ja existir um ponto em T, nao adicionar e adicionar na lista de indices a posiçao ja existente em T 
    std::vector<std::vector<int>> objectIndexList(objectList.size());
    std::vector<Vec2> T; 
    for (int i=0; i<objectList.size(); i++){
        for (int j=0; j<objectList[i].points2D.size();j++){
            int index = addInsideTotal(T, objectList[i].points2D[j]);
            objectIndexList[i].push_back(index); 
        }
    }

    std::cout<<"\nresultado de T: \n" ;
    for(auto point : T){
        std::cout << "("<<point[0]<<"," <<point[1] << ")"<<std::endl;
    }

    std::cout<<"\nresultado das listas de indices: \n" ;
    for(auto objectIndex : objectIndexList  ){
        for (auto index : objectIndex){
            std::cout<<index <<"  ";
        }
        std::cout<<std::endl;
    }
   //criar uma matriz de adjacencia para T, considerando-o como um grafo, e adiciona true nos elementos i,j e j,i a partir do que está escrito nas listas de índice
   //caso exista o valor true em i,j ou em j,i, atribua false nessas posições.  
    std::vector<std::vector<bool>> adjacentMatrix(T.size(),std::vector<bool>(T.size(),false));
    for (int i=0; i<objectIndexList.size(); i++){
        for (int j=0; j<objectIndexList[i].size(); j++){
                int indexInit = objectIndexList[i][j];
                int indexFinal = objectIndexList[i][(j+1)%objectIndexList[i].size()];
                if (adjacentMatrix[indexInit][indexFinal] == true){
                    adjacentMatrix[indexInit][indexFinal] = false;
                    adjacentMatrix[indexFinal][indexInit] = false;
                } else {
                    adjacentMatrix[indexInit][indexFinal] = true;
                    adjacentMatrix[indexFinal][indexInit] = true;
                }
        }
    }
    for(auto line : adjacentMatrix  ){
        for (auto index : line){
            std::cout<<index <<"  ";
        }
        std::cout<<std::endl;
    }
   //realizar a visualização com o SDL2

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
            // pintando todos os pontos
        for (auto object : utils.obj2D){
        SDL_SetRenderDrawColor(renderer,27,216,100,SDL_ALPHA_OPAQUE);
            std::vector<Vec2> pts = object.points2D;
            int size = pts.size();
            for (auto v : object.points2D){
                SDL_RenderDrawPoint(renderer, (v[0]*scale+dx),(-v[1]*scale+dy));
            }
        }
            // pintando o fecho
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        for (auto object : objectList){
            std::vector<Vec2> ch = object.points2D;
            int size = ch.size();
            for (auto v : object.points2D){
                SDL_RenderDrawPoint(renderer, (v[0]*scale+dx),(-v[1]*scale+dy));
            }
        }
        for (int i=0; i<T.size();i++){
            for (int j=0; j<T.size();j++){
                std::cout<<"printing "<<i<<" to "<< j <<" edge..."<<std::endl;
                if (adjacentMatrix[i][j] == true){
                    SDL_RenderDrawLine(renderer,(T[i][0]*scale+dx),(-T[i][1]*scale+dy),(T[j][0]*scale+dx),(-T[j][1]*scale+dy));
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                }
            }
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