Arquivos na pasta gato1/sdl, incluindo a saída como .obj no arquivo mergedhullcat.obj

Passos para rodar o trabalho 1:

Compile o arquivo desejado na pasta gato1/sdl ou gato1/triangulation.

Instruções para compilar o arquivo sdl:

On linux compile with:

g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl

On windows compile with (if using mingw)

g++ main.cpp -o prog.exe -lmingw32 -lSDL2main -lSDL2

On Mac compile with:

clang++ main.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2
