//
//  Queue.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 6/5/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <assert.h>

using namespace std;

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int myData){
        data = myData;
        left = nullptr;
        right = nullptr;
    }
    
    void leftAttach(TreeNode* leftNode){
        left = leftNode;
    }
    
    void rightAttach(TreeNode* rightNode){
        right = rightNode;
    }
};

void printVec(vector<int>& Arr){
    for (int i=0; i<Arr.size(); i++) {
        cout << Arr[i] << " ";
    }
    cout << endl;
}


/////////////////////////////////////////////////////////////////////
// Print Binary Tree in level order traversal
/////////////////////////////////////////////////////////////////////


void LevelOrderPrint(TreeNode* root){
    queue<TreeNode*> myQ;
    myQ.push(root);
    
    while (!myQ.empty()) {
        TreeNode* curr = myQ.front();
        myQ.pop();
        cout << curr->data << " ";
        if (curr->left){
        	myQ.push(curr->left);
        }
        if(curr->right){
        	myQ.push(curr->right);
        }
    }
}

//int main(){
//    TreeNode a = TreeNode(4);
//    TreeNode b = TreeNode(2);
//    TreeNode c = TreeNode(5);
//    TreeNode d = TreeNode(1);
//    TreeNode e = TreeNode(6);
//    TreeNode f = TreeNode(3);
//    TreeNode g = TreeNode(8);
//    TreeNode h = TreeNode(7);
//    TreeNode i = TreeNode(9);
//    
//    d.leftAttach(&b);
//    b.leftAttach(&a);
//    b.rightAttach(&c);
//    d.rightAttach(&f);
//    f.leftAttach(&e);
//    f.rightAttach(&h);
//    h.leftAttach(&g);
//    h.rightAttach(&i);
//    
//    LevelOrderPrint(&d);
//}





/////////////////////////////////////////////////////////////////////
// Circular Queue
// implement circular queue using array
/////////////////////////////////////////////////////////////////////


class CircularQueue{
private:
    vector<int> array;
    size_t start;
    size_t end;
    size_t count;
public:
    CircularQueue(size_t capacity): start(0), end(0), count(0){
        capacity = capacity < 1 ? 1 : capacity;
        array = vector<int>(capacity);
    }
    
    void enqueue(int ele){
        if (count == array.size()) {
            rotate(array.begin(), array.begin()+start, array.end());
            start = 0;
            end = array.size();
            size_t newCapacity = array.size() << 1;
            array.resize(newCapacity);
        }
        count++;
        array[end] = ele;
        end = (end+1) % array.size();
    }
    
    void dequeue(){
        if (count > 0){
            count--;
        	start = (start+1) % array.capacity();
        }
    }
    
    size_t size(){
        return count;
    }
    
    int front(){
        return array[start];
    }

};

//int main(){
//    CircularQueue q(1);
//    q.enqueue(1);
//    assert(q.front() == 1);
//    assert(q.size() == 1);
//
//    q.dequeue();
//    assert(q.size() == 0);
//    
//    q.enqueue(1);
//    q.enqueue(2);
//    assert(q.front() == 1);
//    assert(q.size() == 2);
//    
//    q.enqueue(3);
//    q.dequeue();
//    q.enqueue(4);
//    q.dequeue();
//    q.enqueue(5);
//    assert(q.size() == 3);
//    assert(q.front() == 3);
//    
//    q.enqueue(6);
//}



/////////////////////////////////////////////////////////////////////
// Implement a queue with two stacks
/////////////////////////////////////////////////////////////////////

class TwoStackQueue{
private:
    stack<int> inputStack;
    stack<int> outputStack;
    size_t m_size;
    
    void transfer(stack<int>& fromStack, stack<int>& toStack){
        while (!fromStack.empty()) {
            toStack.push(fromStack.top());
            fromStack.pop();
        }
    }
    
public:
    TwoStackQueue():m_size(0){}
    
    void enqueue(int ele){
        m_size++;
        inputStack.push(ele);
    }
    
    void dequeue(){
        if (m_size==0)
            return;
        if(outputStack.empty())
        	transfer(inputStack, outputStack);
        outputStack.pop();
        m_size--;
    }
    
    int front(){
        if(outputStack.empty())
            transfer(inputStack, outputStack);
        return outputStack.top();
    }
    
    size_t size(){
        return m_size;
    }
};


//int main(){
//    TwoStackQueue q;
//    q.enqueue(1);
//    assert(q.front() == 1);
//    assert(q.size() == 1);
//
//    q.dequeue();
//    assert(q.size() == 0);
//
//    q.enqueue(1);
//    q.enqueue(2);
//    assert(q.front() == 1);
//    assert(q.size() == 2);
//
//    q.enqueue(3);
//    q.dequeue();
//    q.enqueue(4);
//    q.dequeue();
//    q.enqueue(5);
//    assert(q.size() == 3);
//    assert(q.front() == 3);
//
//    q.enqueue(6);
//}

/////////////////////////////////////////////////////////////////////
// Max Queue
// queue with max operation
/////////////////////////////////////////////////////////////////////

class MaxQueue{
    
private:
    queue<int> Q;
    deque<int> maxQ;
    size_t m_size;
    
public:
    MaxQueue():m_size(0){}
    
    void enqueue(int ele){
        Q.push(ele);
        while (!maxQ.empty() && ele > maxQ.back()) {
            maxQ.pop_back();
        }
        maxQ.push_back(ele);
        m_size++;
    }
    
    void dequeue(){
        if (Q.size() == 0) {
            return;
        }
        if (maxQ.front() == Q.front()) {
            maxQ.pop_front();
        }
        Q.pop();
        m_size--;
    }
    
    int max(){
        return maxQ.front();
    }
    
    size_t size(){
        return m_size;
    }
};


//int main(){
//    MaxQueue q;
//    q.enqueue(5);
//    assert(q.max() == 5);
//    q.enqueue(3);
//    assert(q.max() == 5);
//    q.enqueue(5);
//    q.dequeue();
//    assert(q.max() == 5);
//    q.dequeue();
//    q.enqueue(4);
//    q.enqueue(3);
//    q.dequeue();
//    assert(q.max() == 4);
//}



/////////////////////////////////////////////////////////////////////
// Maximum of a sliding window
// given an array of integers, find the max in the sliding window of size w
/////////////////////////////////////////////////////////////////////


vector<int> maxOfSlidingWindow(vector<int>& array, int WSize){
    vector<int> ret;
    MaxQueue maxQ;
    
    for (int i=0; i<array.size(); i++) {
        maxQ.enqueue(array[i]);
        if (maxQ.size() == WSize) {
            ret.push_back(maxQ.max());
            maxQ.dequeue();
        }
    }
    return ret;
}

//int main(){
//    vector<int> array = {2,3,4,2,6,9,8,4,5,3,9};
//    vector<int> retW1 = maxOfSlidingWindow(array, 1);
//    vector<int> retW2 = maxOfSlidingWindow(array, 2);
//    vector<int> retW3 = maxOfSlidingWindow(array, 3);
//    vector<int> retW11 = maxOfSlidingWindow(array, 11);
//    
//    printVec(retW1);     // 2 3 4 2 6 9 8 4 5 3 9
//    printVec(retW2);     // 3 4 4 6 9 9 8 5 5 9
//    printVec(retW3);     // 4 4 6 9 9 9 8 5 9
//    printVec(retW11);    // 9
//}



