#include "../graham.hpp"

int main(){
std::cout << "angulos\n" 
<< "\nresultado para (3.90843,6.23384): "<< get_angle(Vec2(3.66365,6.40671),Vec2(3.90843,6.23384))
<< "\nresultado para  (3.66365,6.40671): "<< get_angle(Vec2(3.66365,6.40671),Vec2(3.66365,6.40671))
<< "\nresultado para  (4.04756,6.53103): "<< get_angle(Vec2(3.66365,6.40671),Vec2(4.04756,6.53103))
<< "\nresultado para  (3.68315,6.54739): "<< get_angle(Vec2(3.66365,6.40671),Vec2(3.68315,6.54739));
}