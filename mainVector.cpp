#include "classVector.h"

int main(int argc, char const *argv[]){

	Vector<int> Test(5, 6);
	cout << "Size: " << Test.size() << endl;
	cout << "Capacity: " << Test.capacity() << endl;
	for (int i = 0; i < Test.size(); i++){
		cout << Test[i] << " ";
	}
	cout << endl;
	Test.push_back(5);
	cout << "Size: " << Test.size() << endl;
	cout << "Capacity: " << Test.capacity() << endl;
	for (int i = 0; i < Test.size(); i++){
		cout << Test[i] << " ";
	}
	cout << endl;
	Test.push_back(9);
	cout << "Size: " << Test.size() << endl;
	cout << "Capacity: " << Test.capacity() << endl;
	for (int i = 0; i < Test.size(); i++){
		cout << Test[i] << " ";
	}
	cout << endl;
	return 0;
}