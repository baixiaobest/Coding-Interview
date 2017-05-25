//
//  Arrays.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 5/14/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <stdio.h>


#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <limits.h>

using namespace std;

/////////////////////////////////////////////////////////////////////
// THREE WAY PARTITION:
// given an array A, and index i. Partition array A into three chunks,
// where elements smaller than A[i] comes first, elements equals A[i] comes next
// and elements larger than A[i] comes last
/////////////////////////////////////////////////////////////////////

void threeWayPartition(vector<int>& arr, int idx){
    int countLess = 0;
    int countEqual = 0;
    int ptrLess(0), ptrEqual(0), ptrLarge(0);
    int partition = arr[idx];

    for (int i=0; i<arr.size(); i++) {
        if (arr[i] < partition) countLess++;
        if (arr[i] == partition) countEqual++;
    }

    ptrEqual = countLess;
    ptrLarge = countLess + countEqual;

    for (int i=0; i<arr.size(); i++) {
        if (arr[i] == partition && (i < countLess || i >= countLess + countEqual)) {
            swap(arr[i], arr[ptrEqual++]);
            i--;
        }else if(arr[i] > partition && i < countLess + countEqual){
            swap(arr[i], arr[ptrLarge++]);
            i--;
        }else if(arr[i] < partition && i >= countLess){
            swap(arr[i], arr[ptrLess++]);
            i--;
        }
    }
}

void threeWayPartition2(vector<int>& arr, int idx){
    int ptrLess(0), ptrLarge(arr.size()-1);
    int ptr=0;
    int partition = arr[idx];

    while (ptr <= ptrLarge) {
        if (arr[ptr] < partition) {
            swap(arr[ptr++], arr[ptrLess++]);
        }else if(arr[ptr] == partition){
            ptr++;
        }else{
            swap(arr[ptr], arr[ptrLarge--]);
        }
    }
}



void printVecInt(vector<int>& Arr){
    for (int i=0; i<Arr.size(); i++) {
        cout << Arr[i] << " ";
    }
    cout << endl;
}


//int main(){
//    vector<int> input = {1,3,3,2,1,2,3,1,1,3,2};
//    int i = 5;
//    printVecInt(input);
//    threeWayPartition2(input, i);
//    printVecInt(input);
//}



/////////////////////////////////////////////////////////////////////
// MAX DIFFERENCE
// find maximum sell price in stock market
/////////////////////////////////////////////////////////////////////

int maxSellPrice(vector<int>& arr){
    int minPrice = INT_MAX;
    int maxProfits = 0;

    for (int i=0; i<arr.size(); i++) {
        int profits = arr[i] - minPrice;
        maxProfits = max(profits, maxProfits);
        minPrice = min(minPrice, arr[i]);
    }

    return maxProfits;
}

//int main(){
//    vector<int> input = {0,5,3,10,-1};
//    vector<int> input2 = {1,-5,0,-6,-3,5};
//    vector<int> input3 = {3,-2};
//    assert(maxSellPrice(input) == 10);
//    assert(maxSellPrice(input2) == 11);
//    assert(maxSellPrice(input3) == 0);
//}


/////////////////////////////////////////////////////////////////////
// Generalization of Max Difference
/////////////////////////////////////////////////////////////////////


// (1) Given array A, find (A[j0]-A[i0]) + (A[j1]-A[i1]) to be maximum
// where i0 < j0 < i1 < j1

int maxTwoPairProfits(vector<int>& arr){
    int minPrice = INT_MAX;
    int maxPrice = INT_MIN;
    int maxProfits = 0;
    vector<int> leftSubarrayMaxProfit = vector<int>(arr.size(), 0);
    vector<int> rightSubarrayMaxProfit = vector<int>(arr.size(), 0);

    for (int i=0; i<arr.size(); i++) {
        int profits = arr[i] - minPrice;
        maxProfits = max(maxProfits, profits);
        minPrice = min(minPrice, arr[i]);
        leftSubarrayMaxProfit[i] = maxProfits;
    }

    maxProfits = 0;

    for (int i=arr.size()-1; i >= 0; i--) {
        int profits = maxPrice - arr[i];
        maxProfits = max(maxProfits, profits);
        maxPrice = max(maxPrice, arr[i]);
        rightSubarrayMaxProfit[i] = maxProfits;
    }

    maxProfits = 0;

    for (int i=0; i<arr.size(); i++) {
        maxProfits = max(maxProfits, leftSubarrayMaxProfit[i] + rightSubarrayMaxProfit[i]);
    }

    return maxProfits;
}

//int main(){
//    vector<int> input = {0,10,5,9,0,-10,3,0};
//    assert(maxTwoPairProfits(input)==23);
//}


/////////////////////////////////////////////////////////////////////
// find subset that sums up to 0 modulo of size of array n.
/////////////////////////////////////////////////////////////////////

pair<int, int> sumSubsetToZero(vector<int>& arr){
    vector<int> prefixSum = arr;
    vector<int> table = vector<int>(arr.size(), -1);

    for (int i=0; i<arr.size(); i++) {
        prefixSum[i] += i > 0 ? prefixSum[i-1] : 0;
        prefixSum[i] %= arr.size();
    }

    for (int i=0; i<prefixSum.size(); i++) {
        if (prefixSum[i] == 0) {
            return pair<int, int>(0, i);
        }else if (table[prefixSum[i]] != -1){
            return pair<int, int>(table[prefixSum[i]]+1, i);
        }
        table[prefixSum[i]] = i;
    }
    return pair<int, int>(-1,-1);
}


//int main(){
//    vector<int> input = {429,334,62,713,701,763,98,733,721,995};
//    pair<int, int> result = sumSubsetToZero(input);
//    cout << result.first << " " << result.second;
//}


/////////////////////////////////////////////////////////////////////
//find longest increasing subarray in an array
/////////////////////////////////////////////////////////////////////


pair<int, int> longestIncreasingSubarray(vector<int> arr){
    int globalStart(0), globalEnd(0);
    int start(0), end(0);
    int prevNum = INT_MIN;
    int maxLength = 0;

    for (; end<arr.size(); end++) {
        if (arr[end] <= prevNum) {
            start = end;
        }
        if (end-start > maxLength) {
            maxLength = end-start;
            globalStart = start;
            globalEnd = end;
        }

        prevNum = arr[end];
    }
    return pair<int, int>(globalStart, globalEnd);
}

//int main(){
//    vector<int> input1 = {0,1,2,3,-1,-2,-3,5,6,7,8,9,9};
//    pair<int, int> result = longestIncreasingSubarray(input1);
//    cout << result.first << " " << result.second << endl;
//}



/////////////////////////////////////////////////////////////////////
// Big integer multiplication.
// given two string representing numbers, find muliplication of both.
/////////////////////////////////////////////////////////////////////


class BigInt{
private:
    bool negative;
    string number;

    void shiftLeft(string& str, int num) const{
        for (int i=0; i<num; i++) {
            str += '0';
        }
    }
    string add(const string& str1, const string& str2) const{
        int size = (int)max(str1.size(), str2.size());
        int carry = 0;
        string result = "";

        for (int i=0; i<size || carry; i++) {
            int idx1 = str1.size()-1-i;
            int idx2 = str2.size()-1-i;
            int digit1 = idx1 < str1.size() && idx1 >=0 ? str1[idx1] - '0' : 0;
            int digit2 = idx2 < str2.size() && idx2 >=0 ? digit2 = str2[idx2] - '0' : 0;

            int addition = digit1 + digit2 + carry;
            result = to_string(addition%10) + result;
            carry = addition/10;
        }
        return result;
    }

public:
    BigInt(): negative(false), number(""){}
    BigInt(string str, bool sign): negative(sign), number(str){}

    string getNumber() const{
        return number;
    }

    bool getSign() const{
        return negative;
    }

    BigInt operator*(const BigInt& other) const{
    	string result = "";
        string otherNum = other.getNumber();

        // for each digit in this bigint
        for (int i=0; i<number.size(); i++) {
            string digitMulIntStr="";
            int carry = 0;
            int digit1 = number[number.size()-i-1] - '0';

            // for each digit in other bigint
            for (int j=0; j<otherNum.size() || carry; j++) {
                int digit2 = j < otherNum.size() ? otherNum[otherNum.size()-j-1] - '0' : 0;

                int mulResult = digit1*digit2 + carry;
                char resultDigit = mulResult%10 + '0';
                digitMulIntStr = resultDigit + digitMulIntStr;

                carry = mulResult/10;
            }
            shiftLeft(digitMulIntStr, i);
            result = add(result, digitMulIntStr);
        }

        return BigInt(result, other.getSign() ^ negative);
    }

    void printNumber(){
    	if(negative)
            cout << "-";
        cout << number << endl;
    }
};

//int main(){
//    BigInt inta("28", false);
//    BigInt intb("78", false);
//    BigInt intc = inta*intb;
//    intc.printNumber(); // 654118386752169913744907850576079184
//}



/////////////////////////////////////////////////////////////////////
// Permutation
// given an array A and permutation P, change A into permutation P
/////////////////////////////////////////////////////////////////////


void permuateArray(vector<int>& arr, vector<int> P){
    for (int i=0; i<P.size(); i++) {
        if (P[i] < 0) {
            continue;
        }
        int j = i;
        int permCycleHead = arr[i];
        while (P[j] != -1) {
            // if next element has been visited, get the cycle head value
            arr[j] = P[P[j]] == -1? permCycleHead : arr[P[j]];
            int next = P[j];
            P[j] = -1;
            j = next;
        }
    }
}

//int main(){
//    vector<int> array = {0,1,2};
//    vector<int> perm =  {2,0,1};
//    vector<int> permInv = {1,2,0};
////    vector<int> array = {0,1,2,3,4,5,6,7,8};
////    vector<int> perm =  {1,4,3,2,0,7,8,6,5};
//    permuateArray(array, perm);
//    printVecInt(array);
//    permuateArray(array, permInv);
//    printVecInt(array);
//}


/////////////////////////////////////////////////////////////////////
// Inverse Permutation
// given a permuation P, find the inverse of this permutation PInv
// such that for an array A, PInv(P(A)) == A
/////////////////////////////////////////////////////////////////////



vector<int> inversePermutation(vector<int> P){
    vector<int> invP(P.size());

    for (int i=0; i<P.size(); i++) {
        if (P[i] < 0) {
            continue;
        }
        int j=P[i];
        int prev = i;
        while (P[j] >= 0) {
            invP[j] = prev;
            prev = j;
            int next = P[j];
            P[j] = -1;
            j = next;
        }
    }
    return invP;
}

//int main(){
//    vector<int> array = {0,1,2,3,4,5,6,7,8};
//    vector<int> perm =  {1,4,3,2,5,7,8,6,0};
//    vector<int> invPerm = inversePermutation(perm);
//    permuateArray(array, perm);
//    printVecInt(array);
//    permuateArray(array, invPerm);
//    printVecInt(array);
//}

/////////////////////////////////////////////////////////////////////
//Next Permutation
/////////////////////////////////////////////////////////////////////

//1 2 3 4
//1 2 4 3
//1 3 2 4
//1 3 4 2
//1 4 3 2
//2 1 3 4

bool nextPermutation(vector<int>& perm){
    if (perm.size() < 2) {
        return false;
    }
    int left = perm.size()-2;
    int right = perm.size()-1;
    int swapCandidateIdx = 0;

    // from right to left, find descending point
    while (left >= 0) {
        if (perm[left] < perm[right]) {
            break;
        }
        left--;
        right--;
    }

    // descending point cannot be found
    if (left < 0) return false;

    // find the minimum value element that is larger than descending point element
    for (int i=right; i<perm.size() && perm[i] > perm[left]; i++) {
        swapCandidateIdx = i;
    }

    swap(perm[left], perm[swapCandidateIdx]);
    reverse(perm.begin()+right, perm.end());
    return true;
}

bool previousPermutation(vector<int>& perm){
    if (perm.size() < 2) {
        return false;
    }
    int left = perm.size()-2;
    int right = perm.size()-1;
    int swapCandidateIdx = 0;

    // from right to left, find ascending point
    while (left >= 0) {
        if (perm[left] > perm[right]) {
            break;
        }
        left--;
        right--;
    }

    // descending point cannot be found
    if (left < 0) return false;

    // find the maximum value element that is smaller than descending point element
    for (int i=right; i<perm.size() && perm[i] < perm[left]; i++) {
        swapCandidateIdx = i;
    }

    swap(perm[left], perm[swapCandidateIdx]);
    reverse(perm.begin()+right, perm.end());
    return true;
}

//int main(){
//    vector<int> perm = {0,1,2};
//    do{
//        printVecInt(perm);
//    }while(nextPermutation(perm));
//
//    cout << "-----------" << endl;
//
//    do{
//        printVecInt(perm);
//    }while(previousPermutation(perm));
//}


/////////////////////////////////////////////////////////////////////
// Rotate array
/////////////////////////////////////////////////////////////////////

int gcd(int a, int b){
    while (b != 0) {
        int mod = a%b;
        a = b;
        b = mod;
    }
    return a;
}


void rotateArray(vector<int>& arr, int shift){
    int i=0;
    int visited = 0;
    int start = 0;
    int prevVal=arr[i];
    bool startVisited = false;
    shift = shift % arr.size();

    while (visited <= arr.size()) {
        swap(arr[i], prevVal);
        if(i==start && startVisited){
            i++;
            prevVal = arr[i];
            start = i;
            startVisited =false;
        }else{
            if (i == start) startVisited = true;
        	i = (i + shift) % arr.size();
        	visited++;
        }
    }
}

void rotateArray2(vector<int>& arr, int shift){
    int prevVal;
    shift = shift % arr.size();
    int numPermCycles = gcd(arr.size(), shift);
    int hops = arr.size() / numPermCycles;

    for (int i=0; i<numPermCycles; i++) {
        prevVal = arr[i];
        for (int j=0; j<=hops; j++) {
            swap(arr[(i+j*shift)%arr.size()], prevVal);
        }
    }
}

void rotateArray3(vector<int>& arr, int shift){
    shift = shift%arr.size();
    reverse(arr.begin(), arr.end());
    reverse(arr.begin(), arr.begin()+shift);
    reverse(arr.begin()+shift, arr.end());
}


//int main(){
//    vector<int> input1 = {0,1,2,3,4,5,6,7,8,9};
//    for (int i=0; i<=input1.size(); i++){
//        input1 = {0,1,2,3,4,5,6,7,8,9};
//    	rotateArray3(input1, i);
//    	printVecInt(input1);
//    }
//}


/////////////////////////////////////////////////////////////////////
// Sudoku checker
// check if a given sudoku is valid
/////////////////////////////////////////////////////////////////////


// assume given sudoku is in valid size
// 0 represents unfilled entry
bool validSudoku(vector<vector<int>>& sudoku){
    unordered_set<int> hash;

    // check row by row
    // see if there are duplicates in a row
    for (int row=0; row<sudoku.size(); row++) {
        hash.clear();
        for (int col=0; col<sudoku[row].size(); col++) {
            // check if sudoku contains valid numbers
            if (sudoku[row][col] < 0 || sudoku[row][col] > 9) {
                return false;
            }
            // ignore empty entry
            if (sudoku[row][col] == 0) continue;

            // check if the number appears more than once
            auto it = hash.find(sudoku[row][col]);
            if (it != hash.end()) {
                return false;
            }
            hash.insert(sudoku[row][col]);
        }
    }

    // check column by column
    // see if there are duplicates in a column
    for (int col=0; col<sudoku[0].size(); col++) {
        hash.clear();
        for (int row=0; row<sudoku.size(); row++) {
            // ignore empty entry
            if (sudoku[row][col] == 0) continue;

            auto it = hash.find(sudoku[row][col]);
            if (it != hash.end()) {
                return false;
            }
            hash.insert(sudoku[row][col]);
        }
    }

    // check block by block
    // see if there are duplicates in a block of 3x3 subsquare
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            hash.clear();
            for (int row = 3*i; row<3*(i+1); row++) {
                for (int col = 3*j; col<3*(j+1); col++) {
                    // ignore empty entry
                    if (sudoku[row][col] == 0) continue;

                    auto it = hash.find(sudoku[row][col]);
                    if (it != hash.end()) {
                        return false;
                    }
                    hash.insert(sudoku[row][col]);
                }
            }
        }
    }

    return true;
}

//int main(){
//    vector<vector<int>> sudoku =
//    {
//        {1,0,7,0,3,0,0,0,0},
//        {0,0,0,0,0,0,0,1,0},
//        {0,0,0,0,0,0,0,2,0},
//        {0,0,0,0,0,0,0,3,0},
//        {0,0,0,0,0,0,0,4,0},
//        {0,0,0,0,0,0,0,5,0},
//        {0,0,0,0,0,0,0,6,0},
//        {0,0,0,0,0,0,0,7,0},
//        {0,0,0,0,0,0,0,8,0}
//    };
//
//    cout << validSudoku(sudoku);
//}


/////////////////////////////////////////////////////////////////////
// spiral print
/////////////////////////////////////////////////////////////////////


void spiralPrint(vector<vector<int>> matrix){
    int n = matrix.size();
    int start = 0;
    int end = n-1;
    while (start <= end) {
        for (int i=start; i<=end; i++) {
            cout << matrix[start][i] << " ";
        }
        for (int i=start+1; i<end; i++) {
            cout << matrix[i][end] << " ";
        }
        for (int i=end; i>start; i--) {
            cout << matrix[end][i] << " ";
        }
        for (int i=end; i>start; i--) {
            cout << matrix[i][start] << " ";
        }
        start++;
        end--;
    }
    cout << endl;
}

//int main(){
//    vector<vector<int>> input1 = {{1}};
//    vector<vector<int>> input2 = {
//        							{1,2,3},
//        							{8,9,4},
//        							{7,6,5}
//                                	};
//    vector<vector<int>> input3 = {
//        {1, 2, 3, 4},
//        {12,13,14,5},
//        {11,16,15,6},
//        {10,9, 8, 7}
//    };
//    spiralPrint(input1);
//    spiralPrint(input2);
//    spiralPrint(input3);
//}


/////////////////////////////////////////////////////////////////////
// Flood fill
// given a 2D array of bool values, flood fill from a given point
/////////////////////////////////////////////////////////////////////


void floodFill(vector<vector<bool>>& image, int x, int y){
    int height = (int)image.size();
    int width = (int)image[0].size();
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    bool color = image[y][x];
    queue<pair<int, int>> myQueue;
    myQueue.push(pair<int, int>(x,y));

    while (!myQueue.empty()) {
        int currX = myQueue.front().first;
        int currY = myQueue.front().second;
        myQueue.pop();

        if (image[currY][currX] != color) {
            continue;
        }

        image[currY][currX] = !color; // flip color
        if (currX - 1 >= 0) {
            myQueue.push(pair<int, int>(currX-1, currY));
        }
        if(currX + 1 < width){
            myQueue.push(pair<int, int>(currX+1, currY));
        }
        if(currY - 1 >= 0){
            myQueue.push(pair<int, int>(currX, currY-1));
        }
        if (currY + 1 < height) {
            myQueue.push(pair<int, int>(currX, currY+1));
        }
    }
}

void print2DVecBool(vector<vector<bool>>& image){
    for (int i=0; i<image.size(); i++) {
        for (int j=0; j<image[i].size(); j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

//int main(){
//    vector<vector<bool>> image =
//    {
//        {1,0,1,1,0},
//        {1,1,1,0,0},
//        {0,1,1,0,0},
//        {1,0,0,1,1}
//    };
//    floodFill(image, 4, 0);
//    print2DVecBool(image);
//}



/////////////////////////////////////////////////////////////////////
// Rotate a square matrix clockwise 90 degrees
/////////////////////////////////////////////////////////////////////

void rotateMatrix(vector<vector<int>>& matrix){
    int start = 0;
    int end = matrix.size()-1;
    int size = matrix.size();

    while (start < end) {
        for (int i=start; i<end; i++) {
            swap(matrix[size-i-1][start], matrix[end][size-i-1]); // swap left side with bottom side
            swap(matrix[end][size-i-1], matrix[i][end]);          // swap bottom side with right side
            swap(matrix[i][end], matrix[start][i]);               // swap right side with top side
        }
        start++;
        end--;
    }
}

void print2DVecInt(vector<vector<int>>& matrix){
    for (int i=0; i<matrix.size(); i++) {
        printVecInt(matrix[i]);
    }
}

//int main(){
//    vector<vector<int>> matrix = {
//        {1,  2, 3, 4},
//        {5,  6, 7, 8},
//        {9, 10,11,12},
//        {13,14,15,16},
//    };
//
//    rotateMatrix(matrix);
//    print2DVecInt(matrix);
//}









