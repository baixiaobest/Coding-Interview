//
//  HashTables.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 5/2/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>
#include <list>
#include <cmath>
#include <limits.h>

using namespace std;


/////////////////////////////////////////////////////////////////////
//Find nearest repetition of a word in an array of string
/////////////////////////////////////////////////////////////////////

string findNearestRepetition(vector<string>& paragraph){
    unordered_map<string, int> mapStr2Idx;
    int closestDist = INT_MAX;
    string closestWord = "";

    for (int i=0; i<paragraph.size(); i++) {
        // check if word is seen before
        if (mapStr2Idx.find(paragraph[i]) != mapStr2Idx.end()) {
            int distance = i - mapStr2Idx[paragraph[i]];
            // if it is the closest word so far, update closest word and closest distance
            if (distance < closestDist) {
                closestDist = distance;
                closestWord = paragraph[i];
            }
        }

        // then update hash table
        mapStr2Idx[paragraph[i]] = i;
    }

    return closestWord;
}

//int main(){
//    vector<string> input1 = {"all","work","and","no","play","makes","for","no","work","no","fun","and","no","results"};
//    assert(findNearestRepetition(input1) == "no");
//}


/////////////////////////////////////////////////////////////////////
//Compress an array of binary trees
/////////////////////////////////////////////////////////////////////

struct TreeNodeH{
    int data;
    TreeNodeH* left;
    TreeNodeH* right;
    size_t hashCode;
    TreeNodeH(int myData){
        data = myData;
        left = nullptr;
        right = nullptr;
        hashCode = 0;
    }

    void leftAttach(TreeNodeH* leftNode){
        left = leftNode;
    }

    void rightAttach(TreeNodeH* rightNode){
        right = rightNode;
    }

    bool compare(const TreeNodeH *other) const{
        if(!other) return false;

        bool leftCheck = (!left && !other->left) || (left && left->compare(other->left));
        bool rightCheck = (!right && !other->right) || (right && right->compare(other->right));

        return data == other->data && leftCheck && rightCheck;
    }

    bool operator==(const TreeNodeH &other) const{
        return compare(&other);
    }
};

struct NodeHash{
    size_t operator()(const TreeNodeH& key) const{
        return key.hashCode;
    }
};

size_t computeHashForTree(TreeNodeH* root){
    if (!root) {
        return 0;
    }

    if(!(root->hashCode)){
    	size_t nodeHash = 3*root->data;
    	size_t leftHash = 5*computeHashForTree(root->left);
    	size_t rightHash = 7*computeHashForTree(root->right);
        root->hashCode = nodeHash+leftHash+rightHash;
    }

    return root->hashCode;
}

TreeNodeH* mergeRecursive(TreeNodeH* root, unordered_map<TreeNodeH, TreeNodeH*, NodeHash>& treeSet){
    if (!root) {
        return root;
    }

    if (treeSet.find(*root) != treeSet.end()) {
        return treeSet[*root];
    }else{
        root->left = mergeRecursive(root->left, treeSet);
        root->right = mergeRecursive(root->right, treeSet);
        treeSet[*root] = root;
        return root;
    }
}

vector<TreeNodeH*> mergeTrees(vector<TreeNodeH*> trees){

    // map from hashCode to node
    unordered_map<TreeNodeH, TreeNodeH*, NodeHash> treeSet;
    // new trees
    vector<TreeNodeH*> resultTrees;

    // for each tree
    for (int i=0; i<trees.size(); i++) {
        TreeNodeH* root = trees[i];
        computeHashForTree(root);
        resultTrees.push_back(mergeRecursive(root, treeSet));
    }

    return resultTrees;
}


//int main(){
//    TreeNodeH tree1 = TreeNodeH(3);
//    TreeNodeH a = TreeNodeH(2);
//    TreeNodeH b = TreeNodeH(1);
//    TreeNodeH c = TreeNodeH(0);
//    tree1.leftAttach(&a);
//    a.leftAttach(&b);
//    b.leftAttach(&c);
//
//
//    TreeNodeH tree2 = TreeNodeH(9);
//    TreeNodeH d = TreeNodeH(11);
//    TreeNodeH e = TreeNodeH(5);
//    TreeNodeH f = TreeNodeH(3);
//    TreeNodeH g = TreeNodeH(7);
//    tree2.rightAttach(&d);
//    tree2.leftAttach(&e);
//    e.leftAttach(&f);
//    e.rightAttach(&g);
//
//
//    TreeNodeH tree3 = TreeNodeH(2);
//    TreeNodeH h = TreeNodeH(1);
//    TreeNodeH i = TreeNodeH(0);
//    TreeNodeH j = TreeNodeH(5);
//    TreeNodeH k = TreeNodeH(3);
//    TreeNodeH l = TreeNodeH(7);
//
//    tree3.leftAttach(&h);
//    h.leftAttach(&i);
//    tree3.rightAttach(&j);
//    j.leftAttach(&k);
//    j.rightAttach(&l);
//
//    vector<TreeNodeH*> inputTrees = {&tree1, &tree2, &tree3};
//    vector<TreeNodeH*> trees = mergeTrees(inputTrees);
//
//}


/////////////////////////////////////////////////////////////////////
//Given a string, whether it can be permuted into palindrome
/////////////////////////////////////////////////////////////////////


bool canBePalindrome(string str){
    vector<int> charCount = vector<int>(26, 0);
    int oddCount = 0;

    for (int i=0; i<str.length(); i++) {
        charCount[str[i]-'a']++;
    }

    for (int i=0; i<26; i++) {
        if (charCount[i] % 2 != 0) {
            oddCount++;
        }
    }
    return oddCount <= 1;
}

//int main(){
//    assert(canBePalindrome("edified"));
//    assert(canBePalindrome("aaabbbb"));
//    assert(!canBePalindrome("aaabbb"));
//}


/////////////////////////////////////////////////////////////////////
//Given a set of points, find the line the goes through most of points
/////////////////////////////////////////////////////////////////////


struct Point{
    int x;
    int y;

    Point(){
        x = 0; y = 0;
    }
    Point(int xCor, int yCor){
        x = xCor;
        y = yCor;
    }
    bool operator==(const Point& other) const{
        return other.x == x && other.y == y;
    }
};


struct HashPoint{
    size_t operator()(const Point& point) const{
        return (size_t) point.x ^ point.y;
    }
};

class Line{
public:
    pair<float, float> slope;
    pair<float, float> intercept;

    Line(){
        slope = pair<int, int>(0,0);
        intercept = pair<int, int>(0,0);
    }

    Line(Point& pt1, Point& pt2){
        float length;

        // two point at the same location cannot form a line
        if (pt1 == pt2) {
            slope = pair<int, int>(0,0);
            intercept = pair<int, int>(0,0);
            return;
        }

        if (pt1.x > pt2.x) {
            swap(pt1, pt2);
        }

        // calculate normalized slope
        slope.first = pt2.x - pt1.x;
        slope.second = pt2.y - pt1.y;
        length = sqrt(slope.first * slope.first + slope.second * slope.second);
        slope.first /= length;
        slope.second /= length;

        // calculate intercept at y axis or x axis
        if (pt1.y == pt2.y) {
            intercept = pair<int, int>(pt1.y, 0);
        }else if(pt1.x == pt2.x){
            intercept = pair<int, int>(0, pt1.x);
            slope.second = abs(slope.second);
        }else{
            float YIntercept = pt1.y - slope.second/slope.first*pt1.x;
            intercept = pair<float, float>(YIntercept, 0);
        }
    }

    bool operator==(const Line& other) const{
        return slope == other.slope && intercept == other.intercept;
    }
};

struct LineHash{
    size_t operator()(const Line& line) const{
        return size_t( line.slope.first*1000 + line.slope.second*100 + line.intercept.first*10 + line.intercept.second );
    }
};


Line GetLineWithMostPoints(vector<Point> points){
    // map a line to the points that the line goes through
    unordered_map<Line, unordered_set<Point, HashPoint>, LineHash> mapLineToPoint;
    unsigned long max = 0;
    Line candidateLine; // line that may potentially go through most points

    // for every pair of points in space forms a line
    for (int i=0; i<points.size(); i++) {
        for (int j=i+1; j<points.size(); j++) {
            // for every line, it is mapped to frequency
            Line line = Line(points[i], points[j]);
            auto it = mapLineToPoint.find(line);

            if (it == mapLineToPoint.end()) {
                mapLineToPoint[line] = unordered_set<Point, HashPoint>();
            }
            mapLineToPoint[line].insert(points[i]);
            mapLineToPoint[line].insert(points[j]);
        }
    }

    // iterate through every line in the map and find the line with largest frequency
    for (auto it = mapLineToPoint.begin(); it != mapLineToPoint.end(); it++) {
        unsigned long pointSetSize = it->second.size();
        if (pointSetSize >= max) {
            candidateLine = it->first;
            max = (int) it->second.size();
        }
    }

    return candidateLine;
}

//int main(){
//    vector<Point> pointArr = {Point(1,2), Point(2,2), Point(2,1), Point(3,1), Point(3,3), Point(3,-1)};
//    Line line = GetLineWithMostPoints(pointArr);
//
//}


/////////////////////////////////////////////////////////////////////
//Given a large array of words A, small array of words Q, find the
//shortest subarray of A that convers all the words in Q.
/////////////////////////////////////////////////////////////////////


pair<int, int> smallestSubarray(vector<string>& paragraph, vector<string>& query){
    unordered_map<string, int> mapWord2Frequency;  // map query word to frequencies in sliding window
    int numUniqueWords = 0; // number of unique words appear in sliding window
    int left(0), right(0); // two pointers representing the bundary of sliding window
    int start(0), end(0); // start and end point for smallest subarray
    int size = paragraph.size();
    int minLength = INT_MAX; // minimum length of subarray

    for(int i=0; i<query.size(); i++){
        mapWord2Frequency[query[i]] = 0;
    }

    while (right < size || right - left >= mapWord2Frequency.size()) {
        // if sliding window contains all the words, then store the subarray indices
        if (numUniqueWords >= mapWord2Frequency.size() && (right - left) < minLength) {
            start = left;
            end = right;
            minLength = right - left;
        }

        // if sliding window does not contain all the words and right boundary can expand
        if(numUniqueWords < mapWord2Frequency.size() && right < size){

            auto it = mapWord2Frequency.find(paragraph[right]);
            if (it != mapWord2Frequency.end()){
                if (it->second == 0)
                    numUniqueWords++;
            	it->second += 1;
            }
            right++;

        // sliding window contains all the words and thus we can shrink left boundary
        }else{
            auto it = mapWord2Frequency.find(paragraph[left]);
            if (it != mapWord2Frequency.end()) {
                it->second -= 1;
                if (it->second == 0)
                    numUniqueWords--;
            }
            left++;
        }
    }

    return pair<int, int>(start, end);
}

void printSubarray(vector<string>& paragraph, pair<int, int> idx){
    for(int i=idx.first; i<idx.second; i++){
    	cout << paragraph[i] << " ";
    }
    cout << endl;
}

//int main(){
//    vector<string> in1 = {"find"};
//    vector<string> q1 = {"find"};
//    vector<string> q12 = {"yes"};
//    pair<int, int> res = smallestSubarray(in1, q1);
//    printSubarray(in1, res);
//    res = smallestSubarray(in1, q12);
//    printSubarray(in1, res);
//
//    vector<string> in2 = {"find", "me", "some", "food"};
//    vector<string> q2 = {"find", "some"};
//    res = smallestSubarray(in2, q2);
//    printSubarray(in2, res);
//
//    vector<string> in3 = {"find", "me", "some", "food", "yes","find"};
//    vector<string> q3 = {"find", "food"};
//    res = smallestSubarray(in3, q3);
//    printSubarray(in3, res);
//
//
//    vector<string> in4 = {"find", "me", "some", "food", "yes","find","find","find","some","food"};
//    vector<string> q4 = {"find", "some", "food"};
//    res = smallestSubarray(in4, q4);
//    printSubarray(in4, res);
//
//}


// when the input paragraph is too long, we cannot store them on RAM.
// instead, we need to digest on word at a time.

class KeywordSearch{
    unordered_map<string, int> mapWord2Frequency;
    list<string> window;
    vector<string> subarray;
    unsigned long minLength;
    int start;
    int end;
    int numUniqueWords;

public:
    KeywordSearch():start(0), end(0), minLength(INT_MAX), numUniqueWords(0){}

    KeywordSearch(vector<string> keywords):start(0), end(0), minLength(INT_MAX), numUniqueWords(0)
    {
        SetKeywords(keywords);
    }

    void SetKeywords(vector<string> keywords){
        clear();
        for (int i=0; i<keywords.size(); i++) {
            mapWord2Frequency[keywords[i]] = 0;
        }
    }

    void clear(){
        mapWord2Frequency.clear();
        window.clear();
        subarray.clear();
        minLength = INT_MAX;
        start = 0;
        end = 0;
        numUniqueWords = 0;
    }

    void digest(string word){

        window.push_back(word);
        auto it = mapWord2Frequency.find(word);
        if (it != mapWord2Frequency.end()) {
            if (it->second == 0)
                numUniqueWords++;
            it->second++;
        }

        if (numUniqueWords >= mapWord2Frequency.size() && numUniqueWords!=0){
            string frontEle = "";
        	while (numUniqueWords >= mapWord2Frequency.size()) {

            	frontEle = window.front();
                window.pop_front();
            	auto it = mapWord2Frequency.find(frontEle);

            	if (it != mapWord2Frequency.end()) {
                	it->second--;
                	if (it->second == 0)
                	    numUniqueWords--;
            	}
        	}
            if (window.size()+1 < minLength) {
                minLength = window.size() + 1;
                subarray.clear();
                subarray.push_back(frontEle);
                for (auto it = window.begin(); it != window.end(); it++) {
                    subarray.push_back(*it);
                }
            }
        }
    }

    vector<string> getSubArray(){
        return subarray;
    }
};

void printVecString(vector<string>& strArr){
    for (int i=0; i<strArr.size(); i++) {
        cout << strArr[i] << " ";
    }
    cout << endl;
}

void KeywordTest(KeywordSearch& ks, vector<string> input){
    for (int i=0; i<input.size(); i++) {
        ks.digest(input[i]);
    }
    vector<string> result = ks.getSubArray();
    printVecString(result);
}

//int main(){
//    KeywordSearch ks;
//    vector<string> in1 = {"find"};
//    vector<string> q1 = {"find"};
//    vector<string> q12 = {"yes"};
//    ks.SetKeywords(q1);
//    KeywordTest(ks, in1);
//    ks.SetKeywords(q12);
//    KeywordTest(ks, in1);
//
//    vector<string> in2 = {"find", "me", "some", "food"};
//    vector<string> q2 = {"find", "some"};
//    ks.SetKeywords(q2);
//    KeywordTest(ks, in2);
//
//    vector<string> in3 = {"find", "me", "some", "food", "yes","find"};
//    vector<string> q3 = {"find", "food"};
//    ks.SetKeywords(q3);
//    KeywordTest(ks, in3);
//
//    vector<string> in4 = {"find", "me", "some", "food", "yes","find","find","find","some","food"};
//    vector<string> q4 = {"find", "some", "food"};
//    ks.SetKeywords(q4);
//    KeywordTest(ks, in4);
//
//    ks.SetKeywords({});
//    KeywordTest(ks, in4);
//}


/////////////////////////////////////////////////////////////////////
// ISBN cache
/////////////////////////////////////////////////////////////////////


class ISBNCache{
private:
    int capacity;
    //       isbn  price
    list<pair<int, int>> cache;
    //            isbn      iterator to cache list node
    unordered_map<int, list<pair<int, int>>::iterator> hash;

    void moveFront(list<pair<int, int>>::iterator it){
        pair<int, int> node = *it;
        cache.erase(it);
        cache.push_front(node);
        hash[node.first] = cache.begin();
    }

public:
    ISBNCache(int cap): capacity(cap){
        cache = list<pair<int, int>>();
        hash = unordered_map<int, list<pair<int, int>>::iterator>();
    }

    // return price for book
    // return -1 if not found
    int lookupPrice(int isbn){
        auto it = hash.find(isbn);
        if (it == hash.end()) {
            return -1;
        }else{
        	int price = hash[isbn]->second;
        	moveFront(hash[isbn]);
        	return price;
        }
    }

    void insert(int isbn, int price){
        auto it = hash.find(isbn);
        if (it != hash.end()) {
            it->second->second = price;
            moveFront(it->second);
        }else{
            if(cache.size() == capacity){
                hash.erase(cache.back().first);
                cache.pop_back();
            }
            pair<int, int> node(isbn, price);
            cache.push_front(node);
            hash[isbn] = cache.begin();
        }
    }

    void erase(int isbn){
        auto it = hash.find(isbn);
        if (it != hash.end()) {
            cache.erase(it->second);
            hash.erase(isbn);
        }
    }
};

//int main(){
//    ISBNCache cache(4);
//    cache.insert(1, 0);
//    assert(cache.lookupPrice(1) == 0);
//    cache.insert(1, 1);
//    assert(cache.lookupPrice(1) == 1);
//    cache.insert(2, 2);
//    cache.insert(3, 3);
//    cache.insert(4, 4);
//    cache.lookupPrice(1);
//    cache.insert(5, 5);
//    assert(cache.lookupPrice(2) == -1);
//    assert(cache.lookupPrice(3) == 3);
//    cache.insert(6, 6);
//    assert(cache.lookupPrice(4) == -1);
//    cache.erase(1);
//    assert(cache.lookupPrice(1) == -1);
//}



