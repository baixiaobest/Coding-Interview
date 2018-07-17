//
//  Sort.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 6/18/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <list>
//#include "Utilities.h"

using namespace std;

/////////////////////////////////////////////////////////////////////
// Indirect sort
// The swap operation in sorting algorithm can be expensive if
// two element are of different lengths.
// indirect sort can solve the problem
/////////////////////////////////////////////////////////////////////


// in this example, we perform indirect sort on integer array for simplicity

class IntPointerCompare{
public:
    bool operator()(const int* a, const int* b) const{
        return *a < *b;
    }
};

void printInSortedOrder(vector<int>& arr){
    vector<int*> pointers;
    for (int i=0; i<arr.size(); i++) {
        pointers.push_back(&arr[i]);
    }
    IntPointerCompare cmp;
    sort(pointers.begin(), pointers.end(), cmp);
    
    for (int i=0; i<pointers.size(); i++) {
        cout << *pointers[i] << " ";
    }
}

//int main(){
//    vector<int> arr = {0,3,6,8,2,9,5,7,1,4};
//    printInSortedOrder(arr);
//}





/////////////////////////////////////////////////////////////////////
// counting sort on arry of objects
// You are given an array of Person objects. Each person object has a
// key. You need to rearrange the elements of the array in place
// so that objects with same key appear together using counting sort.
/////////////////////////////////////////////////////////////////////

class Person{
public:
    int m_key;
    int m_id;
	
    Person(int key, int id){
        m_key = key;
        m_id = id;
    }
};


void inPlaceCountingSort(vector<Person>& arr){
    unordered_map<int, int> mapKey2Freq;
    unordered_map<int, int> mapKey2Pointers;
    
    for (const Person &p : arr) {
        mapKey2Freq[p.m_key]++;
    }
    
    int offset = 0;
    for (const auto it : mapKey2Freq) {
        mapKey2Pointers[it.first] = offset;
        offset += it.second;
    }
    
    int range = mapKey2Freq.begin()->second;
    int firstKey = mapKey2Freq.begin()->first;
    
    for (int i=0; i<range;) {
        int key = arr[i].m_key;
        if (key != firstKey) {
            swap(arr[i], arr[mapKey2Pointers[key]]);
            mapKey2Pointers[key]++;
        }else{
            i++;
        }
    }
}



//int main(){
//    //                  0 1 2 3 4 5 6 7 8 9 10
//    vector<int> keys = {3,1,2,1,7,3,2,3,2,1,4};
//    vector<Person> input;
//    for (int i=0; i<keys.size(); i++) {
//        input.push_back(Person(keys[i], i));
//    }
//    inPlaceCountingSort(input);
//    for (int i=0; i<input.size(); i++) {
//        cout << "key: " << input[i].m_key << " id: " << input[i].m_id << endl;
//    }
//}



/////////////////////////////////////////////////////////////////////
// Given two sorted array A and B, find the elements common to
// both A and B
/////////////////////////////////////////////////////////////////////

// solution 1: brute force two loops
// solution 2: for each element in A, use binary search in B

// solution 3: The optimal solution. Think of A and B in a graph.
// search in this graph

vector<int> intersectionOfTwoSortedArrays(vector<int>& A, vector<int>& B){
    int i(0), j(0);
    vector<int> ret;
    
    while (i < A.size() && j < B.size()) {
        // remember to remove duplicates as well
        if (A[i] == B[j] && (i==0 || A[i] != A[i-1])) {
            ret.push_back(A[i]);
            i++;
            j++;
        }else if(A[i] < B[j]){
            i++;
        }else{
            j++;
        }
    }
    return ret;
}


/////////////////////////////////////////////////////////////////////
// remove duplicates from unsorted array
/////////////////////////////////////////////////////////////////////

// solution 1: use hash to store every elements in array, O(N) time, O(N) space

// solution 2: sort the array and remove duplicates. O(N) time, O(1) space

void removeDuplicates(vector<int>& arr){
    
    sort(arr.begin(), arr.end());
    int slowPtr=0;
    int fastPtr=0;
    
    while (fastPtr < arr.size()) {
        if (fastPtr !=0 && arr[fastPtr] == arr[fastPtr-1]) {
            fastPtr++;
        }else{
        	arr[slowPtr] = arr[fastPtr];
            fastPtr++;
        	slowPtr++;
        }
    }
    
    arr.resize(slowPtr);
}

//int main(){
//    vector<int> arr = {0,3,2,5,6,3,0,2,6,7,3,5,7,8,2,3,4,4,1,9};
//    removeDuplicates(arr);
//    printVecInt(arr); // 0 1 2 3 4 5 6 7 8 9
//    
//    arr = {};
//    removeDuplicates(arr);
//    printVecInt(arr);
//}




/////////////////////////////////////////////////////////////////////
// Find concurrent events
// given a set of intervals of event starting and ending times,
// find the maximum number of events that take place concurrently.
/////////////////////////////////////////////////////////////////////

class EventCompare{
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const{
        if (a.second != b.second) {
            return a.second < b.second;
        }else{
            return a.first < b.first;
        }
    }
};

int findNumOfConcurrentEvents(vector<pair<int, int>>& events){
    //      <start/end, time>
    vector<pair<int, int>> startsAndEnds;
    
    for (const auto event : events) {
        startsAndEnds.emplace_back(0, event.first);
        startsAndEnds.emplace_back(1, event.second);
    }
    EventCompare cmp;
    sort(startsAndEnds.begin(), startsAndEnds.end(), cmp);
    
    int count = 0;
    int maxCount = 0;
    for (const auto point : startsAndEnds) {
        // start point
        if (point.first == 0) {
            count++;
            max(maxCount, count);
        }else{ // end point
            count--;
        }
    }
    return maxCount;
}

//int main(){
//    vector<pair<int, int>> events = {{1,5},{6,10},{11,13},{14,15},{2,7},{8,9},{12,15},{4,5},{9,17}};
//    assert(findNumOfConcurrentEvents(events) == 3);
//}



/////////////////////////////////////////////////////////////////////
// Union of the intervals
// given a set of intervals, find the union of them
/////////////////////////////////////////////////////////////////////

enum EndPointType {OPEN, CLOSED};

class EndPoint{
public:
    
    EndPointType m_type;
    int m_val;
    
    EndPoint(int val, EndPointType type): m_val(val), m_type(type) {}
    
    bool operator<(EndPoint& other) const{
        return m_val < other.m_val;
    }
    bool operator>(EndPoint& other) const{
        return m_val > other.m_val;
    }
    
    bool operator==(EndPoint& other) const{
        return m_val == other.m_val;
    }
};

class Interval{
public:
    EndPoint start;
    EndPoint end;
    
    Interval(EndPoint st, EndPoint ed): start(st), end(ed){}
    Interval(int st, EndPointType stType, int ed, EndPointType edType)
    		: start(st, stType), end(ed, edType){}
};

class IntervalCompare{
public:
    bool operator()(const Interval& a, const Interval& b) const{
        if (a.start.m_val != b.start.m_val) {
            return a.start.m_val < b.start.m_val;
        }else {
            return b.start.m_type == OPEN;
        }
    }
};

bool inRange(EndPoint& pt, Interval& inv){
    return pt.m_val >= inv.start.m_val && pt.m_val <= inv.end.m_val;
}

vector<Interval> UnionOfIntervals(vector<Interval>& intervals){
    IntervalCompare cmp;
    sort(intervals.begin(), intervals.end(), cmp);
    
    vector<Interval> Union;
    Interval newInv = intervals[0];
    
    for (int i=1; i<intervals.size(); i++) {
        Interval currInv = intervals[i];
        if (inRange(currInv.start, newInv)) {
            if (newInv.end < currInv.end
            || (newInv.end == currInv.end && (newInv.end.m_type == OPEN)))
            {
                newInv.end = currInv.end;
            }
        }else{
            Union.push_back(newInv);
            newInv = currInv;
        }
    }
    Union.push_back(newInv);
    
    return Union;
}

EndPointType intToEnum(int a){
    if (a == 0) {
        return OPEN;
    }else{
        return CLOSED;
    }
}

//int main(){
//    vector<pair<int, int>> points = {{0,3},{5,7},{9,11},{12,14},{1,1},{3,4},{7,8},{12,16},{2,4},{8,11},{13,13},{16,17}};
//    vector<pair<int, int>> types = {{0,0},{1,0},{0,1},{1,1},{1,1},{1,0},{1,0},{0,1},{1,1},{1,0},{0,0},{0,0}};
//    
//    vector<Interval> intervals;
//    
//    for (int i=0; i<points.size(); i++) {
//        intervals.emplace_back(points[i].first, intToEnum(types[i].first), points[i].second, intToEnum(types[i].second));
//    }
//    
//    vector<Interval> res = UnionOfIntervals(intervals);
//    
//}


/////////////////////////////////////////////////////////////////////
// Assume above problem does not consider the case of open interval.
// all endpoints are inclusive
/////////////////////////////////////////////////////////////////////

class SimpleIntervalCompare{
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const{
        return a.first < b.first;
    }
};

vector<pair<int, int>> unionOfSimpleIntervals(vector<pair<int, int>>& intervals){
    SimpleIntervalCompare cmp;
    sort(intervals.begin(), intervals.end(), cmp);
    
    pair<int, int> newInv = intervals[0];
    vector<pair<int, int>> Union;
    
    for (int i=1; i<intervals.size(); i++) {
        auto currInv = intervals[i];
        if (currInv.first >= newInv.first && currInv.first <= newInv.second){
            newInv.second = max(currInv.second, newInv.second);
        }else{
            Union.push_back(newInv);
            newInv = currInv;
        }
    }
    Union.push_back(newInv);
    
    return Union;
}

//int main(){
//    vector<pair<int, int>> intervals = {{0,3},{5,7},{9,11},{12,14},{1,1},{3,4},{7,8},{12,16},{2,4},{8,11},{13,13},{16,17}};
//
//    vector<pair<int, int>> res = unionOfSimpleIntervals(intervals);
//
//}



/////////////////////////////////////////////////////////////////////
// Given a set of intervals, find the minimum points that require to
// cover all the intervals
/////////////////////////////////////////////////////////////////////

class LeftCompare{
public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const{
        return lhs.first > rhs.first;
    }
};

class RightCompare{
public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) const{
        return lhs.second > rhs.second;
    }
};

vector<int> findCoveringPoints(vector<pair<int, int>>& intervals){
    vector<int> ret;
    vector<pair<int, int>> leftOrder;
    vector<pair<int, int>> rightOrder;
    
    copy(intervals.begin(), intervals.end(), back_inserter(leftOrder));
    copy(intervals.begin(), intervals.end(), back_inserter(rightOrder));
    sort(leftOrder.begin(), leftOrder.end(), LeftCompare());
    sort(rightOrder.begin(), rightOrder.end(), RightCompare());
    
    while (!rightOrder.empty()) {
        int curr = rightOrder.back().second;
        ret.push_back(curr);
        
        while (!leftOrder.empty() && leftOrder.back().first <= curr) {
            rightOrder.erase(find(rightOrder.begin(), rightOrder.end(), leftOrder.back()));
            leftOrder.pop_back();
        }
    }
    
    return ret;
}


//int main(){
//    vector<pair<int, int>> intervals = {{0,3},{2,4},{1,8},{1,3},{4,6},{7,10},{8,11},{11,13},{13,14},{10,13}};
//    vector<int> ret = findCoveringPoints(intervals);
//    printVecInt(ret); // 3 6 10 13
//
//}




/////////////////////////////////////////////////////////////////////
// Three Sum
/////////////////////////////////////////////////////////////////////


bool threeSum(vector<int>& arr, int target){
    sort(arr.begin(), arr.end());
    
    for (int i=1; i<arr.size()-1; i++) {
        int left = 0;
        int right = arr.size()-1;
        while (left < i && right > i) {
            int sum = arr[left] + arr[i] + arr[right];
            if (sum < target) {
                left++;
            }else if(sum > target){
                right--;
            }else{
                return true;
            }
        }
    }
    return false;
}

//int main(){
//    vector<int> arr = {1, 3, 5, 6, 8};
//    assert(threeSum(arr, 9) == true);
//    assert(threeSum(arr, 8) == false);
//    assert(threeSum(arr, 12) == true);
//    assert(threeSum(arr, 17) == true);
//    assert(threeSum(arr, 20) == false);
//}



/////////////////////////////////////////////////////////////////////
// Pancake Sorting
/////////////////////////////////////////////////////////////////////

void flip(vector<int>& arr, int k){
    k = k >= arr.size() ? arr.size()-1 : k;
    reverse(arr.begin(), arr.begin() + k + 1);
}


void pancakeSorting(vector<int>& arr){
    for (int i=arr.size()-1; i >= 0; i--) {
        int maxIdx = i;
        int max = arr[i];
        for (int j=i-1; j>=0; j--) {
            if (arr[j] > max) {
                maxIdx = j;
                max = arr[j];
            }
        }
        flip(arr, maxIdx);
        flip(arr, i);
    }
}


//int main(){
//    vector<int> arr = {3,1,7,5,9,8,2,4,6};
//    pancakeSorting(arr);
//    printVecInt(arr);
//}






