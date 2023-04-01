#include "wykobi/wykobi.hpp"
#include "wykobi/wykobi_utilities.hpp"
#include "wykobi/wykobi_algorithm.hpp"
#include "util.hpp"

int main(){

    
    wykobi::polygon<double,2> polygon;
  
    parseOBJ("crownDef.obj",polygon);

    std::vector<wykobi::triangle<double,2>> triangle_list;

    wykobi::algorithm::polygon_triangulate<wykobi::point2d<double>>(polygon, std::back_inserter(triangle_list));
    std::cout<<"entrei\n";  
    for(auto i : triangle_list){
        std::cout<< i <<std::endl;
    }
    return 0;
}