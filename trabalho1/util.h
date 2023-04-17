#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <time.h>
#include <string>


bool linearCheck(std::vector<int> vec){
    for(int i = 0;i<vec.size()-1;i++){
        if(vec[i+1]<vec[i]){
            return false;
        }
    }
    return true;
}

void displayTime(clock_t start,clock_t end, std::string algorithm){
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Tempo do " << algorithm << " " << std::fixed << time_taken << std::setprecision(5);
    std::cout << " sec " << std::endl;
}

#endif