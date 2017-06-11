//
//  Utilities.h
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 6/6/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#ifndef ElementsOfProgrammingInterviews_Utilities_h
#define ElementsOfProgrammingInterviews_Utilities_h

#include <vector>

void printVecInt(std::vector<int>& Arr){
    for (int i=0; i<Arr.size(); i++) {
        std::cout << Arr[i] << " ";
    }
    std::cout << std::endl;
}

void print2DVecInt(std::vector<std::vector<int>>& matrix){
    for (int i=0; i<matrix.size(); i++) {
        printVecInt(matrix[i]);
    }
}


#endif
