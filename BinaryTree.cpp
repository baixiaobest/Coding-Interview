//
//  main.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 4/29/17.
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
//Function that takes in a binary tree and return true or false whether it is balanced
//use O(h) additional storage, where h is the height of the tree
/////////////////////////////////////////////////////////////////////

// return height of the tree
// return 0 if root is null
// return -1 if the tree is unbalanced
int TreeHeight(TreeNode* root){
    if(root == nullptr){
        return 0;
    }
    
    int leftHeight = TreeHeight(root->left);
    if(leftHeight == -1) return -1;
    
    int rightHeight = TreeHeight(root->right);
    if(rightHeight == -1) return -1;
    
    if(abs(leftHeight - rightHeight) > 1) return -1;
    
    return max(leftHeight, rightHeight) + 1;
}


bool isBalanced(TreeNode* root){
    return TreeHeight(root) != -1;
}



//int main(){
//    TreeNode a = TreeNode(1);
//    TreeNode b = TreeNode(2);
//    TreeNode c = TreeNode(3);
//    TreeNode d = TreeNode(4);
//    TreeNode e = TreeNode(5);
//    a.left = &b;
//    a.right = &c;
//    cout << isBalanced(&a) << endl;
//    c.left = &d;
//    cout << isBalanced(&a) << endl;
//    d.right = &e;
//    cout << isBalanced(&a) << endl;
//}




/////////////////////////////////////////////////////////////////////
//find a node in the tree that is not k-balanced
//the node has both left subtree and right subtree k-balanced but the node is not
/////////////////////////////////////////////////////////////////////


// pass number of node in tree using postorder traversal
// return the node that is not k-balanced
TreeNode* countNumNode(TreeNode* root, int& num, int k){
    int leftNumNode = 0;
    int rightNumNode = 0;
    if(root == nullptr){
        num = 0;
        return root;
    }
    
    TreeNode* leftUnbalancedNode = countNumNode(root->left, leftNumNode, k);
    // early return if the left subtree is not k balanced
    if(leftUnbalancedNode != nullptr)
        return leftUnbalancedNode;
    
    TreeNode* rightUnbalancedNode = countNumNode(root->right, rightNumNode, k);
    // early return if the right subtree is not k balanced
    if(rightUnbalancedNode != nullptr)
        return rightUnbalancedNode;
    
    // current node is not k balanced
    if (abs(leftNumNode - rightNumNode) > k) {
        return root;
    }
    
    // current node is k balanced
    num = leftNumNode + rightNumNode + 1;
    return nullptr;
}

TreeNode* FindKUnbalanced(TreeNode* root, int k){
    int num=0;
    return countNumNode(root, num, k);
}

//int main(){
//    TreeNode a = TreeNode(1);
//    TreeNode b = TreeNode(2);
//    TreeNode c = TreeNode(3);
//    TreeNode d = TreeNode(4);
//    TreeNode e = TreeNode(5);
//    TreeNode f = TreeNode(6);
//    TreeNode g = TreeNode(7);
//    TreeNode h = TreeNode(8);
//    
//    a.left = &b;
//    a.right = &c;
//    c.left = &d;
//    c.right = &e;
//    e.left = &f;
//    e.right = &g;
//    g.right = &h;
//    assert(FindKUnbalanced(&a, 1)->data == 3);
//    assert(FindKUnbalanced(&a, 2)->data == 3);
//    assert(FindKUnbalanced(&a, 3)->data == 1);
//    assert(FindKUnbalanced(&a, 10) == nullptr);
//}




/////////////////////////////////////////////////////////////////////
// find if the given tree is symmetric
/////////////////////////////////////////////////////////////////////

bool isSymTree(TreeNode* leftPtr, TreeNode* rightPtr){
    
    // both reach leaf node
    if (leftPtr == nullptr && rightPtr == nullptr) {
        return true;
    }
    
    // no matching node in left subtree or right subtree
    if((leftPtr && !rightPtr) || (!leftPtr && rightPtr))
        return false;

    return leftPtr->data == rightPtr->data
        && isSymTree(leftPtr->left, rightPtr->right)
        && isSymTree(leftPtr->right, rightPtr->left);
}

bool isSymetric(TreeNode* root){
    return isSymTree(root, root);
}

//int main(){
//    TreeNode a = TreeNode(1);
//    TreeNode b = TreeNode(2);
//    TreeNode c = TreeNode(2);
//    TreeNode d = TreeNode(3);
//    TreeNode e = TreeNode(3);
//    TreeNode f = TreeNode(4);
//    
//    a.left = &b;
//    a.right = &c;
//    b.right = &d;
//    c.left = &e;
//    assert(isSymetric(&a));
//    b.data = 1;
//    assert(isSymetric(&a) == false);
//    b.data = 2;
//    c.left = nullptr;
//    c.right	= &e;
//    assert(isSymetric(&a) == false);
//    c.right = nullptr;
//    c.left = &e;
//    e.left = &f;
//    assert(isSymetric(&a) == false);
//}


/////////////////////////////////////////////////////////////////////
//inorder traversal of the tree using O(1) space, node has parent pointer
/////////////////////////////////////////////////////////////////////



void InorderTraversalPrint(DLTreeNode* root){
    DLTreeNode* currPtr = root;
    DLTreeNode* prevPtr = nullptr;
    
    if(root == nullptr) return;
    
    while (currPtr != nullptr) {
        DLTreeNode* next;
        // we are traversing down the tree
        if(prevPtr == currPtr->parent || !prevPtr){
            // continue down left
            if(currPtr->left != nullptr){
                next = currPtr->left;
            }else{
                cout << currPtr->data << " ";
                // continue down right or to parent
                next = currPtr->right ? currPtr->right : currPtr->parent;
            }
            
        // back up from left subtree
        }else if(currPtr->left == prevPtr){
            cout << currPtr->data << " ";
            // continue down right or to parent
            next = currPtr->right ? currPtr->right : currPtr->parent;
            
    	// back up from right subtree
        }else{
            next = currPtr->parent;
        }
        prevPtr = currPtr;
        currPtr = next;
    }
    cout << endl;
}


//int main(){
//    DLTreeNode a = DLTreeNode(3);
//    DLTreeNode b = DLTreeNode(1);
//    DLTreeNode c = DLTreeNode(2);
//    DLTreeNode d = DLTreeNode(5);
//    DLTreeNode e = DLTreeNode(4);
//    
//    InorderTraversalPrint(&a); // print 3
//    a.leftAttach(&b);
//    InorderTraversalPrint(&a);  // print 1 3
//    b.rightAttach(&c);
//    InorderTraversalPrint(&a); // print 1 2 3
//    a.rightAttach(&d);
//    d.leftAttach(&e);
//    InorderTraversalPrint(&a);  // print 1 2 3 4 5
//}



/////////////////////////////////////////////////////////////////////
//Build binary tree from inorder and preorder or postorder
/////////////////////////////////////////////////////////////////////


TreeNode* BuildFromPreorder(vector<int>& inorder, vector<int>& preorder, int inorderSt, int inorderEnd, int& preorderIdx)
{
    if (inorderEnd-inorderSt < 1 || preorderIdx >= preorder.size()) {
        return nullptr;
    }
    
    TreeNode* newNode = new TreeNode(preorder[preorderIdx]);
    auto it = find(inorder.begin()+inorderSt, inorder.begin()+inorderEnd, preorder[preorderIdx]);
    int inorderDivider = (int)(it- inorder.begin());
    
    preorderIdx++;
    newNode->left = BuildFromPreorder(inorder, preorder, inorderSt, inorderDivider, preorderIdx);
    newNode->right = BuildFromPreorder(inorder, preorder, inorderDivider+1, inorderEnd, preorderIdx);
    
    return newNode;
}

TreeNode* BuildFromPostorder(vector<int>& inorder, vector<int>& postorder, int inorderSt, int inorderEnd, int& postorderIdx){
    if (inorderEnd-inorderSt < 1 || postorderIdx < 0) {
        return nullptr;
    }
    
    TreeNode* newNode = new TreeNode(postorder[postorderIdx]);
    auto it = find(inorder.begin()+inorderSt, inorder.begin()+inorderEnd, postorder[postorderIdx]);
    int inorderDivider = (int)(it- inorder.begin());
    
    postorderIdx--;
    newNode->right = BuildFromPostorder(inorder, postorder, inorderDivider+1, inorderEnd, postorderIdx);
    newNode->left = BuildFromPostorder(inorder, postorder, inorderSt, inorderDivider, postorderIdx);
    
    return newNode;
}

//
//int main(){
//    vector<int> inorder = {2,1,4,3,7,5,6,8};
//    vector<int> preorder = {1,2,3,4,5,7,6,8};
//    vector<int> postorder = {2,4,7,8,6,5,3,1};
//    int preorderIdx=0;
//    TreeNode* newTree = BuildFromPreorder(inorder, preorder, 0, inorder.size(), preorderIdx);
//    inorderPrint(newTree);
//    cout << endl;
//    preorderPrint(newTree);
//    cout << endl;
//    
//    int postorderIdx = postorder.size()-1;
//    TreeNode* postorderTree = BuildFromPostorder(inorder, postorder, 0, inorder.size(), postorderIdx);
//    inorderPrint(postorderTree);
//    cout << endl;
//    postorderPrint(postorderTree);
//}




/////////////////////////////////////////////////////////////////////
//lowest common ancestor with parent pointer
/////////////////////////////////////////////////////////////////////

int getDepth(DLTreeNode* root, DLTreeNode* node){
    int depth = 0;
    while (node != root) {
        node = node->parent;
        depth++;
    }
    return depth;
}

DLTreeNode* DLLCA(DLTreeNode* root, DLTreeNode* a, DLTreeNode* b){
    
    // get depth by traversing up
    int depth_a = getDepth(root, a);
    int depth_b = getDepth(root, b);
    int depth_diff = abs(depth_a - depth_b);
    if (depth_a < depth_b) {
        swap(a, b);
    }
    
    // put a and b pointer to the same level
    while (depth_diff > 0) {
        a = a->parent;
        depth_diff--;
    }
    
    // both pointers traverse up at the same time until they meet each other
    while (a!=b) {
        a = a->parent;
        b = b->parent;
    }
    return a;
}

DLTreeNode* DLLCA_hash(DLTreeNode* root, DLTreeNode* a, DLTreeNode* b){
    // keep a hash table that record traversed nodes
    unordered_set<DLTreeNode*> hash;
    
    // both pointers traverse up
    while (a || b) {
        if (a) {
            // common ancestor found
            if (hash.find(a) != hash.end()) {
                return a;
            }
            hash.insert(a);
            a = a->parent;
        }
        if (b) {
            // common ancestor found
            if (hash.find(b) != hash.end()) {
                return b;
            }
            hash.insert(b);
            b = b->parent;
        }
    }
    return nullptr;
}


//int main(){
//    DLTreeNode a = DLTreeNode(1);
//    DLTreeNode b = DLTreeNode(2);
//    DLTreeNode c = DLTreeNode(3);
//    DLTreeNode d = DLTreeNode(4);
//    DLTreeNode e = DLTreeNode(5);
//    DLTreeNode f = DLTreeNode(6);
//    
//    a.leftAttach(&b);
//    b.leftAttach(&c);
//    b.rightAttach(&d);
//    d.rightAttach(&f);
//    a.rightAttach(&e);
//    
//    assert(DLLCA(&a, &c, &d) == &b);
//    assert(DLLCA(&a, &c, &f) == &b);
//    assert(DLLCA(&a, &b, &b) == &b);
//    assert(DLLCA(&a, &f, &e) == &a);
//	assert(DLLCA(&a, &a, &b) == &a);
//    
//    assert(DLLCA_hash(&a, &c, &d) == &b);
//    assert(DLLCA_hash(&a, &c, &f) == &b);
//    assert(DLLCA_hash(&a, &b, &b) == &b);
//    assert(DLLCA_hash(&a, &f, &e) == &a);
//    assert(DLLCA_hash(&a, &a, &b) == &a);
//}


