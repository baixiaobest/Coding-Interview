//
//  Header.h
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 4/30/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>

/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////

// doubly linked tree node
struct DLTreeNode{
    int data;
    DLTreeNode* left;
    DLTreeNode* right;
    DLTreeNode* parent;
    DLTreeNode(int myData){
        data = myData;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    void leftAttach(DLTreeNode* leftNode){
        if(left != nullptr)
            left->parent = nullptr;
        left = leftNode;
        leftNode->parent = this;
    }
    
    void rightAttach(DLTreeNode* rightNode){
        if(right != nullptr)
            right->parent = nullptr;
        right = rightNode;
        rightNode->parent = this;
    }
};

void inorderPrint(TreeNode* root){
    if (root==nullptr) {
        return;
    }
    inorderPrint(root->left);
    std::cout << root->data << " ";
    inorderPrint(root->right);
}

void preorderPrint(TreeNode* root){
    if (root==nullptr) {
        return;
    }
    std::cout << root->data << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}

void postorderPrint(TreeNode* root){
    if (root==nullptr) {
        return;
    }
    postorderPrint(root->left);
    postorderPrint(root->right);
    std::cout << root->data << " ";
}


/////////////////////////////////////////////////////////////////////

struct SLLNode{
    int data;
    SLLNode* next;
    
    SLLNode(int val){
        data = val;
        next = nullptr;
    }
    
    SLLNode* Emplace(int val){
        next = new SLLNode(val);
        return next;
    }
    
    void PrintListNode(){
        SLLNode* ptr = this;
        while(ptr){
            std::cout << ptr->data << " ";
            ptr = ptr->next;
        }
    }
};


#endif






