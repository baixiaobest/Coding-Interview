//
//  Search.c
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 6/7/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <queue>
#include <unordered_set>
#include "Utilities.h"

using namespace std;


/////////////////////////////////////////////////////////////////////
// First Occurrance
// find the first occurrance of an element in a sorted array with duplicates
/////////////////////////////////////////////////////////////////////


int firstOccurrance(vector<int>& arr, int target){
    int left = 0;
    int right = arr.size()-1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target && (mid==0 || arr[mid-1] != target)) {
            return mid;
        }else if(target <= arr[mid]){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    return -1;
}

int firstOccurrance2(vector<int>& arr, int target){
    int left = 0;
    int right = arr.size()-1;
    int res = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            res = mid;
            right = mid-1;
        }else if(target < arr[mid]){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    return res;
}

//int main(){
//    vector<int> arr = {-14,-10,2,108,108,243,285,285,285,401};
//    assert(firstOccurrance(arr, 108) == 3);
//    assert(firstOccurrance(arr, 243) == 5);
//    assert(firstOccurrance(arr, 2) == 2);
//    assert(firstOccurrance(arr, 1) == -1);
//    
//    arr = {1};
//    assert(firstOccurrance(arr, 1)==0);
//    arr = {1,1,1,1,1,1,1,1};
//    assert(firstOccurrance(arr, 1) == 0);
//}


/////////////////////////////////////////////////////////////////////
// First element larger than k
/////////////////////////////////////////////////////////////////////

int firstLargerElement(vector<int>& arr, int k){
    int left = 0;
    int right = arr.size()-1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > k && (mid == 0 || arr[mid-1] <= k)) {
            return mid;
        }else if (arr[mid] > k){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    return -1;
}

int firstLargerElement2(vector<int>& arr, int k){
    int left = 0;
    int right = arr.size()-1;
    int res = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > k) {
            res = mid;
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    return res;
}

//int main(){
//    vector<int> arr = {-14,-10,2,108,108,243,285,285,285,401};
//    assert(firstLargerElement(arr, 500) == -1);
//    assert(firstLargerElement(arr, 401) == -1);
//    assert(firstLargerElement(arr, 286) == 9);
//    assert(firstLargerElement(arr, 285) == 9);
//    assert(firstLargerElement(arr, 100) == 3);
//    assert(firstLargerElement(arr, -100) == 0);
//
//    arr = {1};
//    assert(firstLargerElement(arr, 500) == -1);
//    assert(firstLargerElement(arr, 1) == -1);
//    assert(firstLargerElement(arr, 0) == 0);
//}



/////////////////////////////////////////////////////////////////////
// search in sorted array for occurance of A[i] = i
/////////////////////////////////////////////////////////////////////

int dataMatchIndex(vector<int>& arr){
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == mid) {
            return mid;
        }else if (arr[mid] < mid){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    return -1;
}

//int main(){
//    vector<int> arr = {-14,-10,2,108,108,243,285,285,285,401};
//    assert(dataMatchIndex(arr) == 2);
//    
//    arr = {1};
//    assert(dataMatchIndex(arr) == -1);
//}


/////////////////////////////////////////////////////////////////////
// search in absolute value sorted array
// give a sum k and absolute value sorted array
// fine a pair of elements that sum up to k
// return indices of found elements
/////////////////////////////////////////////////////////////////////

int nextPositive(vector<int>& arr, int idx){
    while (idx < arr.size() && arr[idx] < 0) {
        idx++;
    }
    return idx;
}

int prevPositive(vector<int>& arr, int idx){
    while (idx >= 0 && arr[idx] < 0) {
        idx--;
    }
    return idx;
}

int nextNegative(vector<int>& arr, int idx){
    while (idx < arr.size() && arr[idx] >= 0) {
        idx++;
    }
    return idx;
}

int prevNegative(vector<int>& arr, int idx){
    while (idx >= 0 && arr[idx] >= 0) {
        idx--;
    }
    return idx;
}


pair<int, int> twoSumInAbsSortedArray(vector<int>& arr, int target){
    int firstPos = nextPositive(arr, 0);
    int lastPos = prevPositive(arr, arr.size()-1);
    int firstNeg = nextNegative(arr, 0);
    int lastNeg = prevNegative(arr, arr.size()-1);
    
    int left = firstPos;
    int right = lastPos;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum < target) {
            left = nextPositive(arr, left+1);
        }else if(sum > target){
            right = prevPositive(arr, right-1);
        }else{
            return pair<int, int>(left, right);
        }
    }
    
    left = firstNeg;
    right = lastNeg;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum < target) {
            right = prevNegative(arr, right-1);
        }else if(sum > target){
            left = nextNegative(arr, left+1);
        }else{
            return pair<int, int>(left, right);
        }
    }
    
    int negPtr = lastNeg;
    int posPtr = lastPos;
    
    while (negPtr >= 0 && posPtr >= 0) {
        int sum = arr[negPtr] + arr[posPtr];
        if (sum < target) {
            negPtr = prevNegative(arr, negPtr-1);
        }else if (sum > target){
            posPtr = prevPositive(arr, posPtr-1);
        }else{
            return pair<int, int>(negPtr, posPtr);
        }
    }
    return pair<int, int>(-1, -1);
}


//int main(){
//    vector<int> arr = {-49, 75, 103, -147, 164, -197, -238, 314, 348, -422};
//    
//    pair<int, int> ret = twoSumInAbsSortedArray(arr, 167);
//    assert(ret.first == 3 && ret.second == 7);
//    
//    ret = twoSumInAbsSortedArray(arr, 178);
//    assert(ret.first == 1 && ret.second == 2);
//    
//    ret = twoSumInAbsSortedArray(arr, -344);
//    assert(ret.first == 3 && ret.second == 5);
//    
//    ret = twoSumInAbsSortedArray(arr, 178);
//    assert(ret.first == 1 && ret.second == 2);
//    
//    ret = twoSumInAbsSortedArray(arr, 1000);
//    assert(ret.first == -1 && ret.second == -1);
//    
//    ret = twoSumInAbsSortedArray(arr, -49);
//    assert(ret.first == -1 && ret.second == -1);
//}



/////////////////////////////////////////////////////////////////////
// Search the minimum element in the cyclically sorted array
// assume array does not contain duplicates
/////////////////////////////////////////////////////////////////////


int smallestInCyclicallySorted(vector<int>& arr){
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[right]){
            right = mid;
        }else{
            left = mid+1;
        }
    }
    return left;
}


//int main(){
//    vector<int> a = {1,2,3,4,5,6,7,8,9};
//    assert(smallestInCyclicallySorted(a) == 0);
//    
//    for (int i=0; i<a.size(); i++) {
//        rotate(a.begin(), a.begin()+1, a.end());
//        assert(smallestInCyclicallySorted(a) == a.size()-1-i);
//    }
//    
//    a = {1};
//    assert(smallestInCyclicallySorted(a) == 0);
//}



/////////////////////////////////////////////////////////////////////
// Search for element in unknown size sorted array
/////////////////////////////////////////////////////////////////////

class UnknownVector{
private:
    vector<int> arr;
public:
    UnknownVector(vector<int>& array){
        arr = array;
    }
    
    int operator[](int idx){
        if (idx >= arr.size() || idx < 0) {
            return INT_MIN;
        }
        return arr[idx];
    }
};

int findSize(UnknownVector& arr, int target){
    int size = 1;
    while (arr[size-1] != INT_MIN && arr[size-1] < target) {
        size *= 2;
    }
    return size;
}


int findElementOfUnknownArray(UnknownVector& arr, int target){
    int right = findSize(arr, target) - 1;
    int left = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }else if (arr[mid] == INT_MIN || arr[mid] > target){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    return -1;
}

//int main(){
//    vector<int> v = {1,2,3,4,7,9,10,15,20};
//    UnknownVector uv = UnknownVector(v);
//    
//    for (int i=0; i<v.size(); i++){
//    	assert(findElementOfUnknownArray(uv, v[i]) == i);
//    }
//}




/////////////////////////////////////////////////////////////////////
// Completion Search
/////////////////////////////////////////////////////////////////////

int salaryCutoff(vector<int>& salaries, int targetPay){
    int maxSalary = 0;
    for (int i=0; i<salaries.size(); i++) {
        maxSalary = max(maxSalary, salaries[i]);
    }
    
    int left = 0;
    int right = maxSalary;
    int res = 0;
    
    while (left <= right) {
        int mid = left + (right-left) / 2;
        int pay = 0;
        for (int i=0; i<salaries.size(); i++) {
            pay += min(mid, salaries[i]);
        }
        if(pay <= targetPay){
            res = mid;
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    return res;
}


//int main(){
//    vector<int> salaries = {90,30,100,40,20};
//    assert(salaryCutoff(salaries, 210) == 60);
//    assert(salaryCutoff(salaries, 211) == 60);
//    assert(salaryCutoff(salaries, 279) == 99);
//    assert(salaryCutoff(salaries, 269) == 89);
//    assert(salaryCutoff(salaries, 300) == 100);
//    assert(salaryCutoff(salaries, 4) == 0);
//    assert(salaryCutoff(salaries, 5) == 1);
//}



/////////////////////////////////////////////////////////////////////
// search in two sorted array
// given two sorted array A and B,
// find Kth smallest element in merged sorted array C into which A and B merge
/////////////////////////////////////////////////////////////////////

// the most intuitive solution is to merge first K elements, which will take O(k) time and O(1) space
// the most optimized solution takes O(logK) time and O(1) space


// O(k) time O(1) space solution
// assume k is smaller than A.size() * B.size()
int findKthSmallestFromMergedArray(vector<int>& A, vector<int>& B, int k){
    int i(0), j(0);
    int ret=0;
    
    while (k >= 0) {
        if (i != A.size() && j != B.size()) {
            if (A[i] < B[j]) {
                ret = A[i];
                i++;
            }else{
                ret = B[j];
                j++;
            }
        }else if (i != A.size()){
            ret = A[i];
            i++;
        }else{
            ret = B[j];
            j++;
        }
        k--;
    }
    
    return ret;
}

//int main(){
//    vector<int> A = {1, 4, 5, 10};
//    vector<int> B = {2, 6, 6, 7, 12, 14};
//    vector<int> answers;
//    
//    copy(A.begin(), A.end(), back_inserter(answers));
//    copy(B.begin(), B.end(), back_inserter(answers));
//    sort(answers.begin(), answers.end());
//    
//    for (int i=0; i<answers.size(); i++) {
//        assert(findKthSmallestFromMergedArray(A, B, i) == answers[i]);
//    }
//}




/////////////////////////////////////////////////////////////////////
// square root
// use binary search for square root
/////////////////////////////////////////////////////////////////////

double squareRoot(double a, double precision){
    double left = 1.0;
    double right = a;
    
    if (a < 1.0) {
        left = a;
        right = 1.0;
    }
    
    while (left <= right-precision) {
        double mid = left + (right-left) / 2;
        double midSquare = mid * mid;
        if (midSquare < a) {
            left = mid;
        }else{
            right = mid;
        }
    }
    return left;
}

//int main(){
//    double precision = 0.001;
//    for (int i=0; i<=100; i++) {
//        assert( abs(sqrt((double)i) - squareRoot((double)i, precision)) <= precision );
//    }
//    
//    for (int i=1; i<=100; i++) {
//        double a =1.0/i;
//        assert( abs(sqrt(a) - squareRoot(a, precision)) <= precision );
//    }
//}



/////////////////////////////////////////////////////////////////////
// 2D array search
// given a matrix with sorted rows and columns and a target x,
// find check wheter x is in the matrix
/////////////////////////////////////////////////////////////////////


//1 2 4 7  7  9
//1 2 5 8  10 10
//3 4 6 10 11 12
//5 6 7 11 11 12

bool findInSortedMatrix(vector<vector<int>>& M, int target){
    int row = 0;
    int col = M[0].size()-1;
    
    while (row < M.size() && col >= 0) {
        if (M[row][col] == target) {
            return true;
        }else if(target < M[row][col]){
            col--;
        }else{
            row++;
        }
    }
    return false;
}

//int main(){
//    vector<vector<int>> M =
//    {
//        {2,2,5,7,7,9},
//        {2,3,5,8,10,10},
//        {3,5,6,11,11,12},
//        {5,6,7,11,11,12}
//    };
//    
//    assert(findInSortedMatrix(M, 1) == false);
//    assert(findInSortedMatrix(M, 2) == true);
//    assert(findInSortedMatrix(M, 4) == false);
//    assert(findInSortedMatrix(M, 8) == true);
//    assert(findInSortedMatrix(M, 12) == true);
//    assert(findInSortedMatrix(M, 13) == false);
//}







/////////////////////////////////////////////////////////////////////////////////////////////////////
// Unsorted arrays searching problems:
/////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////
// search for kth largest element in unsorted array
/////////////////////////////////////////////////////////////////////

// O(n) time O(1) space
// each partition takes O(n) time
// on average, partitions are taken with array size n, n/2, n/4...1
// this sum up to 1+2+4+8+16+...+n = 2n-1 => O(n)
int partitionArray(vector<int>& arr, int start, int end){
    if (start >= end) {
        return start;
    }
    
    int pivot = arr[end];
    int pivotIdx = start;
    
    for (int i=start; i<end; i++) {
        if (arr[i] > pivot) {
            swap(arr[i], arr[pivotIdx]);
            pivotIdx++;
        }
    }
    swap(arr[pivotIdx], arr[end]);
    return pivotIdx;
}

int findKthLargest(vector<int>& arr, int k){
    int left = 0;
    int right = arr.size()-1;
    
    while (left <= right) {
        int pivotIdx = partitionArray(arr, left, right);
        if (pivotIdx == k) {
            return arr[pivotIdx];
        }else if(pivotIdx < k){
            left = pivotIdx+1;
        }else{
            right = pivotIdx-1;
        }
    }
    return arr[left];
}

//int main(){
//    vector<int> arr = {9,1,0,7,3,2,6,4,8,5,10};
//    vector<int> ans = arr;
//    sort(ans.begin(), ans.end(), greater<int>());
//    
//    for (int i=0; i<arr.size(); i++) {
//        assert(findKthLargest(arr, i) == ans[i]);
//    }
//}




/////////////////////////////////////////////////////////////////////
// Let A be an unsorted array of n intergers from 0 to n-1. But one element
// of A is modified such that there is one duplicate element t.
// This also implies that there is one missing element m in 0 to n-1.
// Use O(N) time and O(1) space to find the duplicate t and missing m.
/////////////////////////////////////////////////////////////////////


// return -1, -1 if no dup or missing found
// <dup, missing>
pair<int, int> findDupAndMissingElementsFromArray(vector<int>& arr){
    int missingXORDup = 0;
    
    for (int i=0; i<arr.size(); i++) {
        missingXORDup ^= i ^ arr[i];
    }
    
    int diffBit = missingXORDup & ~(missingXORDup - 1);
    int dupOrMissing = 0;
    
    for (int i=0; i<arr.size(); i++) {
        if (i & diffBit) {
            dupOrMissing ^= i;
        }
        
        if (arr[i] & diffBit) {
            dupOrMissing ^= arr[i];
        }
    }
    
    for (int i=0; i<arr.size(); i++) {
        // duplicate found, dupOrMissing is duplicate element
        if (arr[i] == dupOrMissing) {
            return {dupOrMissing, missingXORDup ^ dupOrMissing};
        }
    }
    
    // dupOrMissing is missing element
    return {missingXORDup ^ dupOrMissing, dupOrMissing};
}


//int main(){
//    vector<int> arr = {1,6,2,4,0,7,3,6,9,8};
//	
//    pair<int, int> ret = findDupAndMissingElementsFromArray(arr);
//    cout << "dup: " << ret.first << " missing: " << ret.second << endl;
//}




/////////////////////////////////////////////////////////////////////
// search in unsorted array with close entry
// suppose two consecutive array entries A[i] and A[i-1] has this property:
// abs(A[i] - A[i-1]) <= 1, then given k, design an efficient algorithm to search
// for indices where A[i] == k
/////////////////////////////////////////////////////////////////////

// return an array of indices
vector<int> searchCloseArray(vector<int>& arr, int k){
    int i=0;
    vector<int> ret;
    
    while (i < arr.size()) {
        if (arr[i] == k) {
            ret.push_back(i);
        }
        int increment = abs(arr[i]-k);
        i += increment == 0 ? 1 : increment;
    }
    return ret;
}

//int main(){
//    vector<int> arr = {-1, 0, 0, 1, 2, 2, 1, 2 , 3, 4};
//    vector<int> ret = searchCloseArray(arr, 2);
//    printVecInt(ret); // 4 5 7
//    
//    ret = searchCloseArray(arr, 0);
//    printVecInt(ret); // 1 2
//}




