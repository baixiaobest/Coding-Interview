	//
//  Heap.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 6/6/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>
#include <cmath>
#include <unordered_set>
//#include "Utilities.h"

using namespace std;

/////////////////////////////////////////////////////////////////////
// Merge k sorted arrays
// merge k files with entries of timestamps
// timestamps in the files are sorted in order
/////////////////////////////////////////////////////////////////////

struct heapCompare{
    bool operator()(const pair<int, size_t>& a, const pair<int, size_t>& b) const
    {
        return a.first > b.first;
    }
};

vector<int> mergeKArrays(vector<vector<int>>& KArrays){
    vector<int> ret;
    vector<size_t> pointers = vector<size_t>(KArrays.size(), 1);
    priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, heapCompare> minHeap;
	
    for (int fileNum=0; fileNum<KArrays.size(); fileNum++) {
        minHeap.emplace(KArrays[fileNum][0], fileNum);
    }
    
    while (!minHeap.empty()) {
        int timeStamp = minHeap.top().first;
        size_t fileNum = minHeap.top().second;
        size_t entryNum = pointers[fileNum]++;
        
        minHeap.pop();
        ret.push_back(timeStamp);
        
        if ( entryNum < KArrays[fileNum].size()) {
            minHeap.emplace(KArrays[fileNum][entryNum], fileNum);
        }
    }
    return ret;
}

//int main(){
//    vector<vector<int>> arrays = {{1,4,5,35,67},{0,1,3,5},{9,10,13,15,23},{100}};
//    vector<int> merged = mergeKArrays(arrays);
//    printVecInt(merged);
//}



/////////////////////////////////////////////////////////////////////
// Sort K-increasing-decreasing array
// time complexity O(nlogk), space complexity k
/////////////////////////////////////////////////////////////////////

vector<int> mergeKArrays2(vector<int>& arr, vector<pair<size_t, size_t>> arrays){
    vector<int> ret;
    priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, heapCompare> minHeap;
    
    for (size_t i=0; i<arrays.size(); i++) {
        int element = arr[arrays[i].first++];
        minHeap.emplace(element, i);
    }
    
    while (!minHeap.empty()) {
        int ele = minHeap.top().first;
        size_t arrIdx = minHeap.top().second;
        size_t eleIdx = arrays[arrIdx].first++;
        
        minHeap.pop();
        ret.push_back(ele);
        
        if (eleIdx < arrays[arrIdx].second) {
            minHeap.emplace(arr[eleIdx], arrIdx);
        }
    }
    return ret;
}


void sortKIncreasingDecreasing(vector<int>& arr, vector<int>& ret){
    vector<pair<size_t, size_t>> arrays;
    
    size_t start = 0;
    bool increasing = true;
    for (size_t i=1; i<arr.size(); i++) {
        if ((increasing && arr[i-1] > arr[i])
        ||  (!increasing && arr[i-1] < arr[i]))
        {
            size_t end = i;
            arrays.emplace_back(start, end);
            if (!increasing)
                reverse(arr.begin()+start, arr.begin()+end);
            start = end;
            increasing = !increasing;
        }
    }
    arrays.emplace_back(start, arr.size());
    if (!increasing)
        reverse(arr.begin()+start, arr.end());
    
    ret = mergeKArrays2(arr, arrays);
}

//int main(){
//    vector<int> arr = {1,2,3,4,5,5,4,3,6,7,8,6,5,4,4};
//    vector<int> ret;
//    sortKIncreasingDecreasing(arr, ret);
//    printVecInt(ret);
//}


/////////////////////////////////////////////////////////////////////
// Implement stack and queue using priority queue
/////////////////////////////////////////////////////////////////////

struct heapStackQueueCompare{
    bool operator ()(const pair<unsigned int, int>& lhs, const pair<unsigned int, int>& rhs) const
    {
        return lhs.first < rhs.first;
    }
};

class heapStack{
private:
    priority_queue<pair<unsigned int, int>, vector<pair<unsigned int, int>>, heapStackQueueCompare> heap;
    unsigned int priority;
    
public:
    heapStack(): priority(0){}
    
    void push(int data){
        heap.emplace(priority++, data);
    }
    
    void pop(){
        heap.pop();
        priority--;
    }
    
    int top(){
        return heap.top().second;
    }
};

//int main(){
//    heapStack stack;
//    stack.push(1);
//    assert(stack.top() == 1);
//    stack.push(2);
//    assert(stack.top() == 2);
//    stack.pop();
//    assert(stack.top() == 1);
//}



/////////////////////////////////////////////////////////////////////
// find Kth smallest elements from a large array
/////////////////////////////////////////////////////////////////////

// assume k is smaller than size of array
priority_queue<int> findKSmallest(vector<int>& array, int k){
    priority_queue<int> maxHeap;
    
    for (int i=0; i<k && i<array.size(); i++) {
        maxHeap.push(array[i]);
    }
    
    for (int i=k; i<array.size(); i++) {
        if(array[i] < maxHeap.top()){
            maxHeap.pop();
            maxHeap.push(array[i]);
        }
    }
    return maxHeap;
}

//int main(){
//    vector<int> array = {3,2,3,4,6,7,4,9,7,5,6,5,10,11,15};
//    priority_queue<int> Q = findKSmallest(array, 5);
//    
//    vector<int> ret;
//    while (!Q.empty()) {
//        ret.push_back(Q.top());
//        Q.pop();
//    }
//    printVecInt(ret);
//}


/////////////////////////////////////////////////////////////////////
// print Kth largest elements as elements stream in
/////////////////////////////////////////////////////////////////////


// assume k is small, input array is big
void printKthLargest(vector<int>& arr, int k){
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int i=0; i<k; i++) {
        minHeap.emplace(arr[i]);
        cout << minHeap.top() << " ";
    }
    
    for (int i=k; i<arr.size(); i++) {
        if (arr[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.emplace(arr[i]);
        }
        cout << minHeap.top() << " ";
    }
}

//int main(){
//    vector<int> array = {3,2,3,4,6,7,4,9,7,5,6,5,10,11,15};
//    printKthLargest(array, 3);
//}


/////////////////////////////////////////////////////////////////////
// Approximate Sort
// sort the array that is almost sorted
// every element in it is at most k positions away from it's sorted position
/////////////////////////////////////////////////////////////////////


void approximateSort(vector<int>& arr, int k){
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int sortedIdx = 0;   // to the left of index is sorted
    int nextIdx = k+1;   // pointing to next element to be added
    
    for (int i=0; i<=k; i++) {
        minHeap.push(arr[i]);
    }
    
    while (!minHeap.empty()) {
        arr[sortedIdx++] = minHeap.top();
        minHeap.pop();
        if (nextIdx < arr.size()) {
            minHeap.push(arr[nextIdx++]);
        }
    }
}

//int main(){
//    vector<int> nearlySorted = {4,5,3,1,2,9,7,11,6,10,8,14,13,12,15};
//    int k = 3;
//    approximateSort(nearlySorted, k);
//    printVecInt(nearlySorted);
//}


/////////////////////////////////////////////////////////////////////
// Closest to median
// given a unsorted array, find the k elements closest to the median
/////////////////////////////////////////////////////////////////////

double getMedian(vector<int>& arr){
    int mid = arr.size()/2;
    nth_element(arr.begin(), arr.begin()+mid, arr.end());
    
    if (arr.size()%2 == 0) {
        nth_element(arr.begin(), arr.begin()+mid-1, arr.end());
        return (double(arr[mid])+double(arr[mid-1])) / 2;
    }else{
        return (double)arr[mid];
    }
}

class medianCompare{
private:
    double median;

public:
    medianCompare(double mid): median(mid){}
    
    bool operator()(int a, int b) const{
        double aDist = abs(median - a);
        double bDist = abs(median - b);
        return aDist < bDist;
    }
};


vector<int> KClosestToMedian(vector<int>& arr, int k){
    double median = getMedian(arr);
    medianCompare cmp(median);
    priority_queue<int, vector<int>, medianCompare> maxHeap (cmp);
    vector<int> ret;
    
    for (int i=0; i<k; i++) {
        maxHeap.push(arr[i]);
    }
    for (int i=k; i<arr.size(); i++) {
        if (cmp(arr[i], maxHeap.top())) {
            maxHeap.pop();
            maxHeap.push(arr[i]);
        }
    }
    
    while (!maxHeap.empty()) {
        ret.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return ret;
}

//int main(){
//    vector<int> arr = {7,14,10,12,2,11,29,3,4};
//    vector<int> ret = KClosestToMedian(arr, 5);
//    printVecInt(ret);
//}



/////////////////////////////////////////////////////////////////////
// Find median in a steam of integers
/////////////////////////////////////////////////////////////////////

class StreamMedian{
    
private:
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
public:
    void addNum(int data){
        if (!minHeap.empty() && data > minHeap.top()){
        	minHeap.push(data);
        }else{
        	maxHeap.push(data);
        }
        
        if (maxHeap.size() - minHeap.size() == 2) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }else if(minHeap.size() - maxHeap.size() == 2){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double median(){
        if (maxHeap.size() == minHeap.size()) {
            return ( maxHeap.top() + minHeap.top() ) / 2.0;
        }else{
            return maxHeap.size() > minHeap.size() ? maxHeap.top() : minHeap.top();
        }
    }
    
};

//int main(){
//    vector<int> stream = {3,1,4,9,5,3,10};
//    StreamMedian medianCalculator;
//    
//    for (int i=0; i<stream.size(); i++) {
//        medianCalculator.addNum(stream[i]);
//        cout << medianCalculator.median() << " ";
//    }
//    // 3 2 3 3.5 4 3.5 4
//}




/////////////////////////////////////////////////////////////////////
// find Kth smallest sum
// Given two sorted array A and B, find the Kth smallest elements
// of sorted array C formed by merging (sum) array A and B
/////////////////////////////////////////////////////////////////////


// O(klogk) time complexity O(k) space method
/////////////////////////////////////////////////////////////////////


class SumCompare{
public:
    bool operator()(const pair<int, pair<int, int>>& lhs, const pair<int, pair<int, int>>& rhs) const
    {
        return lhs.first > rhs.first;
    }
};

class PosHash{
public:
    size_t operator()(const pair<int, int>& pos) const{
        return pos.first ^ pos.second;
    }
};

// assume k is no larger than A.size() * B.size();
int findKthSmallestSum(vector<int>& A, vector<int>& B, int k){
    SumCompare cmp;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, SumCompare> minHeap(cmp);
    unordered_set<pair<int, int>, PosHash> hash;
    int currSum = -1;
    
    minHeap.emplace(A[0]+B[0], pair<int, int>(0, 0));
    hash.emplace(0, 0);
    
    while (k >= 0) {
        currSum = minHeap.top().first;
        int i = minHeap.top().second.first;
        int j = minHeap.top().second.second;
        minHeap.pop();
        
        if (i + 1 < A.size() && hash.find(pair<int, int>(i+1, j)) == hash.end()) {
            minHeap.emplace(A[i+1]+B[j], pair<int, int>(i+1, j));
            hash.emplace(i+1,j);
        }
        
        if (j+1 < B.size() && hash.find(pair<int, int>(i, j+1)) == hash.end()) {
            minHeap.emplace(A[i]+B[j+1], pair<int, int>(i, j+1));
            hash.emplace(i, j+1);
        }
        k--;
    }
    return currSum;
}

//int main(){
//    vector<int> A = {1, 4, 5, 10};
//    vector<int> B = {2, 6, 6, 7, 12, 14};
//    vector<int> answers;
//    for (int i=0; i<A.size(); i++) {
//        for (int j=0; j<B.size(); j++) {
//            answers.push_back(A[i]+B[j]);
//        }
//    }
//    sort(answers.begin(), answers.end());
//
//    for (int i=0; i<A.size()*B.size(); i++) {
//        assert(findKthSmallestSum(A, B, i) == answers[i]);
//    }
//}








