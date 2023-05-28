#include <iostream>
#include <random>
#include "vec2.hpp"
#include "objUtils.h"
#include <deque>
#include <utility>
#include <vector>


int qsPartition(std::vector<Vec2> & vec, double ref, int first, int last)
{
    Vec2 pivot = vec[last];
    int i = (first - 1);
    Vec2 temp;
    
    for (int j = first; j <= last - 1; j++)
    {
        double p1 = pseudoAngleSquare(vec[j]);
        double p2 = pseudoAngleSquare(pivot);

        p1 < ref ? p1+=8:1;
        p2 < ref ? p2+=8:1;
        if (p1 < p2)
        {
            i++;
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
    }
    temp = vec[i+1];
    vec[i+1] = vec[last];
    vec[last] = temp;
    return (i + 1);
}
 
void quickSort(std::vector<Vec2> & vec,double ref,int first, int last)
{
    if (first < last)
    {
        int partitionPivot = qsPartition(vec,ref,first, last);
        quickSort(vec,ref,first, partitionPivot - 1);
        quickSort(vec,ref, partitionPivot + 1, last);
    }
}

bool crossCompare(Vec2 p, Vec2 c, Vec2 n){
    double s = cross(c - p, n - c);
    if(s>=0){
        return true;
    }
    return false;
}

void graham(const std::vector<Vec2> & pointCloud, std::vector<Vec2> & convexHull ){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    //adição de pontos aleatórios
    //for(int i;i<100;i++){
    //    pointCloud.push_back(Vec2(dist(mt)*2 -1,dist(mt)*2-1));    
    //}

    std::vector<Vec2> vectorPoints = pointCloud;
    std::cout<<"pontos recebidos:\n";
    std::cout<<std::endl;
    for(auto v : vectorPoints){
        std::cout << v;
    }
    int size = vectorPoints.size();
    int randPos = pointCloud.size() * dist(mt);
    //std::cout<< "Ponto de inicio: "<<vectorPoints[randPos] << std::endl;
    std::cout<<"size antes: "<<vectorPoints.size();
    quickSort((vectorPoints),pseudoAngleSquare(vectorPoints[randPos]),0,vectorPoints.size()-1);
    std::cout<<"\nsize depois: " <<vectorPoints.size()<<std::endl;
    std::cout<<"ordenação :\n";
    std::cout<<std::endl;
    for(auto v : vectorPoints){
        std::cout << v;
    }
    std::cout<<std::endl;


    std::deque<std::pair<Vec2,int>> deck;
    for(auto v : vectorPoints){
        deck.push_back(std::pair<Vec2,int>(v,0));
    }

    std::pair<Vec2,int> temp;

    while( (deck.front().second < 2 || deck.back().second < 2)){
        if(crossCompare(deck.back().first,deck.front().first, deck[1].first)){
            temp = deck.front();
            deck.pop_front();
            deck.push_back(temp);
            deck.front().second+=1;
        }
        else{
            deck.pop_front();
            temp = deck.back();
            deck.pop_back();
            deck.push_front(temp);
        }
    }
    for(auto p : deck){
        convexHull.push_back(p.first);
    }
}
