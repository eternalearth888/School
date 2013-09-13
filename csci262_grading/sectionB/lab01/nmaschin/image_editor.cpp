#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//constants
const int BUFFER_SIZE = 1000; //buffer size in pixels
const int NUM_EFFECTS = 9; //number of effects the user can choose from

//global
int maxColor; //maximum possible color value
int rows; //number of rows of pixels
int columns; //number of columns in pixels
int temp[3]; //used in processing data

//prototypes
void negate_red(int buffer[]);
void negate_green(int buffer[]);
void negate_blue(int buffer[]);
void flip_horizontal(int buffer[]);
void grey_scale(int buffer[]);
void flatten_red(int buffer[]);
void flatten_green(int buffer[]);
void flatten_blue(int buffer[]);
void extreme_contrast(int buffer[]);
void effectMenu(bool effectOptions[]);
void applyEffects(int buffer[], bool effectOptions[]);


int main() {
	int buffer[BUFFER_SIZE*3];
	bool effectOptions[NUM_EFFECTS];
	string imageType;


	//open file
	cout << "Enter name of image file:" << endl;
	string imageFileName;
	cin >> imageFileName;
	ifstream inputFile(imageFileName);

	if (!inputFile) {
		cerr << "Error opening file" << endl;
		system("pause");
		exit(1);
	}

	//create output file
	cout << "Enter name of output file:" << endl;
	string outputFileName;
	cin >> outputFileName;
	ofstream outputFile(outputFileName);

	if(!outputFile) {
		cerr << "Error creating file" << endl;
		system("pause");
		exit(1);
	}

	//read in image header info
	inputFile >> imageType;
	inputFile >> columns;
	inputFile >> rows;
	inputFile >> maxColor;

	//quit if picture has too many columns for buffer
	if (rows > BUFFER_SIZE) {
		cerr << "The picture has too many rows" << endl;
		system("pause");
		exit(1);
	}

	//create output file
	outputFile << imageType << endl;
	outputFile << columns << " " << rows << endl;
	outputFile << maxColor << endl;

	//prompt user for effects to apply
	effectMenu(effectOptions);
	cout << "Creating picture..." << endl;

	//copy in rows from input file
	for (int i = 0; i < rows; i ++) {
		for (int j = 0; j < columns*3; j++) { //read a row into the buffer
			inputFile >> buffer[j];
		}

		//apply effects to row
		applyEffects(buffer, effectOptions);



		for (int j = 0; j < columns*3; j++) { //write row to the output file
			outputFile << buffer[j] << " ";
		}
		outputFile << endl;
	}

	//close files
	inputFile.close();
	outputFile.close();

	cout << endl << endl;
	system("pause");
	return 0;


}

//negate a color
int negate(int color) {
	if (color < (double)maxColor/2) {
		color += ((double)maxColor/2 - color)*2;
	} else {
		color -= (color - (double)maxColor/2)*2;
	}
	return color;
}

//negate all reds
void negate_red(int buffer[]) {
	for (int i = 0; i < columns*3; i+=3) {
		buffer[i] = negate(buffer[i]);
	}
}

//negate all greens
void negate_green(int buffer[]) {
	for (int i = 1; i < columns*3; i+=3) {
		buffer[i] = negate(buffer[i]);
	}
}

//negate all blues
void negate_blue(int buffer[]) {
	for (int i = 2; i < columns*3; i+=3) {
		buffer[i] = negate(buffer[i]);
	}
}

//set all reds to 0
void flatten_red(int buffer[]) {
	for (int i = 0; i < columns*3; i+=3) {
		buffer[i] = 0;
	}
}

//set all greens to 0
void flatten_green(int buffer[]) {
	for (int i = 1; i < columns*3; i+=3) {
		buffer[i] = 0;
	}
}

//set all blues to 0
void flatten_blue(int buffer[]) {
	for (int i = 2; i < columns*3; i+=3) {
		buffer[i] = 0;
	}
}

//flip the pixels at positions a and b
void flip(int buffer[], int a, int b) {
	a = 3*a;
	b = 3*b;
	for (int i = 0; i < 3; i ++) {
		temp[i] = buffer[a + i];
	}
	for (int i = 0; i < 3; i ++) {
		buffer[a + i] = buffer[b+i];
		buffer[b+i] = temp[i];
	}
}

//flip the row horizontally
void flip_horizontal(int buffer[]) {
	for (int i = 0; i < columns/2; i++) {
		flip(buffer, i, columns-i);
	}
}

//convert row to greyscale by setting each pixel value to average of the three
void grey_scale(int buffer[]) {
	for (int i = 0; i < columns*3; i+=3) {
		buffer[i] = buffer[i+1] = buffer[i+2] = 
			(buffer[i] + buffer[i+1] + buffer[i+2])/3;
	}
}

//ask the user if effect should be applied, set array to match input
void setEffect(bool effectOptions[], int effect) {
	char c;
	cout << "Do you want [" << effect+1 << "]? (y/n) ";
	cin >> c;
	if (c == 'y' || c == 'Y') {
		effectOptions[effect] = true;
	} else {
		effectOptions[effect] = false;
	}
}

//prompt user for which effects to apply
void effectMenu(bool effectOptions[]) {
	cout << "Here are your choices:" << endl <<
		"[1] convert to greyscale  [2] flip horizontally" << endl <<
		"[3] negative of red  [4] negative of green  [5] negative of blue" << endl <<
		"[6] just the reds  [7] just the greens  [8] just the blues" << endl <<
		"[9] extreme constrast" << endl << endl;

	for (int i = 0; i < NUM_EFFECTS; i++) {
		setEffect(effectOptions, i);
	}
}

//set color values to highest possible or to 0 
void extreme_contrast(int buffer[]) {
	for (int i = 0; i < columns*3; i++) {
		if (buffer[i] > maxColor/2) {
			buffer[i] = maxColor;
		} else {
			buffer[i] = 0;
		}
	}
}

//apply effects to row
void applyEffects(int buffer[], bool effectOptions[]) {
	if (effectOptions[0]) { //greyscale
		grey_scale(buffer);
	}
	if (effectOptions[1]) { //flip horizontally
		flip_horizontal(buffer);
	}
	if (effectOptions[2]) { //negate red
		negate_red(buffer);
	}
	if (effectOptions[3]) { //negate green
		negate_green(buffer);
	}
	if (effectOptions[4]){ //negate blue
		negate_blue(buffer);
	}
	if (effectOptions[5]) { //only reds
		flatten_green(buffer);
		flatten_blue(buffer);
	}
	if (effectOptions[6]) { //only greens
		flatten_red(buffer);
		flatten_blue(buffer);
	}
	if (effectOptions[7]) { //only blues
		flatten_red(buffer);
		flatten_green(buffer);
	}
	if (effectOptions[8]) {//extreme constrast
		extreme_contrast(buffer);
	}
}