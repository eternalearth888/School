#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// global variables
ofstream outFile;
ifstream verticalFile;
string outputNameString, ppmType;
const int BUFFERSIZE = 3000;
int buffer[BUFFERSIZE], verticalFlipBuffer[BUFFERSIZE][BUFFERSIZE * 3];
int maximumColorValue, temp, column, row, halfOfMaxValue, addSubtract, randNumber;


void negate_red(int numberInArray) {
	buffer[numberInArray] = maximumColorValue - buffer[numberInArray];
}

void negate_green(int numberInArray) {
	buffer[numberInArray] = maximumColorValue - buffer[numberInArray];
}

void negate_blue(int numberInArray) {
	buffer[numberInArray] = maximumColorValue - buffer[numberInArray];
}

void flip_horizontal(int numberInArray) {
	outFile << buffer[column * 3 - numberInArray - 3] << " " << buffer[column * 3 - numberInArray - 2] << " " << buffer[column * 3 - numberInArray - 1] << " ";
}

void grey_scale(int numberInArray) {
	temp =  ( buffer[numberInArray] + buffer[numberInArray - 1] + buffer[numberInArray - 2] ) / 3;
	for (int q = 0; q < 3; ++q) {
		buffer[numberInArray - q] = temp;
	}
}

void flatten_red(int numberInArray) {
	buffer[numberInArray] = 0;
}

void flatten_green(int numberInArray) {
	buffer[numberInArray] = 0;
}

void flatten_blue(int numberInArray) {
	buffer[numberInArray] = 0;
}

void horizontal_blur(int numberInArray) {
	temp =  ( buffer[numberInArray] + buffer[numberInArray - 3] + buffer[numberInArray - 6] ) / 3;
	for (int q = 0; q < 3; ++q) {
		buffer[numberInArray - ( q * 3 ) ] = temp;
	}
}

void extreme_contrast(int numberInArray) {
	if (buffer[numberInArray] > halfOfMaxValue) {
		buffer[numberInArray] = maximumColorValue;
	} else if (buffer[numberInArray] < halfOfMaxValue) {
		buffer[numberInArray] = 0;
	}
}

void random_noise(int numberInArray) {
	srand (time (NULL));
	if (buffer[numberInArray] > 1) {
		randNumber = rand() % buffer[numberInArray];
	} else if (buffer[numberInArray] == 1) {
		randNumber = 1;
	} else {
		randNumber = 0;
	}
	addSubtract = rand() % 2;
	if (addSubtract == 0) {
		buffer[numberInArray] = buffer[numberInArray] - randNumber;
	} else {
		if (buffer[numberInArray] + randNumber < maximumColorValue) {
			buffer[numberInArray] = buffer[numberInArray] + randNumber;
		} else {
			buffer[numberInArray] = 255;
		}
	}
}

void flip_horizontal() {
	verticalFile.open(outputNameString.c_str());

	verticalFile >> ppmType;
	verticalFile >> column;
	verticalFile >> row;
	verticalFile >> maximumColorValue;

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column * 3; ++j) {
			verticalFile >> verticalFlipBuffer[i][j];
		}
	}

	verticalFile.close();

	outFile.open(outputNameString.c_str());
	outFile << "P3 " << endl;
	outFile << column << " ";
	outFile << row << endl;
	outFile << maximumColorValue << endl;
	for (int k = row; k > 0; --k) {
		for (int l = 0; l < column * 3; ++l) {
			outFile << verticalFlipBuffer[k][l] << " ";
		}
		outFile << endl;
	}

	outFile.close();
}

int main() {
	// variable declaration
	string inputNameString;
	ifstream inFile;
	int numberOfPixels = BUFFERSIZE / 3;
	char choices[12];


	// input file setup
	cout << "Portable Pixmap (PPM) Image Editor!\n\n" << "Enter name of image file: ";
	cin >> inputNameString;

	inFile.open(inputNameString.c_str());

	if (!inFile) {
		cerr << "Error opening " << inputNameString << "!\n";
		exit (1);
	}

	// output file setup
	cout << "Enter name of output file: ";
	cin >> outputNameString;

	outFile.open(outputNameString.c_str());

	if (!inFile) {
		cerr << "Error opening/creating " << outputNameString << "!\n";
		exit (1);
	}

	inFile >> ppmType;
	if (ppmType != "P3") {
		cout << "Incorrect PPM type.\n";
		exit(1);
	}

	// copy over ppm file info
	inFile >> column;
	inFile >> row;
	inFile >> maximumColorValue;
	outFile << "P3 " << endl;
	outFile << column << " ";
	outFile << row << endl;
	outFile << maximumColorValue << endl;

	// half of maximum value
	halfOfMaxValue = maximumColorValue / 2;

	// check pixel size
	if (column > numberOfPixels) {
		cout << "The image is too large for the program.\n";
		exit(1);
	}

	// menu for choices
	cout << "Here are your choices:\n\n" << "[1]  convert to greyscale [2]  flip horizontally\n";
	cout << "[3]  negative of red [4]  negative of green [5]  negative of blue\n";
	cout << "[6]  just the reds   [7]  just the greens   [8]  just the blues\n";
	cout << "[9]  horizontal_blur [10] extreme_contrast [11] random_noise\n";
	cout << "[12] flip_horizontal\n";
	cout << "Warning: Lower numbers perform actions first.\n\n";
	for (int k = 0; k < 12; ++k) {
		cout << "Do you want [" << k + 1 << "]? (y/n) ";
		cin >> choices[k];
	}

	// begin photo editing
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column * 3; ++j) {
			inFile >> buffer[j];

			// grey scale check
			if (j % 3 == 2 && choices[0] == 'y') {
				grey_scale(j);
			}

			// check to negate colors
			if (j % 3 == 1 && choices[2] == 'y') {
				negate_red(j);
			} else if (j % 3 == 2 && choices[3] == 'y') {
				negate_green(j);
			} else if (j % 3 == 0 && choices[4] == 'y') {
				negate_blue(j);
			}
			
			// check to flatten colors
			if (j % 3 == 1 && choices[5] == 'y') {
				flatten_red(j);
			} else if (j % 3 == 2 && choices[6] == 'y') {
				flatten_green(j);
			} else if (j % 3 == 0 && choices[7] == 'y') {
				flatten_blue(j);
			}

			// horizontal blur
			if (j > 6 && choices[8] == 'y') {
				horizontal_blur(j);
			}

			// extreme contrast
			if (choices[9] == 'y') {
				extreme_contrast(j);
			}

			// random noise
			if (choices[10] == 'y') {
				random_noise(j);
			}
		}
		
		// check whether to flip horizontal or not
		for (int l = 0; l < column * 3; l = l + 3) {
			if (choices[1] == 'y') {
				flip_horizontal(l);
			} else if (choices[1] != 'y') {
				outFile << buffer[l] << " " << buffer[l + 1] << " " << buffer[l + 2] << " ";
			}
		}

		outFile << endl;
	}

	// close both files
	inFile.close();
	outFile.close();

	if (choices[11] == 'y')
		flip_horizontal();

	return 0;
}