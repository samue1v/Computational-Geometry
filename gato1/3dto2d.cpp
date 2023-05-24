#include <string>
#include <iostream>
#include <fstream>
#include <vector>


/*
//Write edges acording to point order.
void writeOBJ(std::string filePath, const std::vector<Vec2> & pointVec){
  std::ofstream file;
  file.open(filePath);
  file << "o Pontos\n";

  for(auto i:pointVec){
    file << "v " << i.x() << " " << i.y() <<" 0.0\n";
  }

  for(int j;j<pointVec.size()-1;j++){
    file <<"l " << j+1 << " " << j+2 <<"\n";
  }
  file <<"l " << pointVec.size() << " " << 1 <<"\n";
  file.close();
}

//Only parse points
void parseOBJ(std::string filePath,  std::vector<Vec2> & destVec){
  std::ifstream file;
  file.open(filePath);
  std::string line;
  std::string delimiter = " ";
  Point2 point;
  int delimiterChar1,delimiterChar2,delimiterChar3;
  
  while(file){
    getline(file,line);
    if(line[0] == 'v'){
      delimiterChar1 = line.find(delimiter);
      delimiterChar2 = line.find(delimiter,delimiterChar1+1);
      delimiterChar3 = line.find(delimiter,delimiterChar2+1);
      point[0] = stod(line.substr(delimiterChar1+1,delimiterChar2));
      point[1] = stod(line.substr(delimiterChar2+1,delimiterChar3));
      destVec.push_back(point);
    }
  }
  file.close();
}
*/
int findOcur(std::string str, std::string c,int n){
    int initDelimiter = 0;
    for(int i = 0;i<n;i++){
        initDelimiter = str.find(c,initDelimiter) + 1;
    }
    return initDelimiter;
}

bool twoDthreeD(std::string twoD,std::string threeD){
    std::ifstream FILEREAD;
    std::ofstream FILEWRITE;
    FILEREAD.open(threeD);
    FILEWRITE.open(twoD);
    std::string line,temp;
    while(FILEREAD){
        getline(FILEREAD,line);
        temp = line;
        if((line[0] == 'v' && line[1] == ' ')){
            int pos = findOcur(line," ",2);
            temp = line.substr(pos,line.size()-pos);
            FILEWRITE << "v "<< temp << "\n";
        }
        else if((line[0] == 'v' && line[1] == 'n')){
            int pos = findOcur(line," ",2);
            temp = line.substr(pos,line.size()-pos);
            FILEWRITE << "vn "<< temp << "\n";
        }
        else{
            FILEWRITE << temp << "\n";
        }
    }
    FILEREAD.close();
    FILEWRITE.close();
    return true;
}

int main(){
    twoDthreeD("gato2d.obj","low_poly_cat.obj");
}