#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>
 
void selectionSort(std::vector<int> & vec)
{
    int i, j, min_index;

    for (i = 0; i < vec.size()-1; i++)
    {
        min_index = i;
        for (j = i+1; j < vec.size(); j++)
        {
          if (vec[j] < vec[min_index])
              min_index = j;
        }
        if (i!=min_index){
            int temp = vec[i];
            vec[i] = vec[min_index];
            vec[min_index] = temp;
                
        }
    }
}

#endif

