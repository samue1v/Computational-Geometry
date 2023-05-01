#include <iostream>
#include <vector>
#include "vec2.hpp"

bool pointOnPolygonTiro(const std::vector<Vec2> & Polygon, Point2 pointHor0){
    double bigDouble = 100000000; //algum double muito grande para formar o segmento point - point2
    Vec2 pointHor1 = Vec2(bigDouble,pointHor0.y());
    int index = 1;
    int counter = 0;
    while(index<Polygon.size()-1){
        Vec2 p0 = Polygon[index];
        Vec2 p1 = Polygon[(index+1)%Polygon.size()];
        if(p0.y() == pointHor0.y()){
            double k = cross(p1-p0,pointHor1 - pointHor0) * cross(p0 - Polygon[index-1],pointHor1 - pointHor0);
            if(k < 0){
                ++counter;
                ++index;
            }
        }
        else if(p0.y() == pointHor1.y()){
            double k = cross(p1-p0,pointHor1 - pointHor0) * cross(p0 - Polygon[index+1],pointHor1 - pointHor0);
            if(k < 0){
                ++counter;
                ++index;
            }
        }
        else{
            if(segmentIntersect(p0,p1,pointHor0,pointHor1)){
                ++counter;
            }
        }
        ++index;

    }
    if(counter % 2 ==0){
        return false;
    }
    return true;
}

bool PointOnPolygonRotacao(const std::vector<Vec2> & Polygon, Vec2 pc){
    Vec2 v0,v1;
    double av0,av1;
    double angle = 0;
    for(int i = 0;i<Polygon.size();++i){
        v0 = Polygon[i] - pc;
        v1 = Polygon[(i+1)%Polygon.size()] -pc;
        av0 = atan2(v0.y(),v0.x());
        av1 = atan2(v1.y(),v1.x());
        angle += std::abs(av1-av0);
    }
    if(angle == 2* M_PI){
        return true;
    }
    return false;
}

int main(){
    return 1;
}