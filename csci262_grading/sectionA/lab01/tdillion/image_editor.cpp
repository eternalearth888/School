#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* IMAGE MODIFICATION FUNCTION DEFINITIONS */
void negate_red(int ppmBuffer[], int &width, int &maxColor) {
	for (int i = 0; i < width; i++) {
		ppmBuffer[3 * i] = maxColor - ppmBuffer[3 * i];
	}
}

void negate_green(int ppmBuffer[], int &width, int &maxColor) {
	for (int i = 0; i < width; i++) {
		ppmBuffer[1 + (3 * i)] = maxColor - ppmBuffer[1 + (3 * i)];
	}
}

void negate_blue(int ppmBuffer[], int &width, int &maxColor) {
	for (int i = 0; i < width; i++) {
		ppmBuffer[2 + (3 * i)] = maxColor - ppmBuffer[2 + (3 * i)];
	}
}

void flatten_red(int ppmBuffer[], int &width) {
	for (int i = 0; i < width; i++) {
		ppmBuffer[3 * i] = 0;
	}
}

void flatten_green(int ppmBuffer[], int &width) {
	for (int i = 0; i < width; i++) {
		ppmBuffer[1 + (3 * i)] = 0;
	}
}

void flatten_blue(int ppmBuffer[], int &width) {
	for (int i = 0; i < width; i++) {
		ppmBuffer[2 + (3 * i)] = 0;
	}
}

void grey_scale(int ppmBuffer[], int &width) {
	int reds[width],
		greens[width],
		blues[width];
	for (int i = 0; i < width; i++) {
		reds[i] = ppmBuffer[3 * i];
		greens[i] = ppmBuffer[1 + (3 * i)];
		blues[i] = ppmBuffer[2 + (3 * i)];
	}
	for (int i = 0; i < width; i++) {
		reds[i] = greens[i] = blues[i] =
		(reds[i] + greens[i] + blues[i]) / 3;
	}
	for (int i = 0; i < width; i++) {
		ppmBuffer[3 * i] = reds[i];
		ppmBuffer[1 + (3 * i)] = greens[i];
		ppmBuffer[2 + (3 * i)] = blues[i];
	}
}

/*

ppmBuffer
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14
R1 G1 B1 R2 G2 B2 R3 G3 B3 R4 G4 B4 R5 G5 B5

*/

void flip_horizontal(int ppmBuffer[], int &width) {
	int reds[width],
		greens[width],
		blues[width];

	for (int i = 0; i < width; i++) {
		reds[i] = ppmBuffer[3 * i];
		greens[i] = ppmBuffer[1 + (3 * i)];
		blues[i] = ppmBuffer[2 + (3 * i)];
	}

	for (int i = 0, j = width - 1; i < width; i++, j--) {
		ppmBuffer[3 * i] = reds[j];
		ppmBuffer[1 + (3 * i)] = greens[j];
		ppmBuffer[2 + (3 * i)] = blues[j];
	}
}

/* END IMAGE MODIFICATION FUNCTION DEFINITIONS */

int main() {
	string inFileName, outFileName;
	string ppmType;
	// buffer size
	const int BUFFER_SIZE = 3000;
	// buffer
	int *ppmBuffer = new int[BUFFER_SIZE];
	// user interface
	const int NUM_ACTIONS = 8;
	char actions[NUM_ACTIONS];
	
	// size of a ppm header
	const int HEADER_SIZE = 4;
	// pixel dimensions of image
	int width, height, maxColor;


	// get filename, open file
	cout << "Enter the source filename (.ppm): "; cin >> inFileName;
	ifstream inFile(inFileName.c_str());
	if (!inFile) {
		cout << "The file \"" << inFileName << "\" failed to open." << endl << endl;
		return -1;
	}
	/* USER INTERFACE */
	cout << "File \"" << inFileName << "\" succesfully opened." << endl << endl;
	cout << "1\tNegate Red" << endl;
	cout << "2\tNegate Green" << endl;
	cout << "3\tNegate Blue" << endl;
	cout << "4\tFlatten Red" << endl;
	cout << "5\tFlatten Green" << endl;
	cout << "6\tFlatten Blue" << endl;
	cout << "7\tGrey Scale" << endl;
	cout << "8\tFlip Horizontal" << endl;
	cout << "Actions (respond y/n):" << endl;

	for (int i = 1; i <= NUM_ACTIONS; i++) {
		cout << i << ": "; cin >> actions[i - 1];
	}

	/* END USER INTERFACE */
	int header[HEADER_SIZE];
	// get the header
	for (int i = 0; i < HEADER_SIZE; i++) {
		if (i == 0) {
			// get the ppm type (P3)
			inFile >> ppmType;
		} else {
			inFile >> header[i];
		}
	}
	// get width & height from the header
	width = header[1];
	height = header[2];
	maxColor = header[3];

	// make sure the buffer can handle the image
	if (width > (BUFFER_SIZE / 3)) {
		cout << "The image is too wide for the buffer to handle. Aborting program." << endl;
		return -1;
	}

	cout << "Enter the resulting file name: "; cin >> outFileName;
	ofstream outFile(outFileName.c_str());
	if (!outFile) {
		cout << "The file \"" << outFileName << "\" could not be created." << endl;
	}
	
	// write the header to the new file
	outFile << ppmType << endl;
	outFile << width << ' ' << height << endl;
	outFile << maxColor << endl;

while (inFile.good()) {

	// get row from file
	for (int i = 0; i < 3 * width; i++) {
		inFile >> ppmBuffer[i];
	}

	/* IMAGE MODIFICATON FUNCTIONS */

	if (actions[0] == 'y' || actions[0] == 'Y') {
		negate_red(ppmBuffer, width, maxColor);
	}
	if (actions[1] == 'y' || actions[1] == 'Y') {
		negate_green(ppmBuffer, width, maxColor);
	}
	if (actions[2] == 'y' || actions[2] == 'Y') {
		negate_blue(ppmBuffer, width, maxColor);
	}
	if (actions[3] == 'y' || actions[3] == 'Y') {
		flatten_red(ppmBuffer, width);
	}
	if (actions[4] == 'y' || actions[4] == 'Y') {
		flatten_green(ppmBuffer, width);
	}
	if (actions[5] == 'y' || actions[5] == 'Y') {
		flatten_blue(ppmBuffer, width);
	}
	if (actions[6] == 'y' || actions[6] == 'Y') {
		grey_scale(ppmBuffer, width);
	}
	if (actions[7] == 'y' || actions[7] == 'Y') {
		flip_horizontal(ppmBuffer, width);
	}

	/* END IMAGE MODIFICATION FUNCTIONS */
		
	// write the buffer content to the new file
	for (int i = 0; i < 3 * width; i++) {
		outFile << ppmBuffer[i] << ' ';
	}
	// go to next row of output
	outFile << endl;
}

	cout << endl << endl;
	cout << "File \"" << outFileName << "\" was created successfully!" << endl;
	cout << "ppmType: " << ppmType << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "Max Color Value: " << maxColor << endl;
	inFile.close();
	outFile.close();
	delete [] ppmBuffer; ppmBuffer = NULL;
	return 0;
}