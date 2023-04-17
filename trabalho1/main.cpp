#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"

int main()
{
    clock_t start, end;
    srand(time(0));
    std::vector<int> ssvec10;
    std::vector<int> ssvec100;
    std::vector<int> ssvec1000;

    std::vector<int> qsvec10;
    std::vector<int> qsvec100;
    std::vector<int> qsvec1000;
    
    std::vector<int> msvec10;
    std::vector<int> msvec100;
    std::vector<int> msvec1000;

    for(int i = 0; i< 10; i++){
        int r = rand() % 1000;
        ssvec10.push_back(r);
        qsvec10.push_back(r);
        msvec10.push_back(r);
    }
    for(int j = 0; j< 100; j++){
        int r = rand() % 1000;
        ssvec100.push_back(r);
        qsvec100.push_back(r);
        msvec100.push_back(r);
    }
    for(int k = 0; k< 1000; k++){
        int r = rand() % 1000;
        ssvec1000.push_back(r);
        qsvec1000.push_back(r);
        msvec1000.push_back(r);
    }

    std::cout<< std::boolalpha << "(SelectionSort)Antes da ordenação:\n"<< " Vec10: " << linearCheck(ssvec10) << std::endl<< " Vec100: " << linearCheck(ssvec100) << std::endl<< " Vec1000: " << linearCheck(ssvec1000) << std::endl;
    start = clock();
    selectionSort(ssvec10);
    end = clock();
    displayTime(start,end,"SelectionSort10");

    start = clock();
    selectionSort(ssvec100);
    end = clock();
    displayTime(start,end,"SelectionSort100");
    
    start = clock();
    selectionSort(ssvec1000);
    end = clock();
    displayTime(start,end,"SelectionSort1000");
    
    std::cout<< std::boolalpha << "(SelectionSort)Após a ordenação:\n"<< " Vec10: " << linearCheck(ssvec10) << std::endl<< " Vec100: " << linearCheck(ssvec100) << std::endl<< " Vec1000: " << linearCheck(ssvec1000) << std::endl << std::endl;
    

    std::cout<< std::boolalpha << "(QuickSort)Antes da ordenação:\n"<< " Vec10: " << linearCheck(qsvec10) << std::endl<< " Vec100: " << linearCheck(qsvec100) << std::endl<< " Vec1000: " << linearCheck(qsvec1000) << std::endl;
    start = clock();
    quickSort(qsvec10,0,qsvec10.size()-1);
    end = clock();
    displayTime(start,end,"QuickSort10");
    
    start = clock();
    quickSort(qsvec100,0,qsvec100.size()-1);
    end = clock();
    displayTime(start,end,"QuickSort100");

    start = clock();
    quickSort(qsvec1000,0,qsvec1000.size()-1);
    end = clock();
    displayTime(start,end,"QuickSort1000");
    std::cout<< std::boolalpha <<"(QuickSort)Após a ordenação:\n"<< " Vec10: " << linearCheck(qsvec10) << std::endl<< " Vec100: " << linearCheck(qsvec100) << std::endl<< " Vec1000: " << linearCheck(qsvec1000) << std::endl << std::endl;;

    std::cout<< std::boolalpha << "(MergeSort)Antes da ordenação:\n"<< " Vec10: " << linearCheck(msvec10) << std::endl<< " Vec100: " << linearCheck(msvec100) << std::endl<< " Vec1000: " << linearCheck(msvec1000) << std::endl;
    start = clock();
    mergeSort(msvec10);
    end = clock();
    displayTime(start,end,"MergeSort10");

    start = clock();
    mergeSort(msvec100);
    end = clock();
    displayTime(start,end,"MergeSort100");
    
    start = clock();
    mergeSort(msvec1000);
    end = clock();
    displayTime(start,end,"MergeSort1000");
    std::cout<< std::boolalpha <<"(MergeSort)Após a ordenação:\n"<< " Vec10: " << linearCheck(msvec10) << std::endl<< " Vec100: " << linearCheck(msvec100) << std::endl<< " Vec1000: " << linearCheck(msvec1000) << std::endl << std::endl;;

    std::cout<< "Analisando o tempo de execução dos algoritmos quando suas entradas já estão ordenadas.(Pior Caso)"<<std::endl;

    start = clock();
    selectionSort(ssvec10);
    end = clock();
    displayTime(start,end,"SortedSelectionSort10");

    start = clock();
    selectionSort(ssvec100);
    end = clock();
    displayTime(start,end,"SortedSelectionSort100");
    
    start = clock();
    selectionSort(ssvec1000);
    end = clock();
    displayTime(start,end,"SortedSelectionSort1000");

    std::cout << std::endl;

    start = clock();
    quickSort(qsvec10,0,qsvec10.size()-1);
    end = clock();
    displayTime(start,end,"SortedQuickSort10");
    
    start = clock();
    quickSort(qsvec100,0,qsvec100.size()-1);
    end = clock();
    displayTime(start,end,"SortedQuickSort100");

    start = clock();
    quickSort(qsvec1000,0,qsvec1000.size()-1);
    end = clock();
    displayTime(start,end,"SortedQuickSort1000");

    std::cout << std::endl;

    start = clock();
    mergeSort(msvec10);
    end = clock();
    displayTime(start,end,"SortedMergeSort10");

    start = clock();
    mergeSort(msvec100);
    end = clock();
    displayTime(start,end,"SortedMergeSort100");
    
    start = clock();
    mergeSort(msvec1000);
    end = clock();
    displayTime(start,end,"SortedMergeSort1000");

    std::cout << std::endl;

    


    return 0;
}