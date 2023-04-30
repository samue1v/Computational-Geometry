#include <iostream>
#include <vector>
#include <algorithm>
#include "util.hpp"
#include "genVecs.hpp"


struct vec2Angle{
    public:
        vec2Angle(Vec2 v1){
            v = v1;
        }
        Vec2 v;
        double angle;
        bool operator < (const vec2Angle& v2) const{
            return (angle < v2.angle);
        }

        friend std::ostream& operator<<(std::ostream &out, const vec2Angle & vec) {
            return out << vec.v[0] << ' ' << vec.v[1]  << ' ' <<  vec.angle <<std::endl;
        }
};

double getSquareAngle(double x,double y){
    if( y >= 0){
        if(x >= 0){
            if(x >= y){
                return y/x;
            }
        return 2 - x/y;
        }
    if(-x <= y){
        return 2 + (-x)/y;
    }
    return 4 - y/(-x); 
    }
    if(x<0){
        if(-x >= -y){
            return 4 + (-y)/(-x);
        }
        return 6 - (-x)/(-y);
    }
    if(x<=-y){
        return 6 + x/(-y);
    }
    return 8 - (-y)/x;
}

void unitSquareSort(std::vector<vec2Angle> & vec){
    double x,y,angle;
    for(int i = 0; i<vec.size();i++){
        x = vec[i].v.x();
        y = vec[i].v.y();
        angle = getSquareAngle(x,y);
        vec[i].angle = angle;
    }
    std::sort(vec.begin(),vec.end());
}

void unitCircleSort(std::vector<vec2Angle> & vec){
 
}

int main(){
    std::vector<Vec2> vec;
    std::vector<vec2Angle> vecAngleSquare;
    std::vector<vec2Angle> vecAngleCircle;
    genVectors(vec);
    for(int i = 0;i<MAX_POINTS;i++){
        vecAngleSquare.push_back(vec2Angle(vec[i]));
        vecAngleCircle.push_back(vec2Angle(vec[i]));
    }

    unitSquareSort(vecAngleSquare);
    unitCircleSort(vecAngleCircle);

    writeOBJ("points.obj",vec);

    for(auto i : vecAngleSquare){
        std::cout<<i;
    }
}