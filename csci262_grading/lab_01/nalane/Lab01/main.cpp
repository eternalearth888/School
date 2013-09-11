/*********************************************************************
*********************Created by Nathaniel Lane************************
*********************************************************************/

#include "image.h"
#include <iostream>

using namespace std;

int main() {
	// Determine which operations we want to perform.
	bool greyscale = false;
	bool flip = false;
	bool negateRed = false;
	bool negateGreen = false;
	bool negateBlue = false;
	bool flattenRed = false;
	bool flattenGreen = false;
	bool flattenBlue = false;
	bool extremeContrast = false;
	bool horizontalBlur = false;

	// Names of input and output files.
	string input;
	string output;

	// Records user's decision about the edits he wishes to make.
	string decision;

	// Create the image editor.
	image file;

	cout << "Portable Pixmap (PPM) Image Editor" << endl << endl;

	do {
		// Gather input and output filenames
		cout << "Enter name of image file: ";
		cin >> input;
		file.setInput(input);
	
		cout << "Enter name of output file: ";
		cin >> output;
		file.setOutput(output);

		// Give the user free will.
		cout << endl << "Here are your choices:" << endl;
	    cout << "[1]  convert to greyscale\n[2]  flip horizontally\n[3]  negative of red\n[4]  negative of green\n[5]  negative of blue\n[6]  flatten the reds\n[7]  flatten the greens\n[8]  flatten the blues\n[9]  extreme contrast\n[10]  horizontal blur\n";

		// Process his decisions.
		do {
			cout << "Do you want [1]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			greyscale = true;
		}

		do {
			cout << "Do you want [2]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			flip = true;
		}

		do {
			cout << "Do you want [3]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			negateRed = true;
		}

		do {
			cout << "Do you want [4]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			negateGreen = true;
		}

		do {
			cout << "Do you want [5]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			negateBlue = true;
		}

		do {
			cout << "Do you want [6]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			flattenRed = true;
		}

		do {
			cout << "Do you want [7]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			flattenGreen = true;
		}

		do {
			cout << "Do you want [8]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			flattenBlue = true;
		}

		do {
			cout << "Do you want [9]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			extremeContrast = true;
		}

		do {
			cout << "Do you want [10]? (y/n) ";
			cin >> decision;
		} while (decision != "y" && decision != "Y" && decision != "n" && decision != "N");
		if(decision == "y" || decision == "Y") {
			horizontalBlur = true;
		}

	} while (!file.copy(negateRed, negateGreen, negateBlue, flip, greyscale, flattenRed, flattenGreen, flattenBlue, extremeContrast, horizontalBlur));

	return 0;
}