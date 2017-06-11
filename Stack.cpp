//
//  Stack.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 6/4/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//
// total 7 problems

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <stack>

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


struct JumpNode{
    int data;
    int order;
    JumpNode* next;
    JumpNode* jump;
    
    JumpNode(int val){
        data = val;
        order = -1;
        next = nullptr;
        jump = nullptr;
    }
    
    JumpNode* Emplace(int val){
        next = new JumpNode(val);
        return next;
    }
    
    void PrintListNode(){
        JumpNode* ptr = this;
        while(ptr){
            std::cout << ptr->data << "(" << ptr->order << ") ";
            ptr = ptr->next;
        }
    }
};


void printStack(stack<int>& s){
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
}

void populateStack(stack<int>& s, vector<int> a){
    for (int i=a.size()-1; i>=0; i--) {
        s.push(a[i]);
    }
}


/////////////////////////////////////////////////////////////////////
// stack with max operation in O(1) time
/////////////////////////////////////////////////////////////////////



class myStack{

private:
    vector<int> stack;
    vector<int> maxStack;
    
public:
    void push(int data){
        stack.push_back(data);
        if (maxStack.empty() || data >= maxStack.back()) {
            maxStack.push_back(data);
        }
    }
    
    void pop(){
        if (stack.empty()) {
            return;
        }
        int data = stack.back();
        stack.pop_back();
        if (data == maxStack.back()) {
            maxStack.pop_back();
        }
    }
    
    int top(){
        return stack.back();
    }
    
    int max(){
        return maxStack.back();
    }
};

//int main(){
//    myStack stack = myStack();
//    stack.push(1);
//    
//    assert(stack.top()==1);
//    assert(stack.max()==1);
//    
//    stack.push(3);
//    assert(stack.top() == 3);
//    assert(stack.max() == 3);
//    
//    stack.push(2);
//    assert(stack.top() == 2);
//    assert(stack.max() == 3);
//    
//    stack.pop();
//    assert(stack.max() == 3);
//    
//    stack.pop();
//    assert(stack.max() == 1);
//    
//    stack.push(2);
//    stack.push(3);
//    stack.push(4);
//    stack.push(5);
//    stack.push(6);
//    
//    assert(stack.max() == 6);
//    stack.pop();
//    assert(stack.max() == 5);
//}



/////////////////////////////////////////////////////////////////////
// expression evaluation
/////////////////////////////////////////////////////////////////////

bool isOperator(string op){
    return op == "+" || op == "-" || op=="*" || op=="/";
}

float evalOperator(float a, float b, string op){
    if (op == "+") {
        return a + b;
    }else if(op == "-"){
        return a - b;
    }else if(op == "*"){
        return a * b;
    }else{
        return a / b;
    }
}

float evaluate(vector<string> arr){
    stack<float> exprStack;
    for (int i=0; i<arr.size(); i++) {
        if (isOperator(arr[i])) {
            float b = exprStack.top();
            exprStack.pop();
            float a = exprStack.top();
            exprStack.pop();
            exprStack.push(evalOperator(a, b, arr[i]));
        }else{
            exprStack.push(stoi(arr[i]));
        }
    }
    return exprStack.top();
}


//int main(){
//    assert(evaluate({"3", "4", "*", "1", "2", "+", "+"}) == 15);
//    assert(evaluate({"1", "1", "+", "-2", "*"}) == -4);
//    cout <<  evaluate({"4", "6", "/", "2", "/"});
//}


/////////////////////////////////////////////////////////////////////
// Print all nodes in BST
/////////////////////////////////////////////////////////////////////


void printBST(TreeNode* root){
    stack<pair<TreeNode*, int>> myStack;
    myStack.push(pair<TreeNode*, int>(root, 0));
    
    while (!myStack.empty()) {
        pair<TreeNode*, int> curr = myStack.top();

        // node visited first time
        if (curr.second == 0) {
            myStack.top().second++;
            if(curr.first->left)
                myStack.push(pair<TreeNode*, int>(curr.first->left, 0));
            
        // node visited second time
        }else{
            myStack.pop();
            cout << curr.first->data << " ";
            if (curr.first->right) {
                myStack.push(pair<TreeNode*, int>(curr.first->right, 0));
            }
        }
    }
}

void printBST2(TreeNode* root){
    stack<TreeNode*> myStack; // it saves visited nodes
    TreeNode* curr = root;
    while (!myStack.empty() || curr) {
        // curr node is visited first time
        if (curr) {
            myStack.push(curr);
            curr = curr->left;
        // curr node is visited second time
        }else{
            curr = myStack.top();
            myStack.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
}

//int main(){
//    TreeNode a = TreeNode(1);
//	TreeNode b = TreeNode(2);
//    TreeNode c = TreeNode(3);
//    TreeNode d = TreeNode(4);
//    TreeNode e = TreeNode(5);
//    TreeNode f = TreeNode(6);
//    TreeNode g = TreeNode(7);
//    TreeNode h = TreeNode(8);
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
//    printBST2(&d);     // 1 2 3 4 5 6 7 8 9
//}


/////////////////////////////////////////////////////////////////////
// Search posting lists
// Both in iterative and recursive way, gives every node in posting
// list an order they are printed.
// jump node is traversed first than next node
/////////////////////////////////////////////////////////////////////


void AssignOrderHelper(JumpNode* head, int& num){
    if (!head || head->order!=-1) {
        return;
    }
    head->order = num++;
    AssignOrderHelper(head->jump, num);
    AssignOrderHelper(head->next, num);
}

void AssignOrderRecv(JumpNode* head){
    int num = 1;
    AssignOrderHelper(head, num);
}

void AssignOrderIterative(JumpNode* head){
    stack<JumpNode*> myStack;
    myStack.push(head);
    int order = 1;
    
    while (!myStack.empty()) {
        JumpNode* curr = myStack.top();
        myStack.pop();
        
        if (curr && curr->order == -1) {
            curr->order = order++;
            myStack.push(curr->next);
            myStack.push(curr->jump);
        }
    }
}

//int main(){
//    JumpNode* a = new JumpNode(0);
//    JumpNode* b = new JumpNode(1);
//    JumpNode* c = new JumpNode(2);
//    JumpNode* d = new JumpNode(3);
//    a->next = b; b->next = c; c->next = d;
//    a->jump = c; b->jump = d; c->jump = b; d->jump = d;
//    
//    AssignOrderIterative(a);
//    a->PrintListNode();
//}



/////////////////////////////////////////////////////////////////////
// Views of the sunset
// buildings have window facing west, taller or equal buildings on the east
// can block the view from buidlings on the west.
// inputs are heights given from east to west order
// find the buildings that have view on sunset
/////////////////////////////////////////////////////////////////////


stack<int> buildingsWithSunsetView(vector<int>& buildings){
    stack<int> myStack;
    for (int i=0; i<buildings.size(); i++) {
        while (!myStack.empty() && buildings[myStack.top()] < buildings[i]) {
            myStack.pop();
        }
        myStack.push(i);
    }
    return myStack;
}

//int main(){
//    vector<int> input = {7,3,5,6,4,2,3,1};
//    stack<int> res = buildingsWithSunsetView(input);
//    printStack(res);
//}



/////////////////////////////////////////////////////////////////////
// Sorting a stack
// sort the stack in DESCENDING order
/////////////////////////////////////////////////////////////////////

// sort stack in DESCENDIN order
void sortStack(stack<int>& myStack){
    stack<int> sortedStack;
    while (!myStack.empty()) {
        int ele = myStack.top();
        myStack.pop();
        while (!sortedStack.empty() && ele < sortedStack.top()) {
            myStack.push(sortedStack.top());
            sortedStack.pop();
        }
        sortedStack.push(ele);
    }
    myStack = sortedStack;
}

//int main(){
//    stack<int> s;
//    populateStack(s, {1,7,4,5,5,2,7,5,0,9,7,6,3,2,8,6});
//    sortStack(s);
//    printStack(s);
//}




/////////////////////////////////////////////////////////////////////
// Normalize/Simplify path names
/////////////////////////////////////////////////////////////////////


void tokenizePath(string path, vector<string>& arr){
    if (path.back() != '/') {
        path += '/';
    }
    size_t prevFound = 0;
    size_t found = 0;
    
    while ((found = path.find("/", prevFound)) != string::npos) {
        string token = path.substr(prevFound, found-prevFound);
        if (token != "") {
            arr.push_back(token);
        }
        prevFound = found+1;
    }
}

string normalizePath(string path){
    vector<string> pathArr;
    stack<string> pathStack;
    string normalizedPath = "";
    
    tokenizePath(path, pathArr);
    
    for (int i=0; i<pathArr.size(); i++) {
        if (pathArr[i] == "..") {
            pathStack.pop();
        }else if(pathArr[i] == "."){
            continue;
        }else{
            pathStack.push(pathArr[i]);
        }
    }
    while (!pathStack.empty()) {
        normalizedPath = "/"+pathStack.top()+normalizedPath;
        pathStack.pop();
    }
    return normalizedPath;
}


//int main(){
//    assert(normalizePath("/Home/Baixiao/../Downloads/././helloworld.cpp") == "/Home/Downloads/helloworld.cpp");
//    assert(normalizePath("/Home/Baixiao/Desktop/Coding/") == "/Home/Baixiao/Desktop/Coding");
//}

