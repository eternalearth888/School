/* Lab 1: PPM image editor.
*
* Author: Christen Boyer
*
* Description: This program reads a file in ppm format, makes changes to it if desired, and then copies it to a new file. 
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Function definitions
void negate_red(int* myArray, int cols, int maxRGB) {  // Its job is to negate the red number of each pixel.
	for(int i=0; i<3*cols; i+=3){
		myArray[i] = maxRGB - myArray[i];
	}
}

void negate_green(int* myArray, int cols, int maxRGB) {  // Its job is to negate the green number of each pixel.
	for(int i=1; i<3*cols; i+=3){
		myArray[i] = maxRGB - myArray[i];
	}
}

void negate_blue(int* myArray, int cols, int maxRGB) {  // Its job is to negate the blue number of each pixel.
	for(int i=2; i<3*cols; i+=3){
		myArray[i] = maxRGB - myArray[i];
	}
}

void flip_horizontal(int* myArray, int cols) {  // that flips each row horizontally
	int newArray[3000];
	for(int i=0; i<cols; i++){
		newArray[i*3] = myArray[((cols-1-i)*3)];
		newArray[i*3+1]=myArray[((cols-1-i)*3)+1];
		newArray[i*3+2]=myArray[((cols-1-i)*3)+2];
	}	

	for(int i=0; i<3*cols; i++){
		myArray[i]=newArray[i];
	}

}

void grey_scale(int* myArray, int cols) {  // sets each pixel value to the average of the three
	double avg;
	for(int i=0; i<3*cols; i+=3){
		avg = (myArray[i]+myArray[i+1]+myArray[i+2])/3;
		//*(data + i) = avg;  //JK Slyby example 
		myArray[i] = avg;
		myArray[i+1] = avg;
		myArray[i+2] = avg;
	}
}

void flatten_red(int* myArray, int cols) {  // sets the red value to zero
	for(int i=0; i<3*cols; i+=3){
		myArray[i] = 0;
	}
}
void flatten_green(int* myArray, int cols) {  // sets the green value to zero
	for(int i=1; i<3*cols; i+=3){
		myArray[i] = 0;
	}
}
void flatten_blue(int* myArray, int cols) {  // sets the blue value to zero
	for(int i=2; i<3*cols; i+=3){
		myArray[i] = 0;
	}
}



int main() {
//welcome message
	cout << "Welcome to the Portable Pixmap (PPM) Image Editor!\n";
//user enters input file. its then opened and checked for errors.
	cout << "Please enter an existing PPM file name for the input image: ";
	string inFileName;
	cin >> inFileName;
	ifstream infile (inFileName);
	if (infile.fail()){
		cout << "Input File Read Failed. Program Aborted.\n";
		system ("pause");
		exit (1);
	}
//user enters output file. its then opened and checked for errors.	
	cout << "Please enter a file name for the output image: ";
	string outFileName;
	cin >> outFileName;
	ofstream outfile (outFileName);
	if (outfile.fail()){
		cout << "Output File Read Failed. Program Aborted.\n";
		system ("pause");
		exit (1);
	}
//declaration of variables
	const int CAPACITY = 3000;
	string ppmType;
	int columns;
	int rows;
	int maxColor;
	int infileArray[CAPACITY];
	char choice1;
	char choice2;
	char choice3;
	char choice4;
	char choice5;
	char choice6;
	char choice7;
	char choice8;

	cout << "\nThe program is now opening " << inFileName << " image file.\n";
//reading the header in the input file	
	infile >> ppmType; 
	infile >> columns >> rows;
	infile >> maxColor;
//writing the header into the output file
	outfile << ppmType << "\n" << columns << "\t" << rows << "\n" << maxColor << "\n";
//user choices for image altering
	cout << "\nHere are your choices for how you can alter the image: \n\n";
	cout << "[1] convert to greyscale  [2] flip horizontally \n"
		"[3] negative of red  [4] negative of green  [5] negative of blue \n"
		"[6] just the reds  [7] just the greens  [8] just the blues \n\n";
	cout << "Do you want [1]? (y/n) ";
	cin >> choice1;
	cout << "Do you want [2]? (y/n) ";
	cin >> choice2;
	cout << "Do you want [3]? (y/n) ";
	cin >> choice3;
	cout << "Do you want [4]? (y/n) ";
	cin >> choice4;
	cout << "Do you want [5]? (y/n) ";
	cin >> choice5;
	cout << "Do you want [6]? (y/n) ";
	cin >> choice6;
	cout << "Do you want [7]? (y/n) ";
	cin >> choice7;
	cout << "Do you want [8]? (y/n) ";
	cin >> choice8;

//for loops to read the whole file
	for (int j = 0; j < rows; j++){  //outer for loop to read each row
		for (int i = 0; i < (3*columns); i++){  //inner for loop to read each column of that row
			infile >> infileArray[i];
		}
//if statements to execute user choices
		if (choice1 == 'y' || choice1 == 'Y'){
			grey_scale(infileArray, columns);
		}
		if (choice2 == 'y' || choice2 == 'Y'){
			flip_horizontal(infileArray, columns);
		}
		if (choice3 == 'y' || choice3 == 'Y'){
			negate_red(infileArray, columns, maxColor);
		}
		if (choice4 == 'y' || choice4 == 'Y'){
			negate_green(infileArray, columns, maxColor);
		}
		if (choice5 == 'y' || choice5 == 'Y'){
			negate_blue(infileArray, columns, maxColor);
		}
		if (choice6 == 'y' || choice6 == 'Y'){
			flatten_green(infileArray, columns);
			flatten_blue(infileArray, columns);
		}
		if (choice7 == 'y' || choice7 == 'Y'){
			flatten_red(infileArray, columns);
			flatten_blue(infileArray, columns);
		}
		if (choice8 == 'y' || choice8 == 'Y'){
			flatten_red(infileArray, columns);
			flatten_green(infileArray, columns);
		}
				

		for (int i = 0; i < (3*columns); i++){  //another inner for loop to write each new row to the output file
			outfile << infileArray[i] << "  ";
		}
		outfile << "\n";
	}

//close each file	
	infile.close();
	outfile.close();

//to tell the user to view the new image
	cout << "To view the new image you created, open the output file using Gimp.\n\n";
	
	system ("pause");
	return 0;

}