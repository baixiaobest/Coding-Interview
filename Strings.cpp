//
//  Strings.cpp
//  ElementsOfProgrammingInterviews
//
//  Created by Baixiao Huang on 5/21/17.
//  Copyright (c) 2017 Baixiao Huang. All rights reserved.
//

#include <iostream>
#include <string>
#include <assert.h>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>


using namespace std;

/////////////////////////////////////////////////////////////////////
// Run Length Encoding
// compress string aaabcc to 3a1b2c format
/////////////////////////////////////////////////////////////////////

// runlength encoding in place
void runLengthEncoding(string& str){
    int expandSize = 0; // expand in size after input string is encoded
    int encodedPtr;     // on the right of this pointer is the encoded string to be returned
    int scanPtr;        // this pointer points to the character to be scanned

    // first, calculate the shrink to determine if the string will be resized
    for (int i=0; i<str.size();) {
        char c = str[i];
        int count = 0;
        while (i<str.size() && str[i] == c) {
            count++;
            i++;
        }
        expandSize += count == 1 ? 1 : 0;
    }

    scanPtr = (int) str.size() - 1;
    // encoded string is larger than original string, resize it
    if (expandSize > 0) {
        str.resize(str.size() + expandSize);
    }
    encodedPtr = (int) str.size()-1;

    // start the encoding from the end of the original string
    while (scanPtr >= 0) {
        char c = str[scanPtr];
        int count = 0;
        while (scanPtr >= 0 && str[scanPtr] == c) {
            count++;
            scanPtr--;
        }
        str[encodedPtr--] = c;
        str[encodedPtr--] = count + '0';
    }
    str = str.substr(encodedPtr+1, str.size()-encodedPtr-1);
}


// run length encoding without in place
string encode(string str){
    string resStr="";
    int count = 1;

    for (int i=1; i<=str.size(); i++) {
        if(i<str.size() && str[i] == str[i-1]){
            count++;
        }else{
        	resStr += count + '0';
            resStr += str[i-1];
            count = 1;
        }
    }

    return resStr;
}

// run length decode without in place
string decode(string str){
	string resStr="";
    int count=1;
    for (int i=0; i<str.size(); i++) {
        if (isdigit(str[i])) {
            count = str[i] - '0';
        }else{
            resStr.append(count, str[i]);
        }
    }
    return resStr;
}


//int main(){
//	string a = "abcde";
//    string b = "aabbcc";
//    string c = "aaaaabcde";
//    string d = "aaaabbbbbccccccddd";
//    string e = "abcdeeeeeee";
//    string f = "";
//
//    runLengthEncoding(a);
//    assert(a == "1a1b1c1d1e");
//
//    runLengthEncoding(b);
//    assert(b == "2a2b2c");
//
//    runLengthEncoding(c);
//    assert(c == "5a1b1c1d1e");
//
//    runLengthEncoding(d);
//    assert(d == "4a5b6c3d");
//
//    runLengthEncoding(e);
//    assert(e == "1a1b1c1d7e");
//
//    runLengthEncoding(f);
//    assert(f == "");
//
//    assert(decode(encode("abcde")) == "abcde");
//    assert(decode(encode("aabbcc")) == "aabbcc");
//    assert(decode(encode("aaaaabcde")) == "aaaaabcde");
//    assert(decode(encode("aaaabbbbbccccccddd")) == "aaaabbbbbccccccddd");
//    assert(decode(encode("abcdeeeeeee")) == "abcdeeeeeee");
//    assert(decode(encode("")) == "");
//}


/////////////////////////////////////////////////////////////////////
// Reverse words in sentence
/////////////////////////////////////////////////////////////////////


void reverseWordsInSentence(string& sentence){
    for (int i=0; i<sentence.size(); i++) {
        if (sentence[i] != ' ') {
            int end = i;
            while (end < sentence.size() && sentence[end] != ' ') {
                end++;
            }
            reverse(sentence.begin()+i, sentence.begin()+end);
            i = end;
        }
    }
    reverse(sentence.begin(), sentence.end());
}

void reverseWordsInSentence2(string& sentence){
    int start = 0;
    int end = 0;
    while ((end = sentence.find(sentence, start)) != string::npos) {
        reverse(sentence.begin()+start, sentence.begin()+end+1);
        start = end+1;
    }
    reverse(sentence.begin(), sentence.end());
}

//int main(){
//    string str = "This is a test";
//    reverseWordsInSentence(str);
//    cout << str << endl;
//}


/////////////////////////////////////////////////////////////////////
// Find first occurance of a string in a text
/////////////////////////////////////////////////////////////////////

// use a sliding window with size of search string, hash the frequencies of
// characters in query string and the frequencies of characters in sliding window.
// if the frequencies of the characters in the sliding window match those of the query string,
// then we compare the actual contents of the sliding window and query string to confirm the match
int matchString(string searchStr, string text){
    int numUniqueChar = 0;
    int windowSize = searchStr.size();
    int left(0), right(0);
    unordered_map<char, int> mapCharFrequency;

    for (int i=0; i<searchStr.size(); i++) {
        auto it = mapCharFrequency.find(searchStr[i]);
        if (it == mapCharFrequency.end()) {
            mapCharFrequency[searchStr[i]] = 1;
        }else{
            mapCharFrequency[searchStr[i]] += 1;
        }
    }
    numUniqueChar = (int)mapCharFrequency.size();

    while (right < text.size()) {
        char c = text[right];

        // expand the right boundary, and decrement the frequency of the character in the hash
        auto it = mapCharFrequency.find(c);
        if(it != mapCharFrequency.end()){
            mapCharFrequency[c] -= 1;
            if (mapCharFrequency[c] == 0) {
                numUniqueChar--;
            }
        }
        right++;

        // if the window is too big, shrink the window by incrementing left boundary
        // update the frequency of the deleted character as well
        if (right - left > windowSize) {
            char charToBeDelete = text[left];
            auto ptr = mapCharFrequency.find(charToBeDelete);
            if (ptr != mapCharFrequency.end()) {
                if(mapCharFrequency[charToBeDelete] == 0)
                    numUniqueChar++;
                mapCharFrequency[charToBeDelete] += 1;
            }
            left++;
        }

        // if all characters frequencies are match, we compare the string
        if (numUniqueChar == 0 && text.compare(left, right-left, searchStr) == 0) {
            return left;
        }
    }

    return -1;
}



// instead of computing the frequencies in the sliding window, we can compute the hash
// in the sliding window. But the hash calculation should have low probability of collision
// and the hashing should be a rolling hash. A rolling hash of a sliding window can be computed
// from the hash of a previous sliding window in O(1) time.
// The sliding window that interate through the input text generate a hash and compared with that
// of the query string. If the two hashes match, then the contents of the sliding window is compared.
// So that the total time complecity is O(n+m) where n, m are sizes of input text and input query.
int matchString2(string searchStr, string text){
    if (searchStr.size() > text.size()) {
        return -1;
    }

    int hashSearch = 0;
    int hashText = 0;
    int left = 0;
    int right = searchStr.size();
    int base = 100;
    int mod = 1000;

    // calculate the hash for search string and hash for initial window
    for (int i=0; i<searchStr.size(); i++) {
        hashSearch = (hashSearch*base + searchStr[i]) % mod;
        hashText = (hashText*base + text[i]) % mod;
    }

    while (right < text.size()) {
        // if the hash match, compare the string inside the sliding window and the search string
        if (hashSearch == hashText && text.compare(left, right-left, searchStr)==0) {
            return left;
        }

        // update the rolling hash by inserting new character and removing old character
        hashText = (hashText*base + text[right]) % mod;
        hashText -= text[left]*(int)pow(base, right-left-1) % mod;
        hashText = hashText < 0 ? hashText + mod : hashText;

        // update the window pointers
        right++;
        left++;
    }
    // final check
    if (hashSearch == hashText && text.compare(left, right-left, searchStr)==0) {
        return left;
    }

    return -1;
}


//int main(){
//    cout << matchString2("test", "tsettest");
//}


/////////////////////////////////////////////////////////////////////
// Replace and Remove
// replace 'a' with 'dd' and remove 'b' from string
// do it in place
/////////////////////////////////////////////////////////////////////

void replaceAndRemove(string& str){
    int expandSize = 0;
    int scanPtr = str.size()-1;
    int resPtr;

    for (int i=0; i<str.size(); i++) {
        if (str[i] == 'a') {
            expandSize++;
        }
    }

	str.resize(str.size()+expandSize);
    resPtr = str.size()-1;

    while (scanPtr >= 0) {
        if (str[scanPtr] == 'a') {
            str[resPtr--] = 'd';
            str[resPtr--] = 'd';

        }else if(str[scanPtr] != 'b'){
            str[resPtr--] = str[scanPtr];
        }

        scanPtr--;
    }
    resPtr++;

    // this will copy character from string
    str = str.substr(resPtr, str.size() - resPtr);

}

//int main(){
//	string a = "abcde";
//    string b = "aaabbbbbbbbbbcde";
//    string c = "a";
//    string e = "b";
//    string f = "";
//
//    replaceAndRemove(a);
//    assert(a=="ddcde");
//
//    replaceAndRemove(b);
//    assert(b=="ddddddcde");
//
//    replaceAndRemove(c);
//    assert(c=="dd");
//
//    replaceAndRemove(e);
//    assert(e=="");
//
//    replaceAndRemove(f);
//    assert(f=="");
//}



/////////////////////////////////////////////////////////////////////
// Phone number mnemonic
/////////////////////////////////////////////////////////////////////

vector<string> number2chars = {"0","1","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};

void phoneNumberMnemonicHelper(string& phoneNumber, int idx, string& currStr){
    if (idx >= phoneNumber.size()) {
        cout << currStr << endl;
        return;
    }

    string charSet = number2chars[phoneNumber[idx]-'0'];
    for (int i=0; i<charSet.size(); i++) {
        currStr.push_back(charSet[i]);
        phoneNumberMnemonicHelper(phoneNumber, idx+1, currStr);
        currStr.pop_back();
    }
}

void phoneNumberMnemonic(string phoneNumber){
    string currString = "";
    phoneNumberMnemonicHelper(phoneNumber, 0, currString);
}

//int main(){
//    phoneNumberMnemonic("1234");
//}











