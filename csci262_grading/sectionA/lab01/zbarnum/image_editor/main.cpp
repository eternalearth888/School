#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

//NAME: Zachary Barnum

// My program is a mess Ive been unable to make it to help this week due to labs for other classes and work, I hope that what I have done 
// is enough to get some credit on this lab.... my functions except for greyscale all worked in the cout<< window but my code is such a mess at 
// this point that im not sure how to allocate those to a new variable. My buffer works but not for the entire file and I know that I have completed
// the majority of the assignment and Im just missing a few stupid details. I muscled my way through this assignment by myself despite my horrific schedule and 
// adding this class late.

int charToInt(char inputChar);
int negate_red(int r, int color);
int negate_blue(int b, int color);
int negate_green(int g, int color);
void flip_horizontal(int col, int *pixArray);
int grey_scale(int r, int g, int b);
int flatten_red(int r);
int flatten_blue(int b);
int flatten_green(int g);

int main() {
	
	string MyFile;
	
	cout << "Please choose an input ppm file: ";
	cin >> MyFile;

	ifstream InFile(MyFile);

	if (!InFile) {
		cerr << "INFILE CORRUPT" << endl;
		system("PAUSE");
	}

	string NewFile;

	cout << "Please choose an output file name:";
	cin >> NewFile;

	ofstream OutFile(NewFile);

	if (!OutFile) {
		cerr << "OUTFILE CORRUPT";
		system("PAUSE");
	}
	const int DATA = 3000;
	int rows = 0, columns = 0, maxColorIndex = 0, pixelValue = 0, r, g, b;
	string inDataArray;
	int pixelArray[DATA];
	int colorValue = 0;
	int count = 0;
	char c = ' ';
	
	char n_red;
	char n_blue;
	char n_green;
	char f_horizontal;
	char g_scale;
	char f_red;
	char f_blue;
	char f_green;

	cout << "Here are your choices:\n[1]Convert to greyscale [2]Flip horizontally\n\n[3]Negative of Red      [4]Negative of Green  [5]Negative of Blue\n\n[6]Only Reds            [7]Only Greens        [8]Only Blues\n\n";
	cout << "Do You want [1]: ";
	cin >> g_scale;
	cout << "Do You want [2]: ";
	cin >> f_horizontal;
	cout << "Do You want [3]: ";
	cin >> n_red;
	cout << "Do You want [4]: ";
	cin >> n_green;
	cout << "Do You want [5]: ";
	cin >> n_blue;
	cout << "Do You want [6]: ";
	cin >> f_red;
	cout << "Do You want [7]: ";
	cin >> f_green;
	cout << "Do You want [8]: ";
	cin >> f_blue;

	while (InFile) {
		inDataArray = "";
		while(c != '\n') { 
			InFile.get(c);
			if (c != '\n') {
				inDataArray.push_back(c);
			}else {
				InFile.get(c);
			}
		}

		c = ' ';
		//cout << "inDataArray: " << inDataArray << endl;

		if (count == 0) {
			OutFile << inDataArray[0] << inDataArray[1] << endl;//sets P3
		}

		else if (count == 1) {//Sets rows and columns
			int counter = 0;
			int startIndex = 0;
				for (int i = 0; i < 2; i++) {
					while(inDataArray[counter] != ' ' && inDataArray[counter] != '\n') {
						counter++;
					}

					if (i == 0) {
						while ((counter - startIndex) != 0) {
							rows += charToInt(inDataArray[startIndex]) * pow(10.0,counter - startIndex - 1);
							startIndex++;
						}
					}
					else {
						counter+=2;
						startIndex++;
						while ((counter - startIndex) >= 0) {
							columns += charToInt(inDataArray[startIndex]) * pow(10.0,counter - startIndex);
							startIndex++;
						}
					}
				}

			OutFile << rows << ' ' << columns << endl;
		}
		else if (count == 2) {// sets line 3 MAX color
			maxColorIndex = charToInt(inDataArray[0]) * 100 + charToInt(inDataArray[1]) * 10 + charToInt(inDataArray[2]);
			OutFile << maxColorIndex << endl;
		}else {
				int counter = 0;
				//int *pointer;
				int startIndex = 0;
				while (startIndex < rows * columns * 3) {
					while(inDataArray[counter] != ' ' && inDataArray[counter] != '\n') {
						counter++;
					}
					colorValue = 0;
					while (counter - startIndex >= 0) {
						colorValue += charToInt(inDataArray[startIndex]) * pow(10.0,counter - startIndex - 1); //creates an integer value for char by using the ASCII index and subtracting 48
						startIndex++;
					}
					pixelArray[pixelValue] = colorValue + 2;

		//greyscale function
					if (g_scale == 'Y' || g_scale == 'y') {
						if (pixelValue % 3 == 0) {
							pixelArray[pixelValue] = grey_scale(pixelArray[pixelValue],pixelArray[pixelValue + 1],pixelArray[pixelValue + 2]);
							//*pointer = pixelArray[pixelValue]; 
						}
					}
		// flip function
					if (f_horizontal == 'Y' || f_horizontal == 'y') {
						flip_horizontal(columns * 3, &pixelArray[0]);
						//*pointer = pixelArray[pixelValue]; 

					}
		//negative functions
					if (n_red == 'Y' || n_red == 'y') {
						if (pixelValue % 3 == 0) {
							pixelArray[pixelValue] = negate_red(pixelArray[pixelValue],maxColorIndex);
							//*pointer = pixelArray[pixelValue]; 
						}
					}
					if (n_green == 'Y' || n_green == 'y') {
							if (pixelValue % 3 == 1) {
							pixelArray[pixelValue] = negate_green(pixelArray[pixelValue],maxColorIndex);
							//*pointer = pixelArray[pixelValue]; 
						}
					}
					if (n_blue == 'Y' || n_blue == 'y') {
							if (pixelValue % 3 == 2) {
							pixelArray[pixelValue] = negate_blue(pixelArray[pixelValue],maxColorIndex);
							//*pointer = pixelArray[pixelValue]; 
						}
					}

		//flatten functions
					if (f_red == 'Y' || f_red == 'y') {
						if (pixelValue % 3 == 0) {
							pixelArray[pixelValue] = flatten_red(pixelArray[pixelValue]);
							//*pointer = pixelArray[pixelValue]; 
						}
					}

					if (f_green == 'Y' || f_green == 'y') {
						if (pixelValue % 3 == 1) {
							pixelArray[pixelValue] = flatten_green(pixelArray[pixelValue]);
							//*pointer = pixelArray[pixelValue]; 
						}
					}
					if (n_blue == 'Y' || n_blue == 'y') {
						if (pixelValue % 3 == 2) {
							pixelArray[pixelValue] = flatten_blue(pixelArray[pixelValue]);
							//*pointer = pixelArray[pixelValue]; 
						}
					}
					OutFile << pixelArray[pixelValue];
		
					pixelValue++;
				
					if(inDataArray[counter] = ' ') {
						counter++;
						OutFile << ' ';
					}else if(inDataArray[counter] = '\n') {
						counter++;
						OutFile << '\n';
					}
				}
		}

		count ++;
	}
	InFile.close();
	OutFile.close();

	cout << NewFile << " created!" << endl;


	system("PAUSE");
	return 0;
}

int charToInt(char inputChar) {
	return inputChar - 48;
}
int negate_red(int r, int color) {
	return color - r;
}
int negate_blue(int b, int color) {
	return color - b;
}
int negate_green(int g, int color) {
	return color - g;
}

void flip_horizontal(int col, int *pixArray) {
	int temp, frontIndex = 0, backIndex = col;
	while(frontIndex < backIndex) {
		temp = *pixArray+frontIndex;
		*(pixArray+frontIndex) = *(pixArray+backIndex);
		*(pixArray+backIndex) = temp;
		frontIndex++;
		backIndex--;
	}

}
int grey_scale(int r, int g, int b) {
	return(r+g+b)/3;
}
int flatten_red(int r) {
	return r = 0;
}
int flatten_blue(int b) {
	return b = 0;
}
int flatten_green(int g) {
	return g = 0;
}