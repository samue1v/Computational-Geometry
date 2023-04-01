#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void writeOBJ(std::string filePath, const wykobi::polygon<double,2> & pointVec){
  std::ofstream file;
  file.open(filePath);
  file << "o Coroa\n";

  for(auto i:pointVec){
    file << "v " << i.x << " " << i.y <<" 0.0\n";
  }

  for(int j;j<pointVec.size()-1;j++){
    file <<"l " << j+1 << " " << j+2 <<"\n";
  }
  file <<"l " << pointVec.size() << " " << 1 <<"\n";
  file.close();
}

void parseOBJ(std::string filePath,  std::vector<wykobi::point2d<double>> & destVec){
  std::ifstream file;
  file.open(filePath);
  std::string line;
  std::string delimiter = " ";
  wykobi::point2d<double> point;
  int delimiterChar1,delimiterChar2,delimiterChar3;
  
  while(file){
    getline(file,line);
    if(line[0] == 'v'){
      delimiterChar1 = line.find(delimiter);
      delimiterChar2 = line.find(delimiter,delimiterChar1+1);
      delimiterChar3 = line.find(delimiter,delimiterChar2+1);
      point.x = stod(line.substr(delimiterChar1+1,delimiterChar2));
      point.y = stod(line.substr(delimiterChar2+1,delimiterChar3));
      destVec.push_back(point);
    }
  }
  file.close();
}

void parseOBJ(std::string filePath,  wykobi::polygon<double,2> & destPolygon){
  std::ifstream file;
  file.open(filePath);
  std::string line;
  std::string delimiter = " ";
  wykobi::point2d<double> point;
  int delimiterChar1,delimiterChar2,delimiterChar3;
  
  while(file){
    getline(file,line);
    if(line[0] == 'v'){
      delimiterChar1 = line.find(delimiter);
      delimiterChar2 = line.find(delimiter,delimiterChar1+1);
      delimiterChar3 = line.find(delimiter,delimiterChar2+1);
      point.x = stod(line.substr(delimiterChar1+1,delimiterChar2));
      point.y = stod(line.substr(delimiterChar2+1,delimiterChar3));
      destPolygon.push_back(point);
    }
  }
  file.close();
}


#endif