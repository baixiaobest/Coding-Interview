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



/////////////////////////////////////////////////////////////////////
// find the node where two overlapping linked list meet
/////////////////////////////////////////////////////////////////////

pair<int, SLLNode*> listLength(SLLNode* head){
    int length = 0;
    SLLNode* prev = head;

    while(head){
        length++;
        prev = head;
        head = head->next;
    }
    return pair<int, SLLNode*>(length, prev);
}


SLLNode* overlapNode(SLLNode* L, SLLNode* R){
    if(!L || !R)
        return nullptr;

    int Llength, Rlength, lengthDiff;
    pair<int, SLLNode*> left = listLength(L);
    pair<int, SLLNode*> right = listLength(R);
    Llength = left.first;
    Rlength = right.first;

    // two linked list do not ends at the same node
    // therefore they are not overlapping
    if(left.second != right.second)
        return nullptr;

    // make sure L pointer is the longer list
    if(Rlength > Llength){
        swap(L, R);
    }
    lengthDiff = abs(Llength - Rlength);

    // offset the left linked list by length difference
    for (int i=0; i<lengthDiff; i++){
        L = L->next;
    }

    // start traversing both linked list until they meet up
    while(L != R){
        L = L->next;
        R = R->next;
    }

    return L;
}

//int main(){
//    SLLNode* a = new SLLNode(1);
//    SLLNode* aTail = a->Emplace(2)->Emplace(3);
//
//    SLLNode* b = new SLLNode(4);
//    SLLNode* bTail = b->Emplace(5)->Emplace(6)->Emplace(7);
//
//    assert(overlapNode(nullptr, nullptr) == nullptr);
//    assert(overlapNode(nullptr, a) == nullptr);
//    assert(overlapNode(a,b) == nullptr);
//
//    aTail->next = bTail;
//    assert(overlapNode(a,b)->data == 7);
//
//    aTail->next = b->next;
//    assert(overlapNode(a,b)->data == 5);
//
//    aTail->next = b;
//    assert(overlapNode(a,b)->data == 4);
//}



/////////////////////////////////////////////////////////////////////
// Even Odd merge
// reorder the linked list such that the even index nodes come
// before the odd index nodes.
/////////////////////////////////////////////////////////////////////


SLLNode* evenOddMerge(SLLNode* head){
    if(!head) return head;

    SLLNode* headPtr = head;
    SLLNode* oddHead = head->next;
    SLLNode* evenPtr = nullptr;
    SLLNode* oddPtr = nullptr;

    bool even = true;

    while(headPtr){
        if(even){
            if(evenPtr)
                evenPtr->next = headPtr;
            evenPtr = headPtr;
        }else{
            if(oddPtr)
                oddPtr->next = headPtr;
            oddPtr = headPtr;
        }
        even = !even;
        headPtr = headPtr->next;
    }

    if(oddPtr)
        oddPtr->next = nullptr;

    evenPtr->next = oddHead;

    return head;
}


//int main(){
//    SLLNode* a = new SLLNode(0);
//
//    evenOddMerge(a)->PrintListNode();
//    cout << endl;
//
//    a->Emplace(1)->Emplace(2)->Emplace(3)->Emplace(4)->Emplace(5)->Emplace(6)->Emplace(7)->Emplace(8)->Emplace(9);
//    evenOddMerge(a)->PrintListNode();
//}


/////////////////////////////////////////////////////////////////////
// Delete element from singly linked list
// with O(1) time O(1) space to delete non-tail node
// O(n) time to delete tail node
/////////////////////////////////////////////////////////////////////

SLLNode* deleteNode(SLLNode* head, SLLNode* node){

    // deleting the linked list with single element
    if(!head->next && head==node){
        head = nullptr;
        delete node;

    // node is the last element
    }else if (!node->next) {
        SLLNode* ptr = head;
        while (ptr->next && ptr->next != node) {
            ptr = ptr->next;
        }
        ptr->next = nullptr;

        delete node;

    // node is in the middle of the list
    }else{
        node->data = node->next->data;
        node->next = node->next->next;
        delete node->next;
    }
    return head;
}

//int main(){
//    SLLNode* a = new SLLNode(1);
//
//    // delete list with single element
//    assert(deleteNode(a, a) == nullptr);
//
//    // delete element from the last
//    a = new SLLNode(1);
//    SLLNode* aTail = a->Emplace(2)->Emplace(3)->Emplace(4);
//    deleteNode(a, aTail)->PrintListNode();   // 1 2 3
//    cout << endl;
//
//
//    // delete element in the middle
//    SLLNode* a2 = a->next;
//    deleteNode(a, a2)->PrintListNode();  // 1 3
//    cout << endl;
//
//    // delete first element from list of size more than 1
//    deleteNode(a, a)->PrintListNode(); // 3
//}




/////////////////////////////////////////////////////////////////////
// Delete K-th last node from linked list
/////////////////////////////////////////////////////////////////////


SLLNode* deleteKthLastNode(SLLNode* head, int k){
    SLLNode* slow = head;
    SLLNode* fast = head;
    SLLNode* prev = head;

    // offset the fast pointer by K
    while (fast && k > 0) {
        fast = fast->next;
        k--;
    }
    // k is larger than size of linked list
    if (!fast) return head;

    // move fast and slow pointers at the same pace
    // record previout pointer of slow, convinient for deletion
    while (fast->next) {
        fast = fast->next;
        prev = slow;
        slow = slow->next;
    }

    // slow is pointing at head, move the head to second node
    if (slow == head) {
        head = head->next;
    }

    // delete the node pointed by slow pointer
    prev->next = slow->next;
    delete slow;

    return head;
}


//int main(){
//	SLLNode* a = new SLLNode(1);
//    assert(deleteKthLastNode(a, 0) == nullptr);
//
//    a = new SLLNode(1);
//    a->Emplace(2)->Emplace(3)->Emplace(4)->Emplace(5)->Emplace(6);
//
//    // k out of range
//    a = deleteKthLastNode(a, 6);
//    a->PrintListNode(); // 1 2 3 4 5 6
//    cout << endl;
//
//    // kth last node is the last node
//    a = deleteKthLastNode(a, 0);
//    a->PrintListNode(); // 1 2 3 4 5
//    cout << endl;
//
//    // kth last node is the first node
//    a = deleteKthLastNode(a, 4);
//    a->PrintListNode(); // 2 3 4 5
//    cout << endl;
//
//    // kth last node is the middle node
//    a = deleteKthLastNode(a, 2);
//    a->PrintListNode(); //2 4 5;
//}



/////////////////////////////////////////////////////////////////////
// reverse linked list
/////////////////////////////////////////////////////////////////////


SLLNode* reverseLinkedList(SLLNode* head){
    if(!head) return head;

    SLLNode* left = head;
    SLLNode* right = head->next;
    head->next = nullptr;

    while (right) {
        SLLNode* next = right->next;
        right->next = left;
        left = right;
        right = next;
    }

    return left;
}


//int main(){
//    SLLNode* a = new SLLNode(1);
//
//    a = reverseLinkedList(a);
//    a->PrintListNode();         // 1
//    cout << endl;
//
//    a->Emplace(2)->Emplace(3)->Emplace(4)->Emplace(5)->Emplace(6)->Emplace(7);
//    a = reverseLinkedList(a);
//    a->PrintListNode();
//}



/////////////////////////////////////////////////////////////////////
// Palindrome linked list
/////////////////////////////////////////////////////////////////////

// this function will modify original linked list
bool isPalindrome(SLLNode* head){
    if (!head) return false;

    SLLNode* slow = head;
    SLLNode* fast = head;
    SLLNode* reversedList;

    // find the middle of linked list
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    reversedList = reverseLinkedList(slow);

    while (reversedList) {
        if (head->data != reversedList->data) {
            return false;
        }
        head = head->next;
        reversedList = reversedList->next;
    }

    return true;
}


//int main(){
//    SLLNode* a = new SLLNode(1);
//
//    assert(isPalindrome(a));
//
//    a = new SLLNode(1);
//    a->Emplace(1);
//    assert(isPalindrome(a));
//
//    a = new SLLNode(1);
//    a->Emplace(2);
//    a->Emplace(1);
//    assert(isPalindrome(a));
//
//    a = new SLLNode(1);
//    a->Emplace(2)->Emplace(3)->Emplace(2)->Emplace(1);
//    assert(isPalindrome(a));
//
//    a = new SLLNode(1);
//    a->Emplace(2);
//    assert(!isPalindrome(a));
//
//    a = new SLLNode(1);
//    a->Emplace(2)->Emplace(3)->Emplace(1)->Emplace(1);
//    assert(!isPalindrome(a));
//}



/////////////////////////////////////////////////////////////////////
// Zipping a linked list
// list of 0->1->2->3->4->5->6 will be zipped into
// list of 0->6->1->5->2->4->3
/////////////////////////////////////////////////////////////////////


SLLNode* zipLinkedList(SLLNode* head){
    if (!head || !head->next) {
        return head;
    }

    SLLNode* slow = head;
    SLLNode* fast = head;
    SLLNode* curr = head;
    SLLNode* result;

    // find the mid point of linked list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    SLLNode* right = reverseLinkedList(slow);
    SLLNode* left = head->next;
    result = head;
    curr = right;

    // traverse simultaneously from left and right of the linked list
    // and add the node to new linked list
    while (curr != result) {
        result->next = curr;
        result = result->next;

        if (curr == left) {
            curr = right;
            left = left->next;
        }else{
            curr = left;
            right = right->next;
        }
    }

    return head;
}

//int main(){
//    SLLNode* a = new SLLNode(0);
//    zipLinkedList(a)->PrintListNode(); // 0
//    cout << endl;
//
//    a = new SLLNode(0);
//    a->Emplace(1);
//    zipLinkedList(a)->PrintListNode(); // 0 1
//    cout << endl;
//
//    a = new SLLNode(0);
//    a->Emplace(1)->Emplace(2);
//    zipLinkedList(a)->PrintListNode(); // 0 2 1
//    cout << endl;
//
//    a = new SLLNode(0);
//    a->Emplace(1)->Emplace(2)->Emplace(3);
//    zipLinkedList(a)->PrintListNode(); // 0 3 1 2
//    cout << endl;
//
//
//    a = new SLLNode(0);
//    a->Emplace(1)->Emplace(2)->Emplace(3)->Emplace(4)->Emplace(5)->Emplace(6)->Emplace(7);
//    zipLinkedList(a)->PrintListNode(); // 0 7 1 6 2 5 3 4
//    cout << endl;
//}



/////////////////////////////////////////////////////////////////////
// Copy Linked list with a node containing random jump pointer
/////////////////////////////////////////////////////////////////////


JumpNode* CopyLinkedList(JumpNode* head){
    if(!head)
        return head;

    JumpNode* ptr = head;
    JumpNode* newHead;

    // traverse old linked list
    // make new node and zigzag old list nodes with new list nodes
    while(ptr){
        JumpNode* newNode = new JumpNode(ptr->data);
        newNode->next = ptr->next;
        ptr->next = newNode;
        ptr = newNode->next;
    }

    // traverse new linked list
    // connect each new node jump pointer to proper node
    ptr = head;
    while(ptr){
        if(ptr->jump){
            ptr->next->jump = ptr->jump->next;
        }
        ptr = ptr->next->next;
    }
    newHead = head->next;

    // traverse both linked list
    // remove the zigzag structure and separate them into two linked lists
    ptr = head;
    while(ptr->next){
        JumpNode* temp = ptr->next;
        ptr->next = temp->next;
        ptr = temp;
    }
    return newHead;
}


int main(){
    JumpNode* a = new JumpNode(0);
    JumpNode* b = new JumpNode(1);
    JumpNode* c = new JumpNode(2);
    JumpNode* d = new JumpNode(3);
    a->next = b; b->next = c; c->next = d;
    a->jump = c; b->jump = d; c->jump = b; d->jump = d;
    a->PrintListNode();            // 0 1 2 3
    cout << endl;

    JumpNode* newA = CopyLinkedList(a);
    newA->PrintListNode();         // 0 1 2 3
    assert(newA->jump == newA->next->next);
    assert(newA->next->jump == newA->next->next->next);
    assert(newA->next->next->jump == newA->next);
    assert(newA->next->next->next == newA->next->next->next);
}




