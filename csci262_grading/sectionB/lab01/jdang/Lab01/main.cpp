//James Dang
//LAB01
//PPM Files

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

const int BUFFERSIZE = 3000, rgb = 3;//constant values used

void negate_red (int buffer[], int columns); //– Its job is to negate the red number of each pixel.
void negate_green (int buffer[], int columns);//, as above but change the green
void negate_blue (int buffer[], int columns);//, as above but change the blue
void flip_horizontal (int buffer[], int columns);//that flips each row horizontally
void grey_scale (int buffer[], int columns);//sets each pixel value to the average of the three
void flatten_red (int buffer[], int columns);//sets the red value to zero
void flatten_green (int buffer[], int columns);//sets the green value to zero
void flatten_blue (int buffer[], int columns);//sets the blue value to zero
void extreme_contrast (int buffer[], int columns, int colorMax);//change the number to the highest or lowest possible.


int main() {//main
	int buffer[BUFFERSIZE];//buffer arrary declared with size
	string fileName;//the filename used of input and output files
	char magic, number;//magic numbers for header
	int rows, columns;//the dimensions of picture for header
	int colorMax, pixel;//the maximum color value for header and pixel color
	char choice[9];//choices for applying effects to image
	cout<<"~PPM Image Editor~"<<endl;//start of the program
	cout<<"What image file would you like to use?\nFilename(ex. in.ppm):";//input file
	cin>>fileName;
	ifstream inPic(fileName.c_str());
	if (inPic.fail()) {//input file error
		cerr<<"Cannot open file."<<endl;
		return 1;
	}
	cout<<"What should the finished image file name be?\nFilename(ex. out.ppm):";//output file
	cin>>fileName;
	ofstream outPic(fileName.c_str());
	if (outPic.fail()) {//output file error
		cerr<<"Cannot open file."<<endl;
		return 1;
	}

	//Input header and output header from files
	inPic>>magic;
	inPic>>number;
	inPic>>rows;
	inPic>>columns;
	if (columns*3 > BUFFERSIZE) {
		cerr<<"Exceeded buffer size"<<endl;
		system("pause");
		return 2;
	}
	inPic>>colorMax;
	cout<<"Magic Number: "<<magic<<number<<endl;
	cout<<"Pixels: "<<rows<<"x"<<columns<<endl;
	cout<<"Max Color: "<<colorMax<<endl;
	outPic<<magic<<number<<"\n";
	outPic<<rows<<" "<<columns<<"\n";
	outPic<<colorMax<<"\n";

	//choices for image editing
	cout<<"Modify Image in what way?"<<endl;
	cout<<"[1]convert to greyscale [2]flip horizontally "<<endl;
	cout<<"[3]negative of red      [4]negative of green [5]negative of blue"<<endl;
	cout<<"[6]just the reds        [7]just the greens   [8]just the blues"<<endl;
	cout<<"[9]extreme contrast"<<endl;
	for (int i = 0; i < 9; i++) {
		cout<<"Apply ["<<i+1<<"] (y/n): ";
		cin>>choice[i];
	}
	cout<<"applying..."<<endl;

	for (int i = 0; i < rows; i++) {//fills the buffer
		for (int j = 0; j < columns*rgb; j++) {
			inPic>>pixel;
			buffer[j] = pixel;
		}
		//apply editing effects.
		if (choice[0] == 'y' || choice[0] == 'Y')
			grey_scale(buffer, columns);
		if (choice[1] == 'y' || choice[1] == 'Y')
			flip_horizontal(buffer, columns);
		if (choice[2] == 'y' || choice[2] == 'Y')
			negate_red(buffer, columns);
		if (choice[3] == 'y' || choice[3] == 'Y')
			negate_green(buffer, columns);
		if (choice[4] == 'y' || choice[4] == 'Y')
			negate_blue(buffer, columns);
		if (choice[5] == 'y' || choice[5] == 'Y')
			flatten_red(buffer, columns);
		if (choice[6] == 'y' || choice[6] == 'Y')
			flatten_green(buffer,columns);
		if (choice[7] == 'y' || choice[7] == 'Y')
			flatten_blue(buffer, columns);
		if (choice[8] == 'y' || choice[8] == 'Y')
			extreme_contrast(buffer, columns, colorMax);

		for (int j = 0; j < columns*rgb; j++) {//outputs the edited buffer into output file
			outPic<<buffer[j]<<" ";
			if (j % rgb == 2) 
				outPic<<"\t";
		}
		outPic<<"\n";
	}

	inPic.close();//closes both files
	outPic.close();
	cout<<"Image finished."<<endl;
	system("pause");
	return 0;
}

void negate_red (int buffer[], int columns) {//negates red
	for (int i = 0; i < columns * rgb; i++) {
		if ((i % rgb) == 0)
			buffer[i] = 255 - buffer[i];
	}
}

void negate_green (int buffer[], int columns) {//negates green
	for (int i = 0; i < columns * rgb; i++) {
		if ((i % rgb) == 1)
			buffer[i] = 255 - buffer[i];
	}
}

void negate_blue (int buffer[], int columns) {//negates blue
	for (int i = 0; i < columns * rgb; i++) {
		if ((i % rgb) == 2)
			buffer[i] = 255 - buffer[i];
	}
}

void flip_horizontal (int buffer[], int columns) {//flips the picture horizontally
	int* temp = new int[columns*rgb];
	int i = 0, j = columns * rgb - 1;
	while (i < (columns * rgb)) {//puts the last pixel of buffer into the first part of temp
		temp[i] = buffer[j-2];
		temp[i+1] = buffer[j-1];
		temp[i+2] = buffer[j];
		i += rgb;
		j -= rgb;
	}
	for (int i = 0; i < columns * rgb; i++) {//places temp into buffer
		buffer[i] = temp[i];
	}
	delete[] temp;//deallocate temp
}

void grey_scale (int buffer[], int columns) {//turns the picture grayscale
	int average = 0;
	for (int i = 0; i < columns * rgb; i++) {
		average += buffer[i];
		if ((i + 1) % rgb == 0) {
			average /=rgb;
			buffer[i] = average;
			buffer[i-1] = average;
			buffer[i-2] = average;
			average = 0;
		}
	}
}
void flatten_red (int buffer[], int columns) {//makes red 0
	for (int i = 0; i < columns * rgb; i++) {
		if ((i % rgb) == 0)
			buffer[i] = 0;
	}
}
void flatten_green (int buffer[], int columns) {//makes green 0
	for (int i = 0; i < columns * rgb; i++) {
		if ((i % rgb) == 1)
			buffer[i] = 0;
	}
}
void flatten_blue (int buffer[], int columns) {//makes blue 0
	for (int i = 0; i < columns * rgb; i++) {
		if ((i % rgb) == 2)
			buffer[i] = 0;
	}
}

void extreme_contrast (int buffer[], int columns, int colorMax) {//change the number to the highest or lowest possible.
	for (int i = 0; i < columns * rgb; i++) {
		if (buffer[i] > colorMax/2)
			buffer[i] = colorMax;
		else if (buffer[i] < colorMax/2)
			buffer[i] = 0;
	}

}