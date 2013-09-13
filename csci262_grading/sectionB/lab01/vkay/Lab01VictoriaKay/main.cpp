#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {

	string imagefile, outputfile;

	cout << "Enter name of image file: ";
	cin >> imagefile;

	ifstream image;
	image.open(imagefile);

	if (!image) {
		cout << "Error opening image file. \n";
		exit (1);
	}

	cout << "Enter name of output file: ";
	cin >> outputfile;

	ofstream output;
	output.open(outputfile);

	if (output.fail()) {
		cout << "Error opening output file. \n";
		exit (1);
	}

	string magic;
	int row, column, color;
	int number[3000];
	char grey1, flip2, nr3, ng4, nb5, red6, green7, blue8;

	image >> magic >> row >> column >> color;

	output << magic << endl << row << " " << column << endl << color << endl;

	//cout << "rows: " << row << " columns: " << column << endl;

	cout << "Here are your choices: \n [1] convert to greyscale [2] flip horizontally \n " <<
		"[3] negative of red [4] negative of green [5] negative of blue \n [6] just the reds " <<
		"[7] just the greens [8] just the blues \n \n Do you want [1]? (y/n) ";
	cin >> grey1;
	cout << "\n Do you want [2]? (y/n) ";
	cin >> flip2;
	cout << "\n Do you want [3]? (y/n) ";
	cin >> nr3;
	cout << "\n Do you want [4]? (y/n) ";
	cin >> ng4;
	cout << "\n Do you want [5]? (y/n) ";
	cin >> nb5;
	cout << "\n Do you want [6]? (y/n) ";
	cin >> red6;
	cout << "\n Do you want [7]? (y/n) ";
	cin >> green7;
	cout << "\n Do you want [8]? (y/n) ";
	cin >> blue8;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column * 3; j++) {
			image >> number[j];
		}
		if (nr3 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {   //negate_red
				number[j] = color - number[j];
			}
		} 
		if (ng4 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {     //negate_green
				number[j + 1] = color - number[j + 1];
			}
		}
		if (nb5 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {     //negate_blue
				number[j + 2] = color - number[j + 2];
			}
		}


		if (flip2 == 'y') {
			for (int j = 0; j < (column * 3) /2; j+=3) { //flip_horizontal
				int k = number[j];
				number[j] = number[column * 3 - (j + 2)];
				number[column * 3 - (j + 2)] = k;
				int m = number[j + 1];
				number[j + 1] = number[column * 3 - (j + 1)];
				number[column * 3 - (j + 1)] = m;
				int n = number[j + 2];
				number[j + 2] = number[column * 3 - (j)];
				number[column * 3 - (j)] = n;
			}
		}

		if (grey1 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {   //grey_scale
				int average = (number[j] + number[j + 1] + number[j + 2]) / 3;
				number[j] = average;
				number[j + 1] = average;
				number[j + 2] = average;
			}
		} 
		if (red6 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {     //flatten_red
				number[j] = 0;
			}
		}
		if (green7 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {     //flatten_green
				number[j + 1] = 0;
			}
		}
		if (blue8 == 'y') {
			for (int j = 0; j < column * 3; j+=3) {     //flatten_blue
				number[j + 2] = 0;
			}
		}
		for (int j = 0; j < column * 3; j++) {
			output << number[j] << " ";
		}
		//cout << i << " ";
		output << endl;
	}

	image.close();
	output.close();

	system("pause");

	return 0;

}