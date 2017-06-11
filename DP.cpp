//
//  DP.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 5/20/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//
// total 2 problems

#include <iostream>
#include <vector>


using namespace std;

/////////////////////////////////////////////////////////////////////
// Cross in a matrix
// Given a matrix that contains only 1s and 0s, how to find the largest cross
// with the same arm lengths and the two arms join at the central point
// of each other
/////////////////////////////////////////////////////////////////////

// arm length   central point coordinate
pair<int, pair<int, int>> largestCross(vector<vector<int>>& matrix){
    if (matrix.size() < 1) {
        return pair<int, pair<int, int>>(-1, pair<int, int>(-1,-1));
    }
    
    int maxArmLength = 0;
    pair<int, int> cross(-1,-1);
    int currSum;
    
    // left to right continuous sum
    vector<vector<int>> LR(matrix.size(), vector<int>(matrix[0].size()));
    // right to left continuous sum
    vector<vector<int>> RL(matrix.size(), vector<int>(matrix[0].size()));
    // top to bottom continuous sum
    vector<vector<int>> TB(matrix.size(), vector<int>(matrix[0].size()));
    // bottom to top continuous sum
    vector<vector<int>> BT(matrix.size(), vector<int>(matrix[0].size()));

    for (int i=0; i<matrix.size(); i++) {
        currSum = 0;
        for (int j=0; j<matrix[i].size(); j++) {
            currSum = matrix[i][j] == 0 ? 0 : currSum + matrix[i][j];
            LR[i][j] = currSum;
        }
    }
    
    for (int i=0; i<matrix.size(); i++) {
        currSum = 0;
        for (int j=matrix[i].size()-1; j>=0; j--) {
            currSum = matrix[i][j] == 0 ? 0 : currSum + matrix[i][j];
            RL[i][j] = currSum;
        }
    }
    
    for (int i=0; i<matrix[0].size(); i++) {
        currSum = 0;
        for (int j=0; j<matrix.size(); j++) {
            currSum = matrix[j][i] == 0 ? 0 : currSum + matrix[j][i];
            TB[j][i] = currSum;
        }
    }
    
    for (int i=0; i<matrix[0].size(); i++) {
        currSum = 0;
        for (int j=matrix.size()-1; j>=0; j--) {
            currSum = matrix[j][i] == 0 ? 0 : currSum + matrix[j][i];
            BT[j][i] = currSum;
        }
    }
    
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            
            int armLength = min(min(min(LR[i][j], RL[i][j]), TB[i][j]), BT[i][j]);
            if (armLength > maxArmLength) {
                maxArmLength = LR[i][j];
            	cross = pair<int, int>(i,j);
            }
        }
    }
    
    return pair<int, pair<int, int>> (maxArmLength, cross);
}

//int main(){
//    vector<vector<int>> matrix =
//    {
//        {1,0,1,0,1},
//        {1,0,1,1,1},
//        {1,1,1,1,1},
//        {1,1,1,0,0},
//        {0,1,1,1,0},
//        {1,1,1,1,1},
//        {0,0,0,0,0}
//    };
//    
//    pair<int, pair<int, int>> result = largestCross(matrix);
//    cout << result.first << " " << result.second.first << " " << result.second.second << endl;
//}



/////////////////////////////////////////////////////////////////////
// Square in a matrix
// Given a matrix where every element is either 0 or 1,
// find the largest subsquare bounded by 1s.
/////////////////////////////////////////////////////////////////////

pair<int, pair<int, int>> squareInMatrix(vector<vector<int>>& matrix){
    
    if (matrix.size() == 0) {
        return pair<int, pair<int, int>>(-1,pair<int, int>(-1,-1));
    }
    
    int currSum = 0;
    int maxSquareLength = 0;
    pair<int, int> subsquare;
    
    // right to left continuous sum matrix
    vector<vector<int>> RL = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size()));
    // bottom to top continuous sum matrix
    vector<vector<int>> BT = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size()));
    
    // construct Right to left sum
    for (int i=0; i<matrix.size(); i++) {
        currSum = 0;
        for (int j=matrix[i].size()-1; j>=0; j--) {
            currSum = matrix[i][j] == 0 ? 0 : currSum + matrix[i][j];
            RL[i][j] = currSum;
        }
    }
    
    // construct bottom to top sum
    for (int i=0; i<matrix[0].size(); i++) {
        currSum = 0;
        for (int j=matrix.size()-1; j>=0; j--) {
            currSum = matrix[j][i] == 0 ? 0 : currSum + matrix[j][i];
            BT[j][i] = currSum;
        }
    }
    
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            
            if (matrix[i][j] == 0)
                continue;

            int squareLength = min(RL[i][j], BT[i][j]);
            
            while (squareLength > maxSquareLength) {
                if (RL[i+squareLength-1][j] >= squareLength
                 && BT[i][j+squareLength-1] >= squareLength) {
                    maxSquareLength = squareLength;
                    subsquare = pair<int, int>(i,j);
                }
                squareLength--;
            }
        }
    }
    return pair<int, pair<int, int>> (maxSquareLength, subsquare);
}


//int main(){
//    vector<vector<int>> matrix =
//    {
//        {0,0,0,0,0,0,0},
//        {0,1,0,1,1,1,0},
//        {0,1,1,1,1,1,0},
//        {0,1,0,1,1,0,0},
//        {0,1,0,0,1,0,0},
//        {0,1,1,1,1,0,0},
//        {0,0,0,0,0,0,0}
//    };
//    
//    pair<int, pair<int, int>> result = squareInMatrix(matrix);
//    cout << result.first << " " << result.second.first << " " << result.second.second << endl;
//}



/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////







