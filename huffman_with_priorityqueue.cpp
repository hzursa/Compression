#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std; 

const int MAXSIZE = 1000;
const int  ASCII = 256; //

vector<int> vectorA;
int frequency [ASCII];
string huffmancode [ASCII];

struct HeapNode { 
  
    // ASCII code of the character
    int data; 
  
    // Frequency of the character 
    unsigned freq; 
  
    // Define left and right child 
    HeapNode *left, *right; 
  
    HeapNode(int data, unsigned freq) { 
  
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 

// Comparison function for priority queue
struct compare { 
  
    bool operator()(HeapNode* l, HeapNode* r) 
  
    { 
        return (l->freq > r->freq); 
    } 
}; 
// Save huffman codes to an array from 
// the root of Huffman Tree. 


void saveCodes(struct HeapNode* root, string str){
    if (!root) 
        return; 
  
    if (root->data != -999) {
        cout << root->data << ": " << str << "\n"; 
        huffmancode[root->data+128] = str;
    }
    saveCodes(root->left, str + "0"); 
    saveCodes(root->right, str + "1"); 
    
}

void HuffmanCodes(int freq[]) 
{ 
    struct HeapNode *left, *right, *top; 
  
    // Create a min heap & inserts all characters of data[] 
    priority_queue<HeapNode*, vector<HeapNode*>, compare> pq; 
  
    for (int i = 0; i < ASCII; ++i) {
        if(freq[i]>0)
        pq.push(new HeapNode(i-128, freq[i])); 
        }
  
  
    while (pq.size() != 1) { 
  

        left = pq.top(); 
        pq.pop(); 
  
        right = pq.top(); 
        pq.pop(); 
  

        top = new HeapNode(-999, left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        pq.push(top); 
    } 
    saveCodes(pq.top(), ""); 
}


int main()
 {
   char ch;
   ifstream fin("in.txt", ios::binary);
   ofstream fout("out.txt");
   while (fin.read(&ch, sizeof(ch))) {
	   //std::cout << int(ch) << std::endl;
       frequency[int(ch)+128]+=1;
   }
    fin.close();
    HuffmanCodes(frequency); 
    ifstream fin2("in.txt", ios::binary);
    while (fin2.read(&ch, sizeof(ch))) {
        fout<<huffmancode[int(ch)+128];
   }
   fin2.close();
   fout.close();

   return 0;
 }