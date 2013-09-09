#include <iostream>
#include <fstream>
#include <string>
#include "image.h"

using namespace std;

// Author: TREVOR HAAK
// Title: Haak Lab 01 130831

int main(){

	//variable declarations
	string file_in;
	string file_out;
	image ppm_image;

	//prompt the user to enter image filename details
	cout << "Please detail which image you wish to copy and where." << endl << endl;
	cout << "Original image file: ";
	cin >> file_in;
	cout << "New output file: ";
	cin >> file_out;
	cout << endl;

	//copies file over, prompts user with effects menu, and carries out those effects
	ppm_image.select_effects(file_in, file_out);


	cout << "Finished." << endl;

	system("pause");
	return 0;
}