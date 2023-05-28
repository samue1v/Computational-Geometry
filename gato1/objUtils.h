#ifndef OBJ_UTILS_H
#define OBJ_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include "vec2.hpp"
#include "vec3.hpp"

struct Object2D{
    public:
    Object2D(){}
    Object2D(std::string name) : name(name){} 
    std::string name;
    std::vector<Vec2> points2D;
    std::vector<Vec2> normal2D;
    std::vector<Vec2> texture2D;
    std::vector<std::vector<Vec3>> faces2D;
    std::vector<std::pair<int,int>> line;
};


struct Object3D{
    public:
    Object3D(){}
    Object3D(std::string name) : name(name){} 
    std::string name;
    std::vector<Vec3> points3D;
    std::vector<Vec3> normal3D;
    std::vector<Vec3> texture3D;
    std::vector<std::vector<Vec3>> faces3D;
    std::vector<std::pair<int,int>> line;
};

class ObjUtils{
    public:

    ObjUtils(){}
    ~ObjUtils() = default;

    bool readFromFile2D(std::string fileName){
        std::ifstream INFILE;
        INFILE.open(fileName);
        std::string line,temp;
        Object2D currentObj;
        currentObj.name = "";
        while(getline(INFILE,line)){
            if(line[0] == 'o' && line[1] == ' '){
                if(currentObj.name != ""){
                    obj2D.push_back(currentObj);
                }
                currentObj = Object2D(line.substr(2));
            }
            else if(line[0] == 'v' && line[1] == ' ' ){
                int lastvoid = 1;
                int voidpos;
                Vec2 v2;
                for(int i = 0;i < 2;i++){
                    voidpos = line.find(" ",lastvoid+1);
                    v2[i] = stod(line.substr(lastvoid+1,voidpos-lastvoid+1));
                    lastvoid = voidpos;
                }
                currentObj.points2D.push_back(v2);
            }
            else if(line[0] == 'v' && line[1] == 'n' ){
                int lastvoid = 2;
                int voidpos;
                Vec2 v2;
                for(int i = 0;i < 2;i++){
                    voidpos = line.find(" ",lastvoid+1);
                    v2[i] = stod(line.substr(lastvoid+1,voidpos-lastvoid+1));
                    lastvoid = voidpos;
                }
                currentObj.normal2D.push_back(v2);
            }
            else if(line[0] == 'v' && line[1] == 't' ){
                int lastvoid = 2;
                int voidpos;
                Vec2 v2;
                for(int i = 0;i < 2;i++){
                    voidpos = line.find(" ",lastvoid+1);
                    v2[i] = stod(line.substr(lastvoid+1,voidpos-lastvoid+1));
                    lastvoid = voidpos;
                }
                currentObj.texture2D.push_back(v2);
            }

            else if(line[0] == 'l' && line[1] == ' ' ){
                int lastvoid = 1;
                int voidpos;
                Vec2 v2;
                for(int i = 0;i < 2;i++){
                    voidpos = line.find(" ",lastvoid+1);
                    v2[i] = stoi(line.substr(lastvoid+1,voidpos-lastvoid+1));
                    lastvoid = voidpos;
                }
                currentObj.line.push_back(std::pair<int,int>(v2[0],v2[1]));
            }
            else if(line[0] == 'f' && line[1] == ' ' ){
                
            }
        }
        obj2D.push_back(currentObj);
        INFILE.close();
        return true;
    }

    bool writeToFile2D(std::string fileName){
        std::ofstream OUTFILE;
        
        OUTFILE.open(fileName);
        
        std::string line,temp;
        Object2D currentObj;

        
        
        for(auto obj : obj2D){
            OUTFILE << "o " << obj.name << std::endl;
            for(auto v : obj.points2D){
                OUTFILE<< "v " << v[0] << " " << v[1]<<std::endl;
            }
            for(auto vn : obj.normal2D){
                OUTFILE<< "vn " << vn[0] << " " << vn[1]<<std::endl;
            }
            for(auto vt : obj.texture2D){
                OUTFILE<< "vt " << vt[0] << " " << vt[1]<<std::endl;
            }
            //OUTFILE << "s 0" << std::endl;
            //aqui deveria vir as faces
            for(auto l : obj.line){
                OUTFILE<< "l " << l.first << " " << l.second<<std::endl;
            }
        }
        std::cout<<"qwert\n";
        OUTFILE.close();
        
        return true;
    }

    public:
    std::vector<Object2D> obj2D;
    std::vector<Object3D> obj3D;


};


#endif

