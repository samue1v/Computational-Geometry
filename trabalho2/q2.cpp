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
            return out << vec.v[0] << ' ' << vec.v[1] <<std::endl;
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

double getCircleAngle(double x, double y){
    double inc = 0;
    double xdir = 1;

   if(y>0){
        if(x<0){
            xdir = -1;
            inc = std::sqrt(2.0);
        }
    }
    else if(x<0){
        xdir = -1;
        inc = 2.0*std::sqrt(2.0);
    }
    else{
        inc = 3.0*std::sqrt(2.0);
    }
    double area = ((xdir-x)*y/2.0);
    return area + inc;

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
    double x,y,angle;
    for(int i = 0; i<vec.size();i++){
        x = vec[i].v.x();
        y = vec[i].v.y();
        angle = getCircleAngle(x,y);
        vec[i].angle = angle;
    }
    std::sort(vec.begin(),vec.end());
}

int main(){
    std::ofstream file;
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

    //writeOBJ("points.obj",vec);

    file.open("squaresort.txt");
    for(int i = 0;i<vecAngleSquare.size();i++){
        //std::cout<<"Square Sort:\n";
        //std::cout << i <<": " << vecAngleSquare[i];
        file << i <<": " << vecAngleSquare[i];
    }
    file.close();

    file.open("circlesort.txt");
    for(int i = 0;i<vecAngleCircle.size();i++){
        //std::cout<<"Circle Sort:\n";
        //std::cout << i <<": " << vecAngleCircle[i];
        file << i <<": " << vecAngleCircle[i];
    }
    file.close();
    
}