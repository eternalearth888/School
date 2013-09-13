#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <time.h>
#include <random>

using namespace std;

// Function Delcarations:
void negate_red(int bufferArray[], int columnLength, int maxColorVal);
void negate_green(int bufferArray[], int columnLength, int maxColorVal);
void negate_blue(int bufferArray[], int columnLength, int maxColorVal);
void flip_horizontal(int bufferArray[], int columnLength);
void grey_scale(int bufferArray[], int columnLength);
void flatten_red(int bufferArray[], int columnLength);
void flatten_green(int bufferArray[], int columnLength);
void flatten_blue(int bufferArray[], int columnLength);
void horizontal_blur(int bufferArray[], int columnLength);
void extreme_contrast(int bufferArray[], int columnLength, int maxColorVal);
void random_noise(int bufferArray[], int columnLength, int maxColorVal, const int RANDOM_RANGE);
void manipulateImage(int bufferArray[], int columnLength, int maxColorVal, bool options[], const int RANDOM_RANGE);
void flip_vertical(bool options[], string outFileName);



int main() {
	srand(time(NULL));
	const int BUFFER_SIZE = 3000;
	const int RANDOM_RANGE = 15;
	const int NUMBER_OF_OPTIONS = 12;
	bool options[NUMBER_OF_OPTIONS];
	string imageFileName, outFileName;

	cout << "Portable Pixmap (PPM) Image Editor" << endl;
	cout << "Enter name of image file: ";
	cin >> imageFileName;

	ifstream imageFile(imageFileName.c_str()); // Open file and call it imageFile.
	if (!imageFile) {
		cerr << "Error opening input file" << endl;
		exit(1);
	}

	cout << "Enter name of output file: ";
	cin >> outFileName;

	ofstream outFile(outFileName.c_str());

	cout << "Here are your choices: " << endl;
	cout << "[1] convert to greyscale  [2] flip horizontally" << endl;
	cout << "[3] negative of red  [4] negative of green [5] negative of blue" << endl;
	cout << "[6] just the reds  [7]  just the greens  [8] just the blues" << endl;
	cout << "[9] horizontal blur  [10] extreme contrast  [11] random_noise" << endl;
	cout << "[12] flip vertically" << endl;
	char choice;
	for (int i = 0; i < NUMBER_OF_OPTIONS; ++i) {
		cout << "Do you want [" << i + 1 << "] (y/n)  ";
		cin >> choice;
		if ((choice == 'y') || (choice == 'Y')) {
			options[i] = true;
		} else {
			options[i] = false;
		}
	}
	cout << "Now Proccessing...  ";
	string magicNumber;
	int numberOfColumns;
	int numberOfRows;
	int maxColorVal;

	imageFile >> magicNumber;
	imageFile >> numberOfColumns;
	imageFile >> numberOfRows;
	imageFile >> maxColorVal;
	int columnLength = numberOfColumns * 3;
	if (columnLength >= BUFFER_SIZE) {
		cerr << "Error, buffer limit reached." << endl;
		exit(1);
	}
	outFile << magicNumber << endl;
	outFile << numberOfColumns << " ";
	outFile << numberOfRows << endl;
	outFile << maxColorVal << endl;

	int bufferArray[BUFFER_SIZE];
	int oneValue;
	int count = 0;
	int breakStep;
	bool breakTriggered = false;
	while (true) {
		for (int i = 0; i < columnLength; ++i) {
			imageFile >> oneValue;
			if (!imageFile) {
				breakTriggered = true;
				breakStep = i;
				break;
			}
			bufferArray[i] = oneValue;
		}
		manipulateImage(bufferArray, columnLength, maxColorVal, options, RANDOM_RANGE);
		for (int i = 0; i < columnLength; ++i) {
			if (breakTriggered && (i == breakStep)) {
				break;
			}
			outFile << bufferArray[i];
			if (((i + 1) % 3) == 0) {
				outFile << "  ";
			} else {
				outFile << " ";
			}
		}
		outFile << endl;
		++count;
		if (breakTriggered) {
			break;
		}
	}
	imageFile.close();
	outFile.close();
	flip_vertical(options, outFileName);
	cout << "Done!" << endl;
	cout << outFileName << " created." << endl;
	return 0;
}
// Negates the red number of each pixel.
void negate_red(int bufferArray[], int columnLength, int maxColorVal) {
	for (int i = 0; i < (columnLength / 3); ++i) {
		bufferArray[i * 3] = maxColorVal - bufferArray[i * 3];
	}
}
// Negates the green number of each pixel.
void negate_green(int bufferArray[], int columnLength, int maxColorVal) {
	for (int i = 0; i < (columnLength / 3); ++i) {
		bufferArray[i * 3 + 1] = maxColorVal - bufferArray[i * 3 + 1];
	}
}
// Negates the blue number of each pixel.
void negate_blue(int bufferArray[], int columnLength, int maxColorVal) {
	for (int i = 0; i < (columnLength / 3); ++i) {
		bufferArray[i * 3 + 2] = maxColorVal - bufferArray[i * 3 + 2];
	}
}
// Flips each row horrizontally.
void flip_horizontal(int bufferArray[], int columnLength) {
	int tempVal;
	for (int i = 0; i < 3; ++ i) {
		for (int j = 0; j < (columnLength / 6); ++j) {
			tempVal = bufferArray[i + (j * 3)];
			bufferArray[i + (j * 3)] = bufferArray[columnLength + i - ((j + 1) * 3)];
			bufferArray[columnLength + i - ((j + 1) * 3)] = tempVal;
		}
	}
}
// Sets each pixel value to the average of the three.
void grey_scale(int bufferArray[], int columnLength) {
	int sumOfAll = 0;
	int average;
	for (int i = 0; i < (columnLength / 3); ++i) {
		for (int j = 0; j < 3; ++j) {
			sumOfAll += bufferArray[(i * 3) + j];
		}
		average = sumOfAll / 3;
		for (int j = 0; j < 3; ++j) {
			bufferArray[(i * 3) + j] = average;
		}
		sumOfAll = 0;
	}
}
// Sets the red value to zero.
void flatten_red(int bufferArray[], int columnLength) {
	for (int i = 0; i < (columnLength / 3); ++i) {
		bufferArray[i * 3] = 0;
	}
}
// Sets the green value to zero.
void flatten_green(int bufferArray[], int columnLength) {
	for (int i = 0; i < (columnLength / 3); ++i) {
		bufferArray[i * 3 + 1] = 0;
	}
}
// Sets the blue value to zero.
void flatten_blue(int bufferArray[], int columnLength) {
	for (int i = 0; i < (columnLength / 3); ++i) {
		bufferArray[i * 3 + 2] = 0;
	}
}
// Blures the image horizontally by averaging nearby values.
void horizontal_blur(int bufferArray[], int columnLength) {
	int leftValue;
	int rightValue;
	int oldValue;
	int newValue;
	for (int i = 0; i < 3; ++ i) {
		for (int j = 0; j < (columnLength / 3); ++j) {
			if (j > 0) {
				leftValue = oldValue;
			}
			oldValue = bufferArray[(j * 3) + i];
			if ((j == 0) && (j == ((columnLength / 3) - 1))) {
				newValue = oldValue;
			} else if (j == 0) {
				rightValue = bufferArray[((j + 1) * 3) + i];
				newValue = (oldValue + rightValue) / 2;
			} else if (j == ((columnLength / 3) - 1)) {
				newValue = (oldValue + leftValue) / 2;
			} else {
				rightValue = bufferArray[((j + 1) * 3) + i];
				newValue = (oldValue + leftValue + rightValue) / 3;
			}
			bufferArray[(j * 3) + i] = newValue;
		}
	}
}
// Takes each value to its extreme, lower values become zero and higher values become theri cap.
void extreme_contrast(int bufferArray[], int columnLength, int maxColorVal) {
	for (int i = 0; i < columnLength; ++i) {
		if (bufferArray[i] > (maxColorVal / 2)) {
			bufferArray[i] = maxColorVal;
		} else {
			bufferArray[i] = 0;
		}
	}
}
// Adds random numbers (+ or -) to each value in the image, simulating noise.
void random_noise(int bufferArray[], int columnLength, int maxColorVal, const int RANDOM_RANGE) {
	int newValue;
	int modifier;
	for (int i = 0; i < columnLength; ++i) {
		modifier = rand() % (RANDOM_RANGE * 2 + 1) - RANDOM_RANGE; // Between -RR and +RR
		newValue = bufferArray[i] + modifier;
		if (newValue > maxColorVal) {
			newValue = maxColorVal;
		} else if (newValue < 0) {
			newValue = 0;
		}
		bufferArray[i] = newValue;
	}
}
// Manipulates the image as specified by the user.
void manipulateImage(int bufferArray[], int columnLength, int maxColorVal, bool options[], const int RANDOM_RANGE) {
	if (options[0]) {
		grey_scale(bufferArray, columnLength);
	}
	if (options[1]) {
		flip_horizontal(bufferArray, columnLength);
	}
	if (options[2]) {
		negate_red(bufferArray, columnLength, maxColorVal);
	}
	if (options[3]) {
		negate_green(bufferArray, columnLength, maxColorVal);
	}
	if (options[4]) {
		negate_blue(bufferArray, columnLength, maxColorVal);
	}
	if (options[5]) {
		flatten_green(bufferArray, columnLength);
		flatten_blue(bufferArray, columnLength);
	}
	if (options[6]) {
		flatten_red(bufferArray, columnLength);
		flatten_blue(bufferArray, columnLength);
	}
	if (options[7]) {
		flatten_red(bufferArray, columnLength);
		flatten_green(bufferArray, columnLength);
	}
	if (options[8]) {
		horizontal_blur(bufferArray, columnLength);
	}
	if (options[9]) {
		extreme_contrast(bufferArray, columnLength, maxColorVal);
	}
	if (options[10]) {
		random_noise(bufferArray, columnLength, maxColorVal, RANDOM_RANGE);
	}
}

// Flips image vertically.
void flip_vertical(bool options[], string outFileName) {
	if(options[11] == true) {
		string magicNumber;
		int numberOfColumns;
		int numberOfRows;
		int maxColorVal;
		ifstream outFile(outFileName.c_str()); // Open file and call it imageFile.
		if (!outFile) {
			cerr << "Error opening file for vertical flip" << endl;
			exit(1);
		}
		outFile >> magicNumber;
		outFile >> numberOfColumns;
		outFile >> numberOfRows;
		outFile >> maxColorVal;

		int rowLength = numberOfColumns * 3;
		int **storedValues;
		storedValues = new int* [numberOfRows];
		for (int i = 0; i < numberOfRows; ++i) {
			storedValues[i] = new int [rowLength];
			for (int j = 0; j < rowLength; ++j) {
				outFile >> storedValues[i][j];
			}
		}
		outFile.close();

		int tempVal;
		for (int i = 0; i < rowLength; ++i) {
			for (int j = 0; j < (numberOfRows / 2); ++j) {
				tempVal = storedValues[j][i];
				storedValues[j][i] = storedValues[numberOfRows - (j + 1)][i];
				storedValues[numberOfRows - (j + 1)][i] = tempVal;
			}
		}
		// Overwrites output file with new contents
		ofstream newOutFile(outFileName.c_str());
		newOutFile << magicNumber << endl;
		newOutFile << numberOfColumns << " ";
		newOutFile << numberOfRows << endl;
		newOutFile << maxColorVal << endl;
		for (int i = 0; i < numberOfRows; ++i) {
			for (int j = 0; j < rowLength; ++j) {
				newOutFile << storedValues[i][j];
				if ((j + 1) % 3 == 0) {
					newOutFile << "  ";
				} else {
					newOutFile << " ";
				}
			}
			newOutFile << endl;
		}
		newOutFile.close();
	}
}