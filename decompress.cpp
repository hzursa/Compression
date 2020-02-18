#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h> 

using namespace std; 

string content;
string lengthOfTree;
int treeLength;
string treeCode;
string lengthOfone;
int oneLength;
string compressedCode;
string decompressed;
string originalcode;


string ToBinary(string words) {
    string binaryString = "";
    for (char& _char : words) {
        binaryString +=bitset<8>(_char).to_string();
    }
    return binaryString;
}

struct HeapNode { 
  
    // ASCII code of the character
    char data; 

  
    // Define left and right child 
    HeapNode *left, *right; 
  
    HeapNode(char data) { 
  
        left = right = NULL; 
        this->data = data; 
    } 
    HeapNode(char data,HeapNode *left,HeapNode *right) { 
  
        this->left=left;
        this->right = right; 
        this->data = data; 
    } 
}; 

void readTree(struct HeapNode* root){
    if(treeCode=="")
        return;
    cout<<"--------Doing readTree-----------"<<endl;
    struct HeapNode *left, *right; 
    cout<< "now treeCode is: "<<treeCode<<endl;
    char a = treeCode[0];
    cout<<"reading fisrt character"<<endl;
    treeCode = treeCode.substr(1,treeCode.length());//read one delete one
    cout<<"deleting first character: "<<a<<endl;
    cout<< "treecode after deleting "<<treeCode<<endl;
    if (a == '1'){
        cout<<"character that is reading = 1"<<endl;
        char b = treeCode[0];
        cout<<b<<" "<<endl;
        root->data = b;
        cout<<"the next character is : "<<b<<" , putting it into the tree."<<endl;
        root->left = NULL;
        root->right = NULL;
        treeCode = treeCode.substr(1,treeCode.length());//read one delete one
        return;
    }else
    {
        cout<<"character that is reading is 0"<<endl;
        left = new HeapNode('\0');
        right = new HeapNode('\0');
        root->left = left;
        root->right = right;
        if(root->data == '\0')
            cout<<"root data"<<"\\0"<<endl;
        root->data = '\0';
        cout<<"cout root data after change"<<"\\0"<<endl;
        cout<<"going to left"<<endl;
        readTree(root->left); 
        cout<<"going to right"<<endl;
        readTree(root->right);
        cout<<"--------end this round--------"<<endl;    
        return;
    }
}
void decoding(struct HeapNode* root ){
    if(root->data != '\0'){
        originalcode += root->data;
        return;
    }else
    {
        char a = compressedCode[0];
        compressedCode = compressedCode.substr(1,compressedCode.length());
        if(a == '1'){
            decoding(root->right);
        }else
        {
            decoding(root->left);
        }
    }    
    return;
}

int main(int argc, char *argv[]){
	if (argc != 3) {
		cout << "please enter 2 arguments" << endl;
		return 0;
	}
		

    char ch;
    ifstream fin(argv[1], ios::binary);
    ofstream fout(argv[2],ios::out | ios::binary);
	if (fin) {
		
        fin.seekg(0, std::ios::end);   
        content.reserve(fin.tellg());
        fin.seekg(0, std::ios::beg);

        content.assign((std::istreambuf_iterator<char>(fin)),
                    std::istreambuf_iterator<char>());
        
		//cout << "the full content is: "<<content <<endl;
		//cout <<"the size of full content: "<< sizeof(content)<endl;
        //cout <<"the length of full content: "<< content.length()<endl;
        lengthOfTree = content.substr(0,3);
        cout <<"lengthOfTree = "<<lengthOfTree<<endl; 
        istringstream(lengthOfTree) >> treeLength;
        cout<<"int of treelength:"<<treeLength<<endl;
        treeCode = content.substr(3,treeLength);
        cout<< "treeCode: "<<treeCode<<endl;
        lengthOfone = content.substr(3+treeLength,4+treeLength);
        istringstream(lengthOfone) >> oneLength;
        cout<<"int of the number of one:"<<oneLength<<endl;
        cout<<"compressedCode :"<<compressedCode<<endl;
        compressedCode = ToBinary(content.substr(4+treeLength));
        if (oneLength !=8){
            compressedCode = compressedCode.substr(0,compressedCode.length()-oneLength);}
        cout<<"the huffman code is:  "<<compressedCode<<endl;
        cout<<"------------build tree------"<<endl;
        HeapNode *root = new HeapNode('\0');
        readTree(root);
        cout<<"------------finish building huffman tree------"<<endl;
        while (compressedCode !="")
        {
            //cout<<compressedCode<<endl;
            decoding(root);
        }
        cout<<"the original code is:  "<<originalcode<<endl;
        fout<<originalcode;
        
	}
		

    fin.close();
    fout.close();


}