#ifndef QUICK_SORT_H
#define QUICK_SORT_H


#include <vector>

int qsPartition(std::vector<int> & vec, int first, int last)
{

    int pivot = vec[last];
    int i = (first - 1);
    int temp;
 
    for (int j = first; j <= last - 1; j++)
    {
        if (vec[j] < pivot)
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
 
void quickSort(std::vector<int> & vec, int first, int last)
{
    if (first < last)
    {
        int partitionPivot = qsPartition(vec, first, last);
        quickSort(vec, first, partitionPivot - 1);
        quickSort(vec, partitionPivot + 1, last);
    }
}

#endif