/* CSCI261 Homework 1: Image Processing
 *
 * Author: SAMUEL JAMES HARVANEK
 *
 * This program reads in an image and outputs an image in accordance with user commands
 *
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

// Global variables (constants)
const int SIZE = 3000;

// Negate red function
void negate_red(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		arr[i]= 255-arr[i];
	}
}

// Negate green function
void negate_green(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		arr[i+1]= 255-arr[i+1];
	}
}

// Negate blue function 
void negate_blue(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		arr[i+2]= 255-arr[i+2];
	}
}

// flip horizontal function
void flip_horizontal(int arr[], int cols) {
	for(int i = 0; i <= cols/2; i+=3) {
		int x, y, z;
		x = arr[i];
		y = arr[i+1];
		z = arr[i+2];
		arr[i] = arr[cols-i-3];
		arr[cols-i-3] = x;
		arr[i+1] = arr[cols-i-2];
		arr[cols-i-2]= y;
		arr[i+2] = arr[cols-i-1];
		arr[cols-i-1] = z;
	}
}

// Grey scale function
void grey_scale(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		int grey;
		grey = 0.299*arr[i]+0.587*arr[i+1]+0.114*arr[i+2];
		arr[i] = grey;
		arr[i+1] = grey;
		arr[i+2] = grey;
	}
}

// Flattern Red Function
void flatten_red(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		arr[i]= 0;
	}
}

// Flatten Green Function
void flatten_green(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		arr[i+1]= 0;
	}
}

// Flatten Blue Function
void flatten_blue(int arr[], int cols) {
	for(int i = 0; i < cols; i+=3) {
		arr[i+2]= 0;
	}
}

int main() {
	
	// Variable Declaration
	int arr[SIZE], number_columns, number_rows, max_color_value;
	char g_scale, flip_hor, negative_r, negative_g, negative_b, just_reds, just_greens, just_blues;
	string user_infile, user_outfile, magic;
	

	// Getting User Input From Keyboard
	cout << "Portable Pixmap (PPM) Image Editor" << endl;
	cout << " " << endl;
	cout << "Enter name of image file: ";
	cin >> user_infile;

	// Open input file
	ifstream infile(user_infile);

	// Check for error opening input file
	if (!infile) {
		cerr << "Error opening input file" << '\n';;
		exit(1);
	}
	
	// Continuing to get user input from keyboard
	cout << "Enter name of output file: ";
	cin >> user_outfile;

	// Open output file
	ofstream outfile(user_outfile);

	// Check for error opening output file 
	if (!outfile) {
		cerr << "Error opening output file" << '\n';;
		exit(1);
	}

	// Continuing to get user input from keyboard
	cout << " " << endl;
	cout << "Here are your choices:" << endl;
	cout << "[1] " << "Convert to greyscale" << endl;
	cout << "[2] " << "Flip Horizontaly" << endl;
	cout << "[3] " << "Negative of Red" << endl;
	cout << "[4] " << "Negative of Green" << endl;
	cout << "[5] " << "Negative of Blue" << endl;
	cout << "[6] " << "Just the Reds" << endl;
	cout << "[7] " << "Just the Greens" << endl;
	cout << "[8] " << "Just the Blues" << endl;
	cout << " " << endl;
	cout <<"Do You want [1]? (y/n)  ";
	cin >> g_scale;
	cout <<"Do You want [2]? (y/n)  ";
	cin >> flip_hor;
	cout <<"Do You want [3]? (y/n)  ";
	cin >> negative_r;
	cout <<"Do You want [4]? (y/n)  ";
	cin >> negative_g;
	cout <<"Do You want [5]? (y/n)  ";
	cin >> negative_b;
	cout <<"Do You want [6]? (y/n)  ";
	cin >> just_reds;
	cout <<"Do You want [7]? (y/n)  ";
	cin >> just_greens;
	cout <<"Do You want [8]? (y/n)  ";
	cin >> just_blues;

	// Reading data from input file
	// Reads magic number
	infile >> magic;

	// Reads number of columns and rows the image has 
	infile >> number_columns >> number_rows;

	// Reads max value for any pixel color
	infile >> max_color_value;

	// Write to output file 
	// Writes magic number and spaces header properly after magic number
	outfile << magic <<'\n';

	// Writes number of columns and rows and spaces header properly 
	outfile << number_columns << ' ' << number_rows << '\n';

	// Writes max color value and spaces header properly after max color value
	outfile << max_color_value << '\n';

	// Check to see if image is too large for our array
	if (SIZE <= number_columns*3) {
		cerr << "Image is too big" << '\n';
		exit(1);
	}

	// Read in one row at a time and write one row at a time
	for (int i = 0; i < number_rows; i++) {
		for(int j = 0; j < number_columns*3; j++) { 
			infile >> arr[j];
		}
		if(g_scale == 'y' || g_scale == 'Y') {
			grey_scale(arr, number_columns*3);
		}
		if(flip_hor == 'y' || flip_hor == 'Y') {
			flip_horizontal(arr, number_columns*3);
		} 
		if(negative_r == 'y' || negative_r == 'Y') {
			negate_red(arr, number_columns*3);
		}
		if(negative_g == 'y' || negative_g == 'Y') {
			negate_green(arr, number_columns*3);
		} 
		if(negative_b == 'y' || negative_b == 'Y') {
			negate_blue(arr, number_columns*3);
		} 
		if(just_reds == 'y' || just_reds == 'Y') {
			flatten_green(arr, number_columns*3);
			flatten_blue(arr, number_columns*3);
		} 
		if(just_greens == 'y' || just_greens == 'Y') {
			flatten_red(arr, number_columns*3);
			flatten_blue(arr, number_columns*3);
		}
		if(just_blues == 'y' || just_blues == 'Y') {
			flatten_red(arr, number_columns*3);
			flatten_green(arr, number_columns*3);
		}
		for(int j = 0; j < number_columns*3; j++) { 
			outfile << arr[j] << ' ';
		}
	}

	// Close the input and output file
	infile.close();
	outfile.close();
	
	// Exit program.
    return 0;
}