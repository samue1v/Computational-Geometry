#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

void merge(std::vector<int> & v,const std::vector<int> & v1,const std::vector<int> & v2){
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] < v2[j]) {
            v[k] = v1[i];
            i++;
        }
        else{
            v[k] = v2[j];
            j++;
        }
        k++;
    }
    while (i < v1.size()) {
        v[k] = v1[i];
        i++;
        k++;
    }
    while (j < v2.size()) {
        v[k] = v2[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> & v){
    int n = v.size();
    if (n > 1) {
        std::vector<int> v1;
        std::vector<int> v2;
        for (int i = 0; i < (int)n/2; i++) {
            v1.push_back(v[i]);
        }
        for (int i =(int)n/2; i < n; i++) {
            v2.push_back(v[i]);
        }
        mergeSort(v1);
        mergeSort(v2);
        merge(v,v1,v2);

    }
}

#endif
