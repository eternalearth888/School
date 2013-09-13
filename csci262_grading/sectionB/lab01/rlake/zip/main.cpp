#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

static const int CAPACITY = 3000;

int negate_red(bool is_wanted, bool is_red, int oldRed, int maxColor) {
	int newRed;
	if (is_wanted && is_red){
		newRed = abs((oldRed-maxColor));
		return newRed;
	} else return oldRed;
}

int negate_green(bool is_wanted, bool is_green, int oldGreen, int maxColor) {
	int newGreen;
	if (is_wanted && is_green){
		newGreen = abs((oldGreen-maxColor));
		return newGreen;
	} else return oldGreen;
}

int negate_blue(bool is_wanted, bool is_blue, int oldBlue, int maxColor) {
	int newBlue;
	if (is_wanted && is_blue){
		newBlue = abs((oldBlue-maxColor));
		return newBlue;
	} else return oldBlue;
}

//doesnt work
int* flip_horizontal(bool is_wanted, int data[], int numColumns) {	
	if (is_wanted) {
		int newArray[CAPACITY];
		for (int i = 0; i < (numColumns); i++) {
			newArray[3*i] = data[(numColumns-i-1)*3];
			newArray[3*i+1] = data[(numColumns-i-2)*3];
			newArray[3*i+2] = data[(numColumns-i-3)*3];
		}
		for (int i = 0; i < (3*numColumns); i+3) {
			data[i] = newArray[i];
		}
		return data;
	} else return data;
}

void grey_scale(bool is_wanted, int data[], int numColumns) {
	if(is_wanted) {
		int i = 0;
		while (i <= (3*numColumns)) {
			int avg = ((data[i] + data[i+1] + data[i+2]) / 3.0);
			data[i] = data[i+1] = data[i+2] = avg;
			i = i+3;
		} 
		return;
	} else return;
}

int flatten_red(bool is_wanted, bool is_red, int red) {
	if (is_wanted && is_red){
		red = 0;
		return red;
	} else return red;
}

int flatten_blue(bool is_wanted, bool is_blue, int blue) {
	if (is_wanted && is_blue){
		blue = 0;
		return blue;
	} else return blue;
}

int flatten_green(bool is_wanted, bool is_green, int green) {
	if (is_wanted && is_green){
		green = 0;
		return green;
	} else return green;
}



int main() {

	string in_file;
	string out_file;

	string ppm_type;
	int rows;
	int columns;
	int max_color;
	int temp, red, green, blue;

	char answer;
	bool isRed = 0, isBlue = 0, isGreen = 0;
	bool greyScale = 0, flipHorizontal = 0, negateReds = 0,
		negateGreens = 0, justRed = 0, negateBlues = 0,
		justGreen = 0, justBlue = 0;
	
	int buffer[CAPACITY];

	//request file names
	cout << "Enter the input file name: ";
	cin >> in_file;
	cout << "\nEnter the output file name: ";
	cin >> out_file;
	
	//open file and check for error
	ifstream source(in_file.c_str());
	if (!source) {
		cerr << "Error opening ouput file.\n";
		exit(1);
	}

	//start read from file
	source >> ppm_type >> rows >> columns >> max_color;
	
	//determine if file will fit in buffer
	if ((3*columns) > CAPACITY) {
		cerr << "Your file is too BIG!!!.\n";
		system ("pause");
		exit(1);
	}

	//options menu
	cout << "\nHere are your choices:\n" <<
	     "[1]  convert to greyScale [2]  flip horizontally\n" <<
	     "[3]  negative of red [4]  negative of green [5]  negative of blue\n" <<
	     "[6]  just the reds   [7]  just the greens   [8]  just the blues\n";

	cout << "\nDo you want [1]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		greyScale = 1;
	}
	
	cout << "\nDo you want [2]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		flipHorizontal = 1;
	}

	cout << "\nDo you want [3]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		negateReds = 1;
	}
	
	cout << "\nDo you want [4]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		negateGreens = 1;
	}
	
	cout << "\nDo you want [5]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		negateBlues = 1;
	}
	
	cout << "\nDo you want [6]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		justRed = 1;
	}
	
	cout << "\nDo you want [7]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		justGreen = 1;
	}
	cout << "\nDo you want [8]? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		justBlue = 1;
	}
	
	//write header to output
	ofstream output(out_file);
	output << ppm_type << endl << rows << ' ' << columns << endl << max_color << endl;
	
	//read from file
	for (int j = 0; j < rows; j++){
		for (int i = 0; i < (3*columns); i++) {
			if (i%3 == 0) {
				isRed = 1;
			} else if (i%3 == 1) {
				isGreen = 1;
			} else if (i%3 == 2) {
				isBlue = 1;
			}
			source >> temp;

			//impliment functions
			temp = negate_red(negateReds, isRed, temp, max_color);
			temp = negate_green(negateGreens, isGreen, temp, max_color);
			temp = negate_blue(negateBlues, isBlue, temp, max_color);
			temp = flatten_red(justRed, isRed, temp);
			temp = flatten_green(justGreen, isGreen, temp);
			temp = flatten_blue(justBlue, isBlue, temp);
			
			buffer[i] = temp;
			
		}
		for (int i = 0; i < (3*columns); i++) {
			
			flip_horizontal(flipHorizontal, buffer, columns);
			grey_scale(greyScale, buffer, columns);

			output << buffer[i] << ' ';
		}
	}

	
	//close files
	source.close();
	output.close();

	cout << "\nTransfer complete [; \n\n";


	system ("pause");
	return 0;
}