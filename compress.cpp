#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std; 

const int MAXSIZE = 1000;
const int  ASCII = 256; //

vector<int> vectorA;
int frequency [ASCII];
string huffmancode [ASCII];
string treeCode="";

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
void saveTree(struct HeapNode* root){
    if (root->data != -999) {
        treeCode+="1"; 
        treeCode+=root->data;
        return;
    }
    treeCode+="0";
    saveTree(root->left); 
    saveTree(root->right); 
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
    saveTree(pq.top());
}


int main(int argc, char *argv[]){
    if (argc != 3) {
		cout << "please enter 2 arguments" << endl;
		return 0;
	}
    char ch;
    ifstream fin(argv[1], ios::binary);
    ofstream fout(argv[2],ios::out | ios::binary);
    while (fin.read(&ch, sizeof(ch))) {
	   //std::cout << int(ch) << std::endl;
        frequency[int(ch)+128]+=1;
    }

    fin.close();
    HuffmanCodes(frequency);
    cout<<"treetosave: "<<treeCode<<endl;
    cout<<"length of treecode: "<<treeCode.length()<<endl;
    fout << setfill('0') << setw(3) << treeCode.length(); //write the length of tree code
    fout<<treeCode; // write the tree code;
    ifstream fin2(argv[1], ios::binary);
    if (fin2) {
    // get length of file:
    fin2.seekg (0, fin2.end);
    int length = fin2.tellg();
    fin2.seekg (0, fin2.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... "<<endl;
    // read data as a block:
    fin2.read (buffer,length);
    string compressStr;
    cout<<buffer<<endl;
    for (size_t i = 0; i < length; i++)
    {
        compressStr.append(huffmancode[int(buffer[i])+128]);
    }
    delete[] buffer;

    cout<<compressStr<<endl;
    int numberofone = 8-compressStr.length()%8;
    cout<<"number of one that insert"<<numberofone<<endl;
    fout<<numberofone; //write the number of the extra"1"
    for (size_t i = 0; i < compressStr.length(); i+=8)
{
    unsigned char byte = 0;
    string str8 = "";
    if (i + 8 < compressStr.length())
        str8 = compressStr.substr(i, 8);
    else
        str8 = compressStr.substr(i);
        while (str8.length()!=8)// add 1 to the last character
        {
            str8.append("1");
        }
        
        
        //cout<<"str8 "<<str8<<endl;
    //https://stackoverflow.com/questions/3289065/how-to-store-8-bits-in-char-using-c/3289182
    for ( size_t j = 0; j < 8; ++j )
        byte |= (str8[j] == '1') << (7 - j);
    //
    //for (unsigned b = 0; b != 8; ++b)
    //{
    //    if (b < str8.length())
    //        byte |= (str8[b] & 1) << b;
    //    else
    //        byte |= 1 << b;
    //}
    cout<<"i:"<<i<<endl;
    cout<<"bits to store :"<<str8<<endl;
    fout.put(byte);
    cout<<"char :"<<byte<<endl;
}
    }


    fin2.close();
    fout.close();

    return 0;
}