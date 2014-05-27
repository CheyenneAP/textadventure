#include <iostream>
#include "string"
#include "vector"
#include <stdlib.h> // system("cls")
#include <fstream>
#include <sstream> // konvertieren
#include <algorithm> // find

using namespace std;

//gibt die Größe eines Arrays zurück XXX
int size(int array[]){
	return sizeof(array)/sizeof(array[0]);
}

int main(){
	List<string> item;
	item.push_back("Hallo ");
	//cout << "Array Größe: " << sizeof(item)/sizeof(item[0]) << endl;
	/*cout << "Hier alle Items:" << endl;
	for(int i=0; i < sizeof(item)/sizeof(item[0]); i++){
		cout << item[i] << endl;
	}*/
	return 0;
}
