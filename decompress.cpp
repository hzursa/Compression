#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
using namespace std; 

string content;
string lengthOfTree;
string treeCode;
string lengthOfone;
string compressedCode;

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

int main(int argc, char *argv[]){
	if (argc != 3) {
		cout << "please enter 2 arguments" << endl;
		return 0;
	}
		

    char ch;
    ifstream fin(argv[1], ios::binary);
    ofstream fout(argv[2],ios::out | ios::binary);
	if (fin) {
		fin >> content;
		cout << "the full content is: "<<content << endl;
		cout <<"the length of full content: "<< content.length()<< endl;
        lengthOfTree = content.substr(0,3);
        cout <<"lengthOfTree = "<<lengthOfTree<<endl; 

	}
		


    //char *  lengthoftree = new char [4];
    //fin.read(lengthoftree,3);
    //lengthoftree[3]='\0';
    //cout<<"lengthoftree: "<<stoi(lengthoftree)<<endl;
    //char * treecode = new char [stoi(lengthoftree)+1];
    //fin.read(treecode,stoi(lengthoftree));
    //treecode[stoi(lengthoftree)]='\0';
    //string someString(treecode);
    //delete[]lengthoftree;
    //delete[]treecode;
    //cout<<"content of tree "<<content<<endl;
	fout << content<< content.length();
    //while (fin.read(&ch, sizeof(ch))) {
	//   std::bitset<8> bin_x(ch);
	//   std::cout<<"Reading bits" << bin_x <<endl;
//}
    fin.close();
    fout.close();
    //delete[]lengthoftree;
    //delete[]treecode;

}