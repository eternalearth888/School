#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "image_editor.h"
#include "image_pix.h"

using namespace std;

int main(){

	//Declare a string
	string infile_name,oufile_name;
	char magic1,magic2;

	//Say hi
	cout << "Portable Pixmap (PPM) Image Editor!" << endl;
	cout << endl;

	//Input a input_file_name
	cout << "Enter name of Image file: ";
	cin >> infile_name;
	
	cout << "Enter name of output file: ";
	cin >>  oufile_name;
	cout << endl;

	//Open an input stream
	ifstream infile(infile_name);
	if (!infile) {
		cout << "Error opening input file name\n";
		exit(0);
	}

	ofstream oufile(oufile_name);
	if (!oufile) {
		cout << "Error creating output file\n";
		exit(0);
	}

	//Show all choices;
	cout << "Here are your choices:" << endl
			<< "[1]  convert to greyscale [2]  flip horizontally" << endl
				<<"[3]  negative of red [4]  negative of green [5]  negative of blue" << endl
					<<"[6]  just the reds   [7]  just the greens   [8]  just the blues" << endl;
	cout << endl;

	//q1, q2, q3 ,q4, q5, q6 ,q7, q8
	char q1, q2, q3, q4, q5, q6, q7, q8;

	//Ask those questions. 
    cout << "Do you want [1]? (y/n) " ;
	cin >> q1;
	cout << "Do you want [2]? (y/n) " ;
	cin >> q2;
	cout << "Do you want [3]? (y/n) " ;
	cin >> q3;
	cout << "Do you want [4]? (y/n) " ;
	cin >> q4;
	cout << "Do you want [5]? (y/n) " ;
	cin >> q5;
	cout << "Do you want [6]? (y/n) " ;
	cin >> q6;
	cout << "Do you want [7]? (y/n) " ;
	cin >> q7;
	cout << "Do you want [8]? (y/n) " ;
	cin >> q8;


	//Read in the first line from the file and store it into the string
	infile >> magic1 >> magic2;
	oufile << magic1 << magic2 << endl;

	//declare some variables
	int col, row, max;
	pix *pointpix;
	pix pixnow;

	// input the number of columns and rows
	infile >> col >> row;
	oufile << col << " " << row;
	infile >> max;
	oufile << max << endl;

	//initailze the capibity of the pointer
	pointpix = new pix[col];
	
	//using a for loop to input data from infile and determine whether those number should be changed under different answers.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++){
			pixnow;
			infile >> pixnow.red >> pixnow.green >> pixnow.blue;
			if (pixnow.red < 0 || pixnow.red > max) pixnow.red = 0;
			if (pixnow.red < 0 || pixnow.green > max) pixnow.green = 0;
			if (pixnow.red < 0 || pixnow.blue > max) pixnow.blue = 0;
			if (q1 == 'y') pixnow = grey_scale(pixnow);
			if (q3 == 'y') pixnow = negate_red(max, pixnow);
			if (q4 == 'y') pixnow = negate_green(max, pixnow);
			if (q5 == 'y') pixnow = negate_blue(max, pixnow);
			if (q6 == 'y') pixnow = flatten_red(pixnow);
			if (q7 == 'y') pixnow = flatten_green(pixnow);
			if (q8 == 'y') pixnow = flatten_blue(pixnow);
			pointpix[j] = pixnow;
		}
		
		// if q2 = yes then flip_horizontal
		if (q2 == 'y' ) pointpix = flip_horizontal(pointpix, col);
		
		for (int j = 0; j < col; j++) {
			oufile << pointpix[j].red << " " << pointpix[j].green << " " << pointpix[j].blue << " ";
		}
	}
	

	//Close infile and oufile
	infile.close();
	oufile.close();

	cout << oufile_name << "created" << endl;

	return 0;
}


