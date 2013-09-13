/*  Jeremy Alvis
	CSCI262 - 12:00

	Includes all 4 bonus functions.
*/

#include <string>
#include <iostream>

#include <fstream>

using namespace std;

const int MAX_SIZE = 3000;
string fileNameIn, fileNameOut, type, input;
int *temp2, x, temp, currentNumber;
bool run = false;
ifstream inFile;
ofstream outFile;

// Flip value of red color
int negate_red(int red, int maxColor) {
	red = maxColor - red;
	return red;
}

// Flip value of green color
int negate_green(int green, int maxColor) {
	green = maxColor - green;
	return green;
}

// Flip value of blue color
int negate_blue(int blue, int maxColor) {
	blue = maxColor - blue;
	return blue;
}

// Flip image horizontally
int* flip_horizontal(int* array, int length) {
	x = length - 1;
	temp2 = new int[length];
	for(int i = 0; i <= length - 1; i = i + 3) {

		temp2[i] = array[x - 2];
		temp2[i + 1] = array[x - 1];
		temp2[i + 2] = array[x];

		x = x - 3;
	}
	x = 0;

	for(int i = 0; i <= length - 1; i++) {
		array[i] = temp2[i];
	}
	delete [] temp2;
	return array;
}

// Change image to greyscale
int grey_scale(int red, int green, int blue) {
	int grey = (red + green + blue) / 3;
	return grey;
}

// Make red 0
int flatten_red(int red) {
	return 0;
}

// Make green 0
int flatten_green(int green) {
	return 0;
}

// Make blue 0
int flatten_blue(int blue) {
	return 0;
}

// Change contrast
int extreme_contrast(int color, int maxColor) {
	if(color >= (maxColor / 2)) {
		return maxColor;
	} else {
		return 0;
	}
}

// Random noise
int random_noise(int color, int input, int maxColor) {
	int randomNumber = rand() % input;
	int plusOrMinus = rand() % 2 + 1;

	if(plusOrMinus == 1) {
		color += randomNumber;
	} else {
		color -= randomNumber;
	}

	if(color > maxColor) {
		return maxColor;
	} else if(color < 0) {
		return 0;
	} else {
		return color;
	}
}

int horizontal_blur(int a, int b, int c) {
	temp = a + b + c;
	temp = temp / 3;
	return temp;
}

void createInFile(string fileName, ifstream& file) {
	// Create input file
	file.open(fileName);

	// Test and make sure the file can be opened
	if(!file) {
		cout << "The file was unable to be opened. (line 121)" << endl;
		system("pause");
		exit(1);
		return;
	}
}

void createOutFile(string fileName, ofstream& file) {
	// Create output file
	file.open(fileName);

	// Test and make sure the file can be opened
	if(!file) {
		cout << "The file was unable to be created. (line 134)" << endl;
		system("pause");
		exit(2);
		return;
	}
}

void printQuestion(string output) {
	cout << output << endl;
}

// Run the image editing algorithm. Value is only used for option 10 (random noise)
void editImage(int number, int value) {
	
	//Create the file
	if(run) {
		createInFile(fileNameOut, inFile);
		createOutFile("temp.ppm", outFile);
	} else {
		createInFile(fileNameIn, inFile);
		createOutFile(fileNameOut, outFile);
	}

	inFile >> type;
	if(type != "p3" && type != "P3") {
		cout << "The file is corrupt. (line 159)" << endl;
		system("pause");
		exit(3);
		return;
	}
	
	cout << "Working";
	outFile << type << endl;

	int columns, rows, maxColor;

	inFile >> columns;
	inFile >> rows;
	inFile >> maxColor;

	outFile << columns << " " << rows << endl;
	outFile << maxColor << endl;

	if(columns > MAX_SIZE) {
		cout << "The file is too big. (line 178)" << endl;
		system("pause");
		exit(4);
		return;
	}

	int *arr;
	int **arr2D;
	arr = new int[columns * 3];
	arr2D = new int*[rows];
	for (int i = 0; i < rows; i++) {
		arr2D[i] = new int[columns * 3];
	}

	currentNumber = 0;

	while(!inFile.eof()) {
		if(number != 12) {
			for(int c = 0; c < columns * 3; c++) {
				inFile >> arr[c];
			}
		} else {
			for(int r = 0; r < rows; r++) {
				for(int c = 0; c < columns * 3; c++) {
					inFile >> arr2D[r][c];
				}
			}
		}
		
		if(currentNumber % 10 == 0) {
			cout << ".";
		}
		if(number == 2) {
			arr = flip_horizontal(arr, columns * 3);
		}
		if(number != 12) {
			for(int c = 0; c < columns * 3; c = c + 3) {
				if(number == 1) {
					temp = grey_scale(arr[c], arr[c + 1], arr[c + 2]);
					arr[c] = temp;
					arr[c + 1] = temp;
					arr[c + 2] = temp;
				} else if(number == 3) {
					arr[c] = negate_red(arr[c], maxColor);
				} else if(number == 4) {
					arr[c + 1] = negate_green(arr[c + 1], maxColor);
				} else if(number == 5) {
					arr[c + 2] = negate_blue(arr[c + 2], maxColor);
				} else if(number == 6) {
					arr[c + 1] = flatten_green(arr[c + 1]);
					arr[c + 2] = flatten_blue(arr[c + 2]);
				} else if(number == 7) {
					arr[c] = flatten_red(arr[c]);
					arr[c + 2] = flatten_blue(arr[c + 2]);
				} else if(number == 8) {
					arr[c] = flatten_red(arr[c]);
					arr[c + 1] = flatten_green(arr[c + 1]);
				} else if(number == 9) {
					arr[c] = extreme_contrast(arr[c], maxColor);
					arr[c + 1] = extreme_contrast(arr[c + 1], maxColor);
					arr[c + 2] = extreme_contrast(arr[c + 2], maxColor);
				} else if(number == 10) {
					arr[c] = random_noise(arr[c], value, maxColor);
					arr[c + 1] = random_noise(arr[c + 1], value, maxColor);
					arr[c + 2] = random_noise(arr[c + 2], value, maxColor);
				} else if(number == 11) {
					if(c == 0) {
						arr[c] = horizontal_blur(arr[c], arr[c + 3], arr[c + 3]);
						arr[c + 1] = horizontal_blur(arr[c + 1], arr[c + 4], arr[c + 4]);
						arr[c + 2] = horizontal_blur(arr[c + 2], arr[c + 5], arr[c + 5]);
					} else if(c == (columns * 3) - 3) {
						arr[c] = horizontal_blur(arr[c], arr[c - 3], arr[c - 3]);
						arr[c + 1] = horizontal_blur(arr[c + 1], arr[c - 2], arr[c - 2]);
						arr[c + 2] = horizontal_blur(arr[c + 2], arr[c - 1], arr[c - 1]);
					} else {
						arr[c] = horizontal_blur(arr[c], arr[c - 3], arr[c + 3]);
						arr[c + 1] = horizontal_blur(arr[c + 1], arr[c + 4], arr[c - 2]);
						arr[c + 2] = horizontal_blur(arr[c + 2], arr[c + 5], arr[c - 1]);
					}
				} else {

				}
				outFile << arr[c] << " " << arr[c + 1] << " " << arr[c + 2] << "  ";
			}
			outFile << endl;
			currentNumber++;
		} else {
			for(int r = rows - 1; r >= 0; r--) {
				for(int c = 0; c < columns * 3; c = c + 3) {
					outFile << arr2D[r][c] << " " << arr2D[r][c + 1] << " " << arr2D[r][c + 2] << " ";
				}
				outFile << endl;
				currentNumber++;
			}
		}	
	}
	cout << endl;

	// Deallocate the array
	delete [] arr;

	for (int i = 0; i < rows; i++) {
		delete [] arr2D[i];
	}
	
	delete [] arr2D;

	inFile.close();
	outFile.close();

	if(run) {
		ifstream src("temp.ppm", ios::binary);
		ofstream dst(fileNameOut, ios::binary);

		dst << src.rdbuf();

		// Close the files
		src.close();
		dst.close();

		if( remove("temp.ppm") != 0) {
			cout << "Error deleting temp file. (line 299)" << endl;
			system("pause");
			exit(6);
			return;
		}
	}
	run = true;
}

void printQuestionLoop(string output, int number) {
	do {
		printQuestion(output);
		cin >> input;
	} while(input != "y" && input != "n" && input != "Y" && input != "N");

	if(input == "y" || input == "Y") {
		if(number == 10) {
			int value;
			printQuestion("What value do you want to use for the random number?");
			cin >> value;
			editImage(number, value);
		} else {
			editImage(number, 0);
		}
	}
}

int main() {
	// Ask for and store the input filename
	printQuestion("Please enter the name of the image file:");
	cin >> fileNameIn;

	// Ask and store the output filename
	printQuestion("Please enter the name of the output file: ");
	cin >> fileNameOut;

	// Print list of choices for operations
	printQuestion("Here are your choices:");
	printQuestion("[1]  convert to greyscale [2]  flip horizontally");
	printQuestion("[3]  negative of red [4]  negative of green");
	printQuestion("[5]  negative of blue [6]  just the reds");
	printQuestion("[7]  just the greens   [8]  just the blues");
	printQuestion("[9]  extreme contrast   [10]  random noise");
	printQuestion("[11]  horizontal blur   [12]  flip vertically");
	
	//Check each operation
	printQuestionLoop("Do you want [1]? (y/n)", 1);
	printQuestionLoop("Do you want [2]? (y/n)", 2);
	printQuestionLoop("Do you want [3]? (y/n)", 3);
	printQuestionLoop("Do you want [4]? (y/n)", 4);
	printQuestionLoop("Do you want [5]? (y/n)", 5);
	printQuestionLoop("Do you want [6]? (y/n)", 6);
	printQuestionLoop("Do you want [7]? (y/n)", 7);
	printQuestionLoop("Do you want [8]? (y/n)", 8);
	printQuestionLoop("Do you want [9]? (y/n)", 9);
	printQuestionLoop("Do you want [10]? (y/n)", 10);
	printQuestionLoop("Do you want [11]? (y/n)", 11);
	printQuestionLoop("Do you want [12]? (y/n)", 12);

	cout << "The file: " << fileNameOut << " has been created." << endl;

	system("pause");
	return 0;
}

//Programming is Magic