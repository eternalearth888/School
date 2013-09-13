// CSCI 262
// Lab 1
// By: Nathaniel Keller
// http://eecs.mines.edu/Courses/csci262/labs/lab01/lab01.html

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "picture.h"
using namespace std;

int main(){
	// Variable Declarations
	string filename, outfilename;
	bool filter_choice[12] = {false};

	// Create input filestream
	cout << "Enter a filename: ";
	// cin >> filename;
	filename = "tinypix.ppm"; //-----------------------------------------------------------------remove
	picture edit(filename);

	// Create output filestream
	cout << "Enter an output filename: ";
    // cin >> outfilename;
	outfilename = "OUTPUT.ppm"; //-----------------------------------------------------------------remove

	// Determine filters the user wants to apply
	cout << endl << endl << "Filter choices:" << endl 
		<< "[1] Convert to greyscale" << endl 
		<< "[2] Flip Horizontally" << endl 
		<< "[3] Negative of Red" << endl 
		<< "[4] Negative of Green" << endl 
		<< "[5] Negative of Blue" << endl 
		<< "[6] Flatten Reds" << endl 
		<< "[7] Flatten Greens" << endl 
		<< "[8] Flatten Blues" << endl;
	for(int i = 0; i < 8; i++){
		char filter_ans;
		cout << "Do you want [" << i+1 << "]? (y/n): ";
		cin >> filter_ans;
		if(filter_ans == 'y' || filter_ans == 'Y'){
			filter_choice[i] = true;
		} else if(filter_ans == 'n' || filter_ans == 'N'){
			filter_choice[i] = false;
		} else {
			cout << "Invalid entry, try again" << endl;
			i--;
		}
	}

	//Apply Filters
	edit.applyFilters(outfilename,filter_choice);

	cout << endl << endl << outfilename << " created with specified filters." << endl << endl;
	
	system("pause");
	return 0;
}
