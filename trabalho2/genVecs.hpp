#ifndef GEN_VECS_H
#define GEN_VECS_H

#include <iostream>
#include <vector>
#include "vec2.hpp"
#include <fstream>
#include <random>

#define MAX_POINTS 10

Vec2 getXPointOnCirc(double y){
    return Vec2(std::sqrt(1-y*y) , y);
}

Vec2 getYPointOnCirc(double x){
    return Vec2(x , std::sqrt(1-x*x));
}

void genVectors(std::vector<Vec2> & vec){
    const double lower_bound = -1;
    const double upper_bound = 1;

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    
    std::random_device rand_dev;

    std::mt19937 rand_engine(rand_dev()); 

    for(int i = 0;i<MAX_POINTS/2;i++){
        vec.push_back(getYPointOnCirc(unif(rand_engine) * std::pow(-1.0,i)));
    }   

    for(int i = 0;i<MAX_POINTS/2;i++){
        vec.push_back(getXPointOnCirc(unif(rand_engine) * std::pow(-1.0,i)));
    } 
}


#endif