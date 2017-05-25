//
//  BinarySearchTree.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 4/30/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include "DataStructures.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

using namespace std;

/////////////////////////////////////////////////////////////////////
//Function that check if a given tree is BST
/////////////////////////////////////////////////////////////////////

bool isBSTHelper(TreeNode* root, int lower, int upper){
    if (root == nullptr) {
        return true;
    }
    
    if (root->data < lower || root->data > upper) {
        return false;
    }else{
        return isBSTHelper(root->left, lower, root->data-1) && isBSTHelper(root->right, root->data+1, upper);
    }
}

bool isBST(TreeNode* root){
    return isBSTHelper(root, INT_MIN, INT_MAX);
}

/////////////////////////////////////////////////////////////////////
//Insert and delete node from BST
/////////////////////////////////////////////////////////////////////

TreeNode* insertNode(TreeNode* root, int num){
    if (!root) {
        return new TreeNode(num);
    }
    
    if (num < root->data) {
        root->left = insertNode(root->left, num);
    }else if(num > root->data){
        root->right = insertNode(root->right, num);
    }
    return root;
}

TreeNode* getMaxNode(TreeNode* root){
    if (root == nullptr) {
        return root;
    }
    
    while (root->right) {
        root = root->right;
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int num){
    if (!root) {
        return root;
    }
    
    // node on left subtree
    if (num < root->data) {
        root->left = deleteNode(root->left, num);
        
    // node on right subtree
    }else if(num > root->data){
        root->right = deleteNode(root->right, num);
        
    // delete current node
    }else{
        // current node has no child
        if (!root->left && !root->right) {
            delete root;
            root = nullptr;
        // current node has one child
        }else if((root->left && !root->right) || (!root->left && root->right)){
            TreeNode* child = root->left ? root->left : root->right;
            delete root;
            root = child;
        // two children
        }else{
            TreeNode* maxNode = getMaxNode(root->left);
            root->data = maxNode->data;
            root->left = deleteNode(root->left, maxNode->data);
        }
    }
    return root;
}


//int main(){
//    TreeNode* root = insertNode(nullptr, 4);
//    insertNode(root, 1);
//    insertNode(root, 3);
//    insertNode(root, 2);
//    insertNode(root, 5);
//    insertNode(root, 8);
//    insertNode(root, 6);
//    insertNode(root, 7);
//    insertNode(root, 9);
//    inorderPrint(root);  // print 1 2 3 4 5 6 7 8
//    cout << endl;
//    
//    root = deleteNode(root, 1);
//    root = deleteNode(root, 1);
//    root = deleteNode(root, 5);
//    root = deleteNode(root, 3);
//    root = deleteNode(root, 8);
//    inorderPrint(root); // print 2 4 6 7 9
//    cout << endl;
//	
//    root = deleteNode(root, 4);
//    inorderPrint(root); // print 2 6 7 9
//    cout << endl;
//    
//    root = deleteNode(root, 7);
//    inorderPrint(root); // print 2 6 9
//    cout << endl;
//    
//    root = deleteNode(root, 2);
//    root = deleteNode(root, 9);
//    inorderPrint(root); // print 6
//    cout << endl;
//}



/////////////////////////////////////////////////////////////////////
//given min first binary search tree, find k in the tree
/////////////////////////////////////////////////////////////////////

TreeNode* findMinFirstBST(TreeNode* root, int k){
    if (root == nullptr) {
        return root;
    }
    
    while (root) {
        // key is found
        if (root->data == k) {
            break;
            
        // key is less than minimum of the tree, so key not found
        }else if(k < root->data){
            root = nullptr;
            
        // key is possible in the tree
        }else{
            // node has two children, going to left or right depends on value of children
            if (root->left && root->right) {
                root = k >= root->right->data ? root->right : root->left;
            // node has one or no child
            }else{
                root = root->left ? root->left : root->right;
            }
        }
    }
    return root;
}

bool MFBSTExists(TreeNode* root, int k){
    return findMinFirstBST(root, k) != nullptr;
}

//int main(){
//    TreeNode a = TreeNode(2);
//    TreeNode b = TreeNode(3);
//    TreeNode c = TreeNode(5);
//    TreeNode d = TreeNode(7);
//    TreeNode e = TreeNode(11);
//    TreeNode f = TreeNode(13);
//    TreeNode g = TreeNode(17);
//    TreeNode h = TreeNode(19);
//    TreeNode i = TreeNode(23);
//    a.leftAttach(&b);
//    b.rightAttach(&c);
//    c.leftAttach(&d);
//    c.rightAttach(&e);
//    a.rightAttach(&f);
//    f.leftAttach(&g);
//    f.rightAttach(&h);
//    h.leftAttach(&i);
//    
//    assert(MFBSTExists(&a, 2));
//    assert(MFBSTExists(&a, 11));
//    assert(MFBSTExists(&a, 7));
//    assert(MFBSTExists(&a, 5));
//    assert(MFBSTExists(&a, 23));
//    assert(MFBSTExists(&a, 19));
//    assert(MFBSTExists(&a, 17));
//    assert(MFBSTExists(&a, 13));
//    assert(!MFBSTExists(&a, 1));
//    assert(!MFBSTExists(&a, 4));
//    assert(!MFBSTExists(&a, 12));
//    assert(!MFBSTExists(&a, 30));
//}



/////////////////////////////////////////////////////////////////////
//Build a balanced BST from sorted singly linked list
/////////////////////////////////////////////////////////////////////

TreeNode* BuildBSTFromSLLHelper(int n){
    if (n <= 0) {
        return  nullptr;
    }
    TreeNode* root = new TreeNode(0);
    
    int mid = n/2;
    root->left = BuildBSTFromSLLHelper(mid);
    root->right = BuildBSTFromSLLHelper(n-mid-1);
    return root;
}

void PopulateInorder(TreeNode* root, SLLNode*& head){
    if (!head || !root) {
        return;
    }
    
    PopulateInorder(root->left, head);
    root->data = head->data;
    head = head->next;
    PopulateInorder(root->right, head);

}


TreeNode* BuildBSTFromSLL(SLLNode* head){
    int count = 0;
    SLLNode* ptr = head;
    
    if (head == nullptr) {
        return nullptr;
    }
    
    while (ptr) {
        count++;
        ptr = ptr->next;
    }
    
    TreeNode* tree = BuildBSTFromSLLHelper(count);
    
    ptr = head;
    PopulateInorder(tree, ptr);
    return tree;
}

//int main(){
//    SLLNode* linkedList = new SLLNode(1);
//    linkedList->Emplace(2)->Emplace(3)->Emplace(4)->Emplace(5)->Emplace(6)->Emplace(7)->Emplace(8)->Emplace(9);
//    TreeNode* tree = BuildBSTFromSLL(linkedList);
//    inorderPrint(tree);
//}


/////////////////////////////////////////////////////////////////////
//Convert a binary search tree into a doubly linked list without additional memory
/////////////////////////////////////////////////////////////////////


TreeNode* Tree2ListHelper(TreeNode* root){
    if (!root) {
        return root;
    }
    
    TreeNode* LTail = nullptr;
    
    TreeNode* LHead = Tree2ListHelper(root->left);
    TreeNode* RHead = Tree2ListHelper(root->right);
    if (LHead) {
        // append root to last element of left list
        LTail = LHead->left;
        LTail->right = root;
        root->left = LTail;
        
        LTail = root;
        LHead->left = root;
        LTail->right = LHead;
    }else{
        // root itself is a list
        LHead = root;
        LTail = root;
        root->left = root;
        root->right = root;
    }
    
    if (RHead) {
        TreeNode* RTail = RHead->left;
        LTail->right = RHead;
        RHead->left = LTail;
        
        LHead->left = RTail;
        RTail->right = LHead;
    }
    
    return LHead;
}

TreeNode* Tree2List(TreeNode* root){
    TreeNode* list = Tree2ListHelper(root);
    if (list) {
        list->left->right = nullptr;
        list->left = nullptr;
    }
    return list;
}


//int main(){
//    TreeNode a = TreeNode(7);
//    TreeNode b = TreeNode(3);
//    TreeNode c = TreeNode(11);
//    TreeNode d = TreeNode(2);
//    TreeNode e = TreeNode(5);
//    
//    a.rightAttach(&c);
//    a.leftAttach(&b);
//    b.leftAttach(&d);
//    b.rightAttach(&e);
//    
//    TreeNode* list = Tree2List(&a);
//    while (!list) {
//        cout << list->data << " ";
//    }
//}

/////////////////////////////////////////////////////////////////////
//Rebuild Binary Search Tree from preorder traversal
/////////////////////////////////////////////////////////////////////

TreeNode* rebuildBSTHelper(vector<int>& preorder, int start, int end){
    if (start >= end) {
        return nullptr;
    }
    
    TreeNode* newNode = new TreeNode(preorder[start]);
    int divider = start+1;
    while (preorder[divider] < preorder[start]) {
        divider++;
    }
    
    newNode->left = rebuildBSTHelper(preorder, start+1, divider);
    newNode->right = rebuildBSTHelper(preorder, divider, end);
    
    return newNode;
}

TreeNode* rebildBSTFromPreorder(vector<int>& preorder){
    return rebuildBSTHelper(preorder, 0, preorder.size());
}

//int main(){
//    vector<int> preorder = {11,5,3,2,7,17,13,23,19};
//    
//    TreeNode* rebuiltTree = rebildBSTFromPreorder(preorder);
//    preorderPrint(rebuiltTree);
//    cout << endl;
//    inorderPrint(rebuiltTree);
//    
//}



/////////////////////////////////////////////////////////////////////
//find lowest common ancestor in binary search tree
/////////////////////////////////////////////////////////////////////

TreeNode* LCABST(TreeNode* root, int a, int b){
    // always a <= b
    if(a > b)
        swap(a, b);
    
    while (root) {
        //LCA on left subtree
        if (b < root->data) {
            root = root->left;
            
        //LCA on right subtree
        }else if(a > root->data){
            root = root->right;
            
        //root is the LCA
        }else{
            break;
        }
    }
    return root;
}

//int main(){
//    vector<int> preorder = {11,5,3,2,7,17,13,23,19};
//    TreeNode* tree = rebildBSTFromPreorder(preorder);
//    assert(LCABST(tree, 2, 7)->data == 5);
//    assert(LCABST(tree, 7, 7)->data == 7);
//	assert(LCABST(tree, 5, 2)->data == 5);
//    assert(LCABST(tree, 13, 19)->data == 17);
//    assert(LCABST(tree, 19, 2)->data == 11);
//}






