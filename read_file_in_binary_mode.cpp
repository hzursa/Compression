#include <fstream>
#include <iostream>
#include <bitset>

int main()
 {
   char ch;

   std::ifstream fin("out.txt", std::ios::binary);

   while (fin.read(&ch, sizeof(ch))) {
	   std::cout << int(ch) << std::endl;
	   std::bitset<8> bin_x(ch);
	   std::cout << bin_x << std::endl;
   }

   return 0;
 }