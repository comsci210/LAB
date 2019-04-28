#include<iostream>
using namespace std;

int* gimmieArray(int size){
	int result[size];
	for (int i = 0; i < size; ++i)
	{result[i];}
}


int main(){
	int* brokenArray = gimmieArray(100);

	for(int i=0; i<1000000;++i)
	{cout << brokenArray[i] << endl;}
}
