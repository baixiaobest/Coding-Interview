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




