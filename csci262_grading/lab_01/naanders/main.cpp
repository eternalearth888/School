//Name: Nathan Anderson
//Collaborator: Garrett Wiese
//Collaborator: Christen Boyer
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

//Variables!
string input, output;
string magicNumber = "";
const int INTEGER_COUNT = 3000;
int myArray[INTEGER_COUNT];
int rows = 1, columns = 1, maxColor = 255;
int currentPixel = 0;
int pixelCount = 0;
string answer1, answer2, answer3, answer4, answer5, answer6, answer7, answer8;

//Functions!
//Negate
void negate_red() {
	for (int i=0; i<(columns*3); i+=3) {
		myArray[i] = abs(255 - myArray[i]);
	}
}

void negate_green() {
	for (int i=1; i<(columns*3); i+=3) {
		myArray[i] = abs(255 - myArray[i]);
	}
}

void negate_blue() {
	for (int i=2; i<(columns*3); i+=3) {
		myArray[i] = abs(255 - myArray[i]);
	}
}

//Flip
//For the life of me, I cannot figure out what I'm doing wrong!
//The mirrored image is being overlapped 3 times, and I cannot
//find out why.  Some explanation would be awesome :D
void flip_horizontal() {
	int j = 0;
	int newArray[3000];
	for (int i=(columns*3)-1; i>=0; i-=3) {
		newArray[j] = myArray[i-2];
		newArray[j+1] = myArray[i-1];
		newArray[j+2] = myArray[i];
		j+=3;
	}
	for (int i=0; i<=(columns*3); i++) {
		myArray[i] = newArray[i];
	}
}

//Greyscale
void grey_scale() {
	double avg = 0;
	for (int i=0; i<(columns*3); i++) {
		avg = ((myArray[i])+(myArray[i+1])+(myArray[i+2]))/3;
		myArray[i] = avg;
		myArray[i+1] = avg;
		myArray[i+2] = avg;
	}
}

//Flatten
void flatten_red() {
	for (int i=0; i<(columns*3); i+=3) {
		myArray[i] = 0;
	}
}

void flatten_green() {
	for (int i=1; i<(columns*3); i+=3) {
		myArray[i] = 0;
	}
}

void flatten_blue() {
	for (int i=2; i<(columns*3); i+=3) {
		myArray[i] = 0;
	}
}

//Main!
int main() {

	cout << "Portable Pixmap (PPM) inFile Editor!\n\n";
	//Managing input file
	cout << "Enter name of inFile file: ";
	cin >> input;
	ifstream inFile(input);
	if (!inFile) {
		cerr << "There was an error reading the file." << endl;
		system("pause");
		exit(1);
	}
	//Managing output file
	cout << "Enter name of output file: ";
	cin >> output;
	cout << output << " created!" << endl << endl;
	ofstream outFile(output);
	if (!outFile) {
		cerr << "There was an error writing the file." << endl;
		system("pause");
		exit(1);
	}

	//Determining the magic number, the number of rows, columns, and the max color
	inFile >> magicNumber >> rows >> columns >> maxColor;
	pixelCount = rows * columns;

	//sending the magic number, rows, columns, and max color to the output file
	outFile << magicNumber << endl << rows << " " << columns << endl << maxColor << endl;

	cout << "What would you like to do to the image?" << endl << endl;
	cout << "Here are your choices:" << endl;
	cout << "[1]  convert to greyscale          [5]  negative of blue" << endl;
	cout << "[2]  flip horizontally (mirror)    [6]  just the reds" << endl;
	cout << "[3]  negative of red               [7]  just the greens" << endl;
	cout << "[4]  negative of green             [8]  just the blues" << endl << endl;

	cout << "Do you want [1]? (y/n) ";
	cin >> answer1;
	cout << "Do you want [2]? (y/n) ";
	cin >> answer2;
	cout << "Do you want [3]? (y/n) ";
	cin >> answer3;
	cout << "Do you want [4]? (y/n) ";
	cin >> answer4;
	cout << "Do you want [5]? (y/n) ";
	cin >> answer5;
	cout << "Do you want [6]? (y/n) ";
	cin >> answer6;
	cout << "Do you want [7]? (y/n) ";
	cin >> answer7;
	cout << "Do you want [8]? (y/n) ";
	cin >> answer8;

	//While the inFile is good (still data)
	while(inFile.good()){
		//since the pixel is split into RGB, multiply it by 3
		//send the inFile row directly into the array
		for(int i=0; i<columns*3; i++){
			inFile >> myArray[i];
		}
		//Function implementation
		//Option [1]
		if ((answer1 == "Y") || (answer1 == "y")) {
			grey_scale();
		}
		//Option [2]
		if ((answer2 == "Y") || (answer2 == "y")) {
			flip_horizontal();
		}
		//Option [3]
		if ((answer3 == "Y") || (answer3 == "y")) {
			negate_red();
		}
		//Option [4]
		if ((answer4 == "Y") || (answer4 == "y")) {
			negate_green();
		}
		//Option [5]
		if ((answer5 == "Y") || (answer5 == "y")) {
			negate_blue();
		}
		//Option [6]
		if ((answer6 == "Y") || (answer6 == "y")) {
			flatten_red();
		}
		//Option [7]
		if ((answer7 == "Y") || (answer7 == "y")) {
			flatten_green();
		}
		//Option [8]
		if ((answer8 == "Y") || (answer8 == "y")) {
			flatten_blue();
		}

		//print outFile row one at a time
		for(int i=0; i<columns*3; i++){
			//cout << myArray[i] << " ";
			outFile << myArray[i] << " ";
		}
		//Extra to make the outFile prettier to the eyes (new line after every row)
		//cout << endl;
		outFile << endl;
	}

	//First Draft
	/*while (inFile >> currentPixel) {
	//while there is data, do:
	//read in all the columns for one row and store in an array
	//print the row to the outFile
	//row boundary: column
	//we don't actually have to worry about the rows, just the columns, since
	//they are the boundary for that row

	myArray[cursor] = currentPixel;

	//This line below prints out all the correct numbers
	cout << myArray[cursor];

	//now to figure out how to print it row by row (using column boundary)
	for (int number = 0; number < columns; number++) {
	cout << myArray[cursor];
	}
	}*/

	cout << endl;
	cout << "file transferred to " << output << "!" << endl;
	cout << "Pixel count: " << pixelCount << endl;

	inFile.close();
	outFile.close();

	system("pause");
	return 0;
}