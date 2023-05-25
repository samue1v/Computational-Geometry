#include <iostream>
#include <random>
#include <algorithm>
#include "vec2.hpp"
#include "objUtils.h"
#include <vector>


int qsPartition(std::vector<Vec2> & vec, int ref, int first, int last)
{
    Vec2 pivot = vec[last];
    int i = (first - 1);
    Vec2 temp;
    
    for (int j = first; j <= last - 1; j++)
    {
        int p1 = pseudoAngleSquare(vec[j]);
        int p2 = pseudoAngleSquare(pivot);
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
 
void quickSort(std::vector<Vec2> & vec,int ref,int first, int last)
{
    if (first < last)
    {
        int partitionPivot = qsPartition(vec,ref,first, last);
        quickSort(vec,ref,first, partitionPivot - 1);
        quickSort(vec,ref, partitionPivot + 1, last);
    }
}

bool crossCompare(int previous, int current, int next, const std::vector<Vec2> & vectorPoints,const std::vector<int> & v){
    double s = cross(vectorPoints[current] - vectorPoints[previous], vectorPoints[next] - vectorPoints[current]);
    if(s>=0){
        return true;
    }
    return false;
}

void graham(const std::vector<Vec2> & pointCloud, std::vector<Vec2> & convexHull ){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    /* adição de pontos aleatórios
    for(int i;i<5;i++){
        pointCloud.push_back(Vec2(dist(mt)*2 -1,dist(mt)*2-1));    
    }*/




    std::vector<Vec2> vectorPoints = pointCloud;
    
    int size = vectorPoints.size();


    int randPos = pointCloud.size() * dist(mt);
    //std::cout<< "Ponto de inicio: "<<vectorPoints[randPos] << std::endl;
    
    quickSort((vectorPoints),pseudoAngleSquare(vectorPoints[randPos]),0,vectorPoints.size()-1);

    std::cout<<"ordenação :\n";
    std::cout<<std::endl;
    for(auto v : vectorPoints){
        std::cout << v;
    }
    std::cout<<std::endl;
    
    
    std::vector<int> v(size,-2);
    int previous = 0;
    int current = 1;
    int next = 2;
    //v[1] = 0;
    //v[0] = v.size()-1; //????????

   
   
    while(!crossCompare(previous,current,next,vectorPoints,v)){
        v[current] = -1;
        current = next;
        next+=1;
    }

    v[current] = 0;
    while(!(v[0] != -2)){
        if(crossCompare(previous,current,next,vectorPoints,v)){
            v[next] = current;
            v[current] = previous;
            previous = current;
            current = next;
            next = (next + 1)%size;
        }
        else{
            int tempCurrent = current;
            previous = v[previous];
            current = v[current];
            v[tempCurrent] = -1;
        }
    }

    while(true){
        if(v[next] > -1){
            if(crossCompare(previous,current,next,vectorPoints,v)){
                v[current] = previous;
                break;
            }
            else{
                v[current] = -1;
                current = next;
            }
        }
        
        next+=1;
    }

    for(int i = 0;i<size;i++){
        if(v[i] > -1){
            convexHull.push_back(vectorPoints[i]);
        }
    }
}

int main(){
    //std::vector<Vec2> cloud = {Vec2(1,0),Vec2(-1,0),Vec2(0,1),Vec2(-0.1,0.1),Vec2(0.2,-0.1),Vec2(0,-1),Vec2(0.1,0.1)};
    std::vector<Vec2> currentHull;
    std::string filename = "gato2d_input.obj";
    ObjUtils obj; 
    obj.readFromFile2D(filename);

    obj.writeToFile2D("gato2d_output.obj");

    /* apaga essa linha pra descomentar tudo abaixo
    std::vector<Object2D> catModel = catObj.obj2D;
    std::vector<Object2D> catOutput;
    std::vector<Vec2> outputPoints;
    for (auto cloud : catModel) {
        graham(cloud.points2D,currentHull); 
        cloud.points2D = currentHull;
        catOutput.push_back(cloud);
    }
    ObjUtils catOutputObj = catObj;
    catOutputObj.obj2D = catOutput;
    catOutputObj.writeToFile2D("./gato2d_output.obj");
    /*
    std::cout<<"hull :\n";

    for(auto v : ch){
        std::cout<<v;
    }
    */
    return 0;
}