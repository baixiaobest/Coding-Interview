//
//  LinkedList.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 5/23/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include "DataStructures.h"
#include <iostream>
#include <assert.h>

using namespace std;

/////////////////////////////////////////////////////////////////////
// merge two linked list
/////////////////////////////////////////////////////////////////////

SLLNode* mergeTwoLinkedLists(SLLNode* L, SLLNode* R){
    if (!L) return R;
    if (!R) return L;
    
    SLLNode* M = nullptr;
    SLLNode* MTail = nullptr;
    
    while (L && R) {
        // select the smallest node from two linked list
        SLLNode* newNode = nullptr;
        if(L->data > R->data){
            newNode = R;
            R = R->next;
        }else{
            newNode = L;
            L = L->next;
        }
        
        // append new node to new linked list
        if (!M) {
            M = newNode;
            MTail = newNode;
        }else{
            MTail->next = newNode;
            MTail = MTail->next;
        }
    }
    if (L) {
        MTail->next = L;
    }
    if (R) {
        MTail->next = R;
    }
    
    return M;
}


//int main(){
//    SLLNode* L = new SLLNode(1);
//    L->Emplace(3)->Emplace(5)->Emplace(7)->Emplace(9);
//    
//    SLLNode* R = new SLLNode(2);
//    R->Emplace(4)->Emplace(6);
//    
//    SLLNode* M = mergeTwoLinkedLists(L, R);
//    M->PrintListNode();
//}



/////////////////////////////////////////////////////////////////////
// Check cyclicity of linked list
// find the start of a cycle in linked list
/////////////////////////////////////////////////////////////////////

// use two pointers, slow and fast
// fast jump two nodes while slow jump one node at a time
// if fast pointer and slow pointer meet up, then there is a cycle, otherwise, fast will reach the end
// the size of cycle can be calculated by incrementing slow pointer until they meet up again
// then reset the slow pointer to head and offset fast pointer ahead of slow pointer by cycle size
// both pointers start increment one until they meet up, then they are pointing at the start of the cycle
SLLNode* findCycle(SLLNode* head){
    if (!head) {
        return head;
    }
    
    SLLNode* slow = head;
    SLLNode* fast = head->next;
    int cycleSize = 0;
    
    while (fast && fast->next && fast != slow) {
        // increment fast pointer by two
        fast = fast->next->next;
        // increment slow pointer by one
        slow = slow->next;
    }
    if (fast != slow) {
        return nullptr;
    }
    
    // calculate cycle length
    do{
        slow = slow->next;
        cycleSize++;
    }while(slow != fast);
    
    slow = head;
    fast = head;
    
    // offset the fast pointer by cycle size
    while (cycleSize > 0) {
        fast = fast->next;
        cycleSize--;
    }
    // increment both pointers at the same speed
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return fast;
}

//int main(){
//    SLLNode* a = new SLLNode(1);
//    
//    assert(findCycle(nullptr) == nullptr);
//    assert(findCycle(a) == nullptr);
//    
//    SLLNode* cycleStart = a->Emplace(2)->Emplace(3)->Emplace(4);
//    cycleStart->next = cycleStart;
//    
//    assert(findCycle(a)->data == 4);
//    
//    cycleStart->Emplace(5)->Emplace(6)->Emplace(7)->Emplace(8);
//    assert(findCycle(a) == nullptr);
//    
//    cycleStart->next = cycleStart;
//    assert(findCycle(a)->data == 4);
//}





/////////////////////////////////////////////////////////////////////
// median of linked list
/////////////////////////////////////////////////////////////////////

int medianLinkedList(SLLNode* ptr){
    SLLNode* head = ptr->next;
    SLLNode* tail = ptr;
    int prevVal = tail->data;

    // break the loop when current value is smaller than previous value
    // or when the pointer comes back to initial position
    while (head != ptr && head->data >= prevVal) {
        prevVal = head->data;
        tail = head;
        head = head->next;
    }

    SLLNode* fast = head;
    SLLNode* slow = head;
    SLLNode* prevPtr = head;
    
    // increment fast pointer two steps and slow pointer one step
    // if faster pointer stops at tail, then size is odd, then slow pointer value is median
    // if faster pointer stops at head, then size is even, then slow pointer value is average of prevPtr and slow pointer
    do{
        fast = fast->next->next;
        prevPtr = slow;
        slow = slow->next;
    }while(fast != tail && fast!= head);
        
    return fast == tail ? slow->data : (slow->data + prevPtr->data) / 2;
}

//int main(){
//    SLLNode* a = new SLLNode(1);
//    a->next = a;
//    
//    assert(medianLinkedList(a) == 1);
//    
//    a->Emplace(3)->next = a;
//    assert(medianLinkedList(a) == 2);
//    
//    a->next->Emplace(4)->next = a;
//    assert(medianLinkedList(a) == 3);
//    
//    a->next->next->Emplace(8)->next = a;
//    assert(medianLinkedList(a) == 3);
//    
//    SLLNode* b = new SLLNode(2);
//    b->Emplace(2)->Emplace(2)->Emplace(2)->next = b;
//    assert(medianLinkedList(b) == 2);
//}







