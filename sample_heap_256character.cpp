//Zhou Hong 19025779
//Zichen Xu 15377704
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
const int MAXSIZE = 1000;
const int  ASCII = 256; //

vector<int> vectorA;
int fre [ASCII];


/*  Implement a Heap class here (from the slides)  */
class Heap
{
private: 
	int data[MAXSIZE];
	int last;
	int Icounter, Dcounter;
public:
	Heap(){last = -1;
		for(int i = 0; i < MAXSIZE; i++) { data[i]=0; }
        Icounter = 0;
        Dcounter = 0;}
	//~Heap(); delete it otherwise error:Undefined symbols for architecture x86_64
	void InertHeap(int newthing);
	void PrintHeap();
	int returnI(){return Icounter;}
	int returnD(){return Dcounter;}
	int DeleteRoot();
};

void Heap::InertHeap( int newasdii ){
	data[last+1]= newasdii;
	last = last+1;
	int temp, swindex = last, parindex = 0;
	if (last == 0) return;
	int childindex = last;
	bool swapping = true;
	while(swapping==true){
		 if(swindex == 0) break;
        swapping=false;
        if(swindex%2==0) parindex=swindex/2-1;
        else parindex=swindex/2;
        Icounter++;
        if(fre[data[swindex]+127]>fre[data[parindex]+127]){
            temp=data[swindex];
            data[swindex]=data[parindex];
            data[parindex]=temp;
            swapping=true;
            swindex=parindex;
        }
	}	
}



int Heap::DeleteRoot() {
    int deletedvalue = data[0];
    swap(data[0],data[last]);
    data[last] = 0;
    
    int  i=0;
    int j=(2*i)+1;
    int valuetoswap;
    while(true){
        if(data[j]==0&&data[j+1]==0){break;}
        
        if(data[j+1]==0){
            valuetoswap = data[j];
        }
        else {
            valuetoswap = max(data[j],data[j+1]);
            Dcounter++;
        }
        if(data[i]>valuetoswap) {
            Dcounter++;
            break;
        }
        if(valuetoswap == data[j+1]) {
            swap(data[j+1],data[i]);
            i = j+1;
            j = (2*i)+1;
            Dcounter++;
        }
        else if(valuetoswap==data[j]){
            swap(data[j],data[i]);
            i = j;
            j = (2*i)+1;
            Dcounter++;
        }
    }
    last--;
    return deletedvalue;
}


void Heap::PrintHeap(){
	for (int i = 0; i < last+1; ++i)
	{
		cout<<data[i]<<" ";
	}
}

void heapsort(vector<int> &sortingvector,int number_of_elements, char* filename){
    std::vector<int> v = sortingvector;
    cout<<"Heap before sorting: "<<filename<<endl;
    Heap myHeap; //declare a Heap instance here */
	int i =0;
  	while(i<number_of_elements)
  	{
  		myHeap.InertHeap(v[i]);
  		i++;
  	}
  /* Using the sortingvector, INSERT elements into the Heap */
  	myHeap.PrintHeap();
  	 for (int i=number_of_elements-1;i>=0;i--) {
	  	v[i]=myHeap.DeleteRoot();
  	}/* After building the heap from the file, PRINT the current state of the heap before sorting */
  	cout<<endl;
  	cout<<"InsertHeap: "<<myHeap.returnI()<<" comparisons"<<endl;
  	cout<<"DeleteRoot: "<<myHeap.returnD()<<" comparisons"<<endl; /* PRINT the number of comparisons for the Insert and Deletion tasks */
  	cout<<"Vector after sorting:"<<endl;
  	for(int count=0;count<number_of_elements;count++){
		printf("%d ",v[count]);
	}
	cout<<endl<<endl;
}

int main()
 {
   char ch;
    Heap huffman;
   std::ifstream fin("out.txt", std::ios::binary);

   while (fin.read(&ch, sizeof(ch))) {
	   std::cout << int(ch) << std::endl;
       fre[int(ch)+127]+=1;
   }
   for (size_t i = 0; i < 256; i++)
   {
       if (fre[i]>0)
       {
           cout<<endl<<"ASDII = "<<int(i-127)<<", number = "<<fre[i]<<" ."<<endl;
           huffman.InertHeap(int(i-127));
           huffman.PrintHeap();
       }
       
   }



   return 0;
 }