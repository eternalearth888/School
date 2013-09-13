#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int maxPixel = 3000;

void negate_red(int pixel[], int numCol) {
	int i = 0;

	while (i < (numCol*3)) {
		pixel[i] = 255 - pixel[i];

		i = i + 3;
	}
}

void negate_green(int pixel[], int numCol) {
	int i = 1;

	while (i < (numCol*3)) {
		pixel[i] = 255 - pixel[i];

		i = i + 3;
	}
}

void negate_blue(int pixel[], int numCol) {
	int i = 2;

	while (i < (numCol*3)) {
		pixel[i] = 255 - pixel[i];

		i = i + 3;
	}
}

void flip_horizontal(int pixel[], int pixelCopy[], int numCol) {
	int i = 0;
	int j = 0;

	while (i < (numCol*3)) {
		pixel[i] = pixelCopy[(numCol*3)-(3+j)];
		pixel[i+1] = pixelCopy[(numCol*3)-(2+j)];
		pixel[i+2] = pixelCopy[(numCol*3)-(1+j)];

		i = i + 3;
		j = j + 3;;
	}
}

void grey_scale(int pixel[], int numCol) {
	int i = 0;

	while (i < (numCol*3)) {
		pixel[i] = pixel[i+1] = pixel[i+2] = (pixel[i] + pixel[i+1] + pixel[i+2]) / 3;

		i = i + 3;
	}
}

void flatten_red(int pixel[], int numCol) {
	int i = 0;

	while (i < (numCol*3)) {
		pixel[i] = 0;

		i = i + 3;
	}
}

void flatten_green(int pixel[], int numCol) {
	int i = 1;

	while (i < (numCol*3)) {
		pixel[i] = 0;

		i = i + 3;
	}
}

void flatten_blue(int pixel[], int numCol) {
	int i = 2;

	while (i < (numCol*3)) {
		pixel[i] = 0;

		i = i + 3;
	}
}

int main(){

	int rowPixel = 0;
	int numCol = 0;
	int numRow = 0;
	int maxColor = 0;

	char ans[8];

	// Declare a string
	string image;
	string outfile;

	string inpixel[maxPixel];
	int pixel[maxPixel];
	int pixelCopy[maxPixel];

	cout << "Portable Pixmap (PPM) Image Editor!" << endl << endl;

	cout << "Enter the name of the image file: " << endl;
	getline(cin, image);
	cout << endl;

	// Open an input stream
	ifstream myfile(image);
	ofstream myfileout(outfile);

	if (!myfile) {
		cout << "Error opening image file" << endl;
	}
	else {

		cout << "Enter the name of the output file: " << endl;
		getline(cin, outfile);
		cout << endl;

		myfileout.open(outfile.c_str());

		if (!myfileout) {
		cout << "Error opening output file" << endl;
		}
		else {

			cout << "Here are your choices:" << endl << endl;
			cout << "[1] Flip horizontally" << endl;
			cout << "[2] Convert to greyscale" << endl;
			cout << "[3] Apply negative red" << endl;
			cout << "[4] Apply negative green" << endl;
			cout << "[5] Apply negative blue" << endl;
			cout << "[6] Apply just reds" << endl;
			cout << "[7] Apply just greens" << endl;
			cout << "[8] Apply just blues" << endl << endl;
			
			cout << "Do you want [1]? (y/n)" << endl;
			cin >> ans[0];
			cout << "Do you want [2]? (y/n)" << endl;
			cin >> ans[1];
			cout << "Do you want [3]? (y/n)" << endl;
			cin >> ans[2];
			cout << "Do you want [4]? (y/n)" << endl;
			cin >> ans[3];
			cout << "Do you want [5]? (y/n)" << endl;
			cin >> ans[4];
			cout << "Do you want [6]? (y/n)" << endl;
			cin >> ans[5];
			cout << "Do you want [7]? (y/n)" << endl;
			cin >> ans[6];
			cout << "Do you want [8]? (y/n)" << endl;
			cin >> ans[7];
			
			for(int i=0; i<4; i++){
				myfile >> inpixel[i];
			}

			for(int i=1; i<4; i++)
			{
				pixel[i]=atoi(inpixel[i].c_str());
			}

			numCol = pixel[1];
			numRow = pixel[2];
			maxColor = pixel[3];	
			
			myfileout << inpixel[0] << endl;
			myfileout << numCol << " " << numRow << endl;
			myfileout << maxColor << endl;
			
			if (maxPixel >= (3*numCol)) {
				for (int j=0; j<numRow; j++) {
					for (int i=0; i<(3*numCol); i++){
						myfile >> inpixel[i];
					}

					for(int i=0; i<(3*numCol); i++)
					{
						pixel[i]=atoi(inpixel[i].c_str());
						pixelCopy[i]=atoi(inpixel[i].c_str());
					}

					if (ans[0] == 'y' || ans[0] == 'Y') {
						flip_horizontal(pixel,pixelCopy,numCol);	
					}
					if (ans[1] == 'y' || ans[1] == 'Y') {
						grey_scale(pixel,numCol);	
					}
					if (ans[2] == 'y' || ans[2] == 'Y') {
						negate_red(pixel,numCol);	
					}
					if (ans[3] == 'y' || ans[3] == 'Y') {
						negate_green(pixel,numCol);	
					}
					if (ans[4] == 'y' || ans[4] == 'Y') {
						negate_blue(pixel,numCol);	
					}
					if (ans[5] == 'y' || ans[5] == 'Y') {
						flatten_red(pixel,numCol);	
					}
					if (ans[6] == 'y' || ans[6] == 'Y') {
						flatten_green(pixel,numCol);	
					}
					if (ans[7] == 'y' || ans[7] == 'Y') {
						flatten_blue(pixel,numCol);	
					}
					
					for (int i=0; i<(numCol*3); i++) {
						myfileout << pixel[i] << " ";
					}
		
					myfileout << endl;
				}

				myfileout.close();
	
				cout << outfile << " created" << endl << endl;
			}
			else {
				cout << endl << "The image is too large to be processed." << endl << endl;
			}
		}
	}

	system ("pause");
}