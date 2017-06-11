//
//  PrimitiveTypes.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 5/9/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//
// total 5 problems

#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////
//calculate parity of a given value
/////////////////////////////////////////////////////////////////////

bool parity1(unsigned long x){
    short result = 0;
    while (x) {
        result ^= x & 1;
        x = x >> 1;
    }
    return result;
}

bool parity2(unsigned long x){
    short result = 0;
    while (x) {
        result ^= 1;
        x &= (x-1);
    }
    return result;
}

//int main(){
//    assert(parity1(0xf) == false);
//    assert(parity1(0x7) == true);
//    assert(parity1(0x0) == false);
//    assert(parity1(0x77777777) == false);
//    assert(parity1(0x77777773) == true);
//    
//    assert(parity2(0xf) == false);
//    assert(parity2(0x7) == true);
//    assert(parity2(0x0) == false);
//    assert(parity2(0x77777777) == false);
//    assert(parity2(0x77777773) == true);
//}



/////////////////////////////////////////////////////////////////////
// swap two bits give two positions
/////////////////////////////////////////////////////////////////////



unsigned long swapBits(unsigned long val, int i, int j){
    if (((val >> i)&1) != ((val >> j)&1)) {
        val ^= (1 << i) | (1 << j);
    }
    return val;
}

//int main(){
//    int a = 6;
//    assert(swapBits(a, 2, 0) == 3);
//    assert(swapBits(a, 2, 1) == 6);
//    assert(swapBits(a, 3, 0) == 6);
//}


/////////////////////////////////////////////////////////////////////
//reverse all the bits integer
/////////////////////////////////////////////////////////////////////

unsigned int reverseBits1(unsigned int val){
    int left (63), right(0);
    while (left > right) {
        if (((val >> left)&1) != ((val >> right)&1)) {
            val ^= (1 << left) | (1 << right);
        }
    }
    return left;
}
unsigned int reverseBits2(unsigned int val){
    unsigned int result = 0;
    for (int i=0; i<8*sizeof(val); i++) {
        result = result << 1;
        result |= val & 1;
        val = val >> 1;
    }
    return result;
}

//int main(){
//    assert(reverseBits1(0) == 0);
//    assert(reverseBits1(0x5) == 0xA0000000);
//    assert(reverseBits2(0) == 0);
//    assert(reverseBits2(0x5) == 0xA0000000);
//}


/////////////////////////////////////////////////////////////////////
//print power set
/////////////////////////////////////////////////////////////////////


void printPowerSetHelper(vector<int>& arr, int idx, vector<int>& res){
    if (idx >= arr.size()) {
        for (int i=0; i<res.size(); i++) {
            cout << res[i] << " ";
        }
        cout << endl;
        return;
    }
    
    printPowerSetHelper(arr, idx+1, res);
    res.push_back(arr[idx]);
    printPowerSetHelper(arr, idx+1, res);
    res.pop_back();
}

void printPowerSet(vector<int>& arr){
    vector<int> res;
    printPowerSetHelper(arr, 0, res);
}

//int main(){
//    vector<int> input ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//    printPowerSet(input);
//}


/////////////////////////////////////////////////////////////////////
// greatest common divisor and least common multiple
/////////////////////////////////////////////////////////////////////

int greatestCommonDivisor(int a, int b){
    return b == 0 ? a : greatestCommonDivisor(b, a%b);
}

int greatestCommonDivisor2(int a, int b){
    while (b != 0) {
        int mod = a%b;
        a = b;
        b = mod;
    }
    return a;
}

int leastCommonMultiple(int a, int b){
    return abs(a*b)/greatestCommonDivisor2(a, b);
}

//int main(){
//    cout << greatestCommonDivisor2(15, 30) << endl;
//    cout << leastCommonMultiple(2,6) << endl;
//}




