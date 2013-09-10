#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//functions
void grayScale(ofstream &out_image, int x, int columns_wanted);
void flipHorizontal(ofstream &out_image, int i, int columns_wanted);
void negateRed(ofstream &out_image, int x, int columns_wanted);
void negateGreen(ofstream &out_image, int x, int columns_wanted);
void negateBlue(ofstream &out_image, int x, int columns_wanted);
void flattenRed(ofstream &out_image, int x, int columns_wanted);
void flattenGreen(ofstream &out_image, int x, int columns_wanted);
void flattenBlue(ofstream &out_image, int x, int columns_wanted);

//global variables
const int SIZE = 3000;
int pixels[SIZE];
int *flip = new int[SIZE];
int grayscaleTotal;
int counter;		
int columns_wanted, rows_wanted, max_value;
int min_value = 0;	
int index;

int main() {
	string imageFile;
	string newImage;
	int pixelCount = 0;
	int pixel = 0;
	char choice1;
	char choice2;
	char choice3;
	char choice4;
	char choice5;
	char choice6;
	char choice7;
	char choice8;
	string type_of_ppm;

	
	cout << "Portable Pixmap (PPM) Image Editor" << endl;
	cout << "Please enter in the image filename (add .ppm at the end): " << endl;
	cin >> imageFile;
	cout << "Please enter in the output image filename (add .ppm at the end): " << endl;
	cin >> newImage;

	cout << " Here are your choices:" << endl
		<< "[1]  convert to greyscale  [2]  flip horizontally" << endl
		<< "[3]  negative of red  [4]  negative of green " << endl 
		<< "[5]  negative of blue  [6]  just the reds" << endl 
		<< "[7]  just the greens   [8]  just the blues" << endl << endl;
	cout << "Do you want [1]? (y/n): ";
	cin >> choice1;
	cout << "Do you want [2]? (y/n): ";
	cin >> choice2;
	cout << "Do you want [3]? (y/n): ";
	cin >> choice3;
	cout << "Do you want [4]? (y/n): ";
	cin >> choice4;
	cout << "Do you want [5]? (y/n): ";
	cin >> choice5;
	cout << "Do you want [6]? (y/n): ";
	cin >> choice6;
	cout << "Do you want [7]? (y/n): ";
	cin >> choice7;
	cout << "Do you want [8]? (y/n): ";
	cin >> choice8;
	
	ifstream in_image(imageFile.c_str());
	ofstream out_image(newImage.c_str());

	if (!in_image) {
		cerr << "Error opening the input file\n";
		exit (1);
	}
	if (!out_image) {
	cerr << "Error opening the input file\n";
	exit (1);
	}
	

	in_image >> type_of_ppm;
	out_image << type_of_ppm << endl;
	in_image >> columns_wanted >> rows_wanted;
	out_image << columns_wanted << " " << rows_wanted << endl;
	in_image >> max_value;
	out_image << max_value << endl;
/*
	while (in_image >> pixel_in_row) {
		if (position <= 12 && pixel_in_row <= max_value) {
			cout << "pixel: " << pixel_in_row << endl;
			pixels[position] = pixel_in_row; //<< space
			cout << "stored: " << position << " " << pixels[position] << endl;
			position++;
		} else if(position > 12) {
			cerr << "Error! Exceeded the buffer.";
			exit(1); 
		}
	}

*/
	//cout << "Choice1 " << choice1;
	
	//cout << "number of indices:" << columns_wanted*3 << endl;
	

	for (int j = 0; j < rows_wanted; j++) {
		grayscaleTotal = 0;
		counter = 0;
		int i;
		index = 0;
		flip = new int[columns_wanted*3];
	
		for (int k = 0; k < columns_wanted*3; k++) {
			
			if (k < SIZE) {
				i = k;
				in_image >> pixels[i];
			} else {
				i = k - SIZE;
				in_image >> pixels[i];
			}
			if (pixels[i] < 0 || pixels[i] > 255) {
				cout << "ERROR! Color number is not between 0 and 255 at index " << i << " " << j << ". It is " << pixels[i] << "max" << max_value << endl;
				exit(0);
			}
			//cout << "i" << i << "max" << max_value << endl;
			
			if(choice1 == 'y'){
					grayScale(out_image, i, columns_wanted);
				}
				if(choice2 == 'y') {
					flipHorizontal(out_image, i, columns_wanted);
				}
				if(choice3 == 'y') {
					negateRed(out_image, i, columns_wanted);
				}
				if(choice4 == 'y') {
					negateGreen(out_image, i, columns_wanted);
				}
				if(choice5 == 'y') {
					negateBlue(out_image, i, columns_wanted);
				}
				if(choice6 == 'y') {
					flattenRed(out_image, i, columns_wanted);
				}
				if(choice7 == 'y') {
					flattenGreen(out_image, i, columns_wanted);
				}
				if(choice8 == 'y') {
					flattenBlue(out_image, i, columns_wanted);
				}
		
	
			
			
//================= FOR GRAYSCALE COPY ============================
		
			/*if (counter < 3) {
				grayscaleTotal = pixels[i] + grayscaleTotal;
				if (counter == 2) {
					pixels[i] = grayscaleTotal / 3;
					pixels[i-1] = grayscaleTotal / 3;
					pixels[i-2] = grayscaleTotal / 3;
					cout //<< "array spot:" << i-3 << " array value:" << pixels[i-3] << endl 
							<< "array spot:" << i-2 << " array value:" << pixels[i-2] << endl
							<< "array spot:" << i-1 << " array value:" << pixels[i-1] << endl
							<< "array spot:" << i << " array value:" << pixels[i] << endl;
					out_image << pixels[i-2] << " " << pixels[i-1] << " " << pixels[i] << " ";
				}
			} else {
				counter = 0;
				grayscaleTotal = pixels[i];
			}
			counter++;*/
		
			
//================= FOR FLIP HORIZONTAL COPY ============================
/*
			if	(i % 3 == 0) { 
				flip[columns_wanted*3 - i - 3] = pixels[i]; 
				//cout << "pixel index " << i
					// << "  pixel value " << pixels[i]
					// << "  flip index:" << columns_wanted*3 - i - 3
					// << "  flip value " << flip[columns_wanted*3 - i -3] << endl;
			} else if (i % 3 == 1) { 
				flip[columns_wanted*3 - i - 1]= pixels[i]; 
				//cout << "  pixel index " << i
				//	 << "  pixel value " << pixels[i]
				//	 << "  flip index:" << columns_wanted*3 - i - 1
				//	 << "  flip value " << flip[columns_wanted*3 - i - 1] << endl;

					 
			} else if (i % 3 == 2) { 
				flip[columns_wanted*3 - i + 1] = pixels[i];
				//cout << "  pixel index " << i
				//	 << "  pixel value " << pixels[i]
				//	 << "  flip index:" << columns_wanted*3 - i + 1
				//	 << "  flip value " << flip[columns_wanted*3 - i + 1] << endl;
			}
			if (i == (columns_wanted*3) - 1) {
				for (int p = 0; p < columns_wanted*3; p++) {
					pixels[p] = flip[p];
					out_image << pixels[p] << " ";
				}
			}
*/

//================= FOR NEGATE RED COPY ============================
	/*	
			int negativeRed;
			if (i % 3 == 0) {
				negativeRed = 255 - pixels[i];
				pixels[i] = negativeRed;
			}
		
		
//================= FOR NEGATE GREEN COPY ============================
	
			int negativeGreen;
			if (i % 3 == 1) {
				negativeGreen = 255 - pixels[i];
				pixels[i] = negativeGreen;
			}
		
	
//================= FOR NEGATE BLUE COPY ============================
			
			int negativeBlue;
			if (i % 3 == 2) {
				negativeBlue = 255 - pixels[i];
				pixels[i] = negativeBlue;
			}
			

//================= FOR FLATTEN RED COPY ============================
			
			if (i % 3 == 0) {
				pixels[i] = 0;
			}
			


*/			
//================= FOR FLATTEN GREEN COPY ============================
	/*		
			if (i % 3 == 1) {
				pixels[i] = 0;
			}
		

*/

//================= FOR FLATTEN BLUE COPY ============================
	/*		
			if (i % 3 == 2) {
				pixels[i] = 0;
			}
			

*/
//================= FOR IDENTICAL COPY ============================
	//		if (choice1 == 'n' && choice2 == 'n') {
	//			out_image << pixels[i] << " ";
	//		}

		}
		
		out_image << endl;
	}
	

	
	
	out_image.close();
	in_image.close();

	cout << newImage << " created." << endl;

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	void grayScale(ofstream &out_image, int i, int columns_wanted) {
			if (counter < 3) {
				grayscaleTotal = pixels[i] + grayscaleTotal;
				if (counter == 2) {
					pixels[i] = grayscaleTotal / 3;
					pixels[i-1] = grayscaleTotal / 3;
					pixels[i-2] = grayscaleTotal / 3;
					if (i > SIZE) {
						cout// "array spot:" << i-3 << " array value:" << pixels[i-3] << endl 
								<< "array spot:" << i-2 << " array value:" << pixels[i-2] << endl
								<< "array spot:" << i-1 << " array value:" << pixels[i-1] << endl
								<< "array spot:" << i << " array value:" << pixels[i] << endl;
					}
					out_image << pixels[i-2] << " " << pixels[i-1] << " " << pixels[i] << " ";
				}
			} else {
				counter = 0;
				grayscaleTotal = pixels[i];
			}
			counter++;
	} 
	

	void flipHorizontal(ofstream &out_image, int i, int columns_wanted) {
		
		if (index < (columns_wanted*3)/2) {
			if	(i % 3 == 0) { 
				flip[columns_wanted*3 - i - 3] = pixels[i]; 
				//cout << "pixel index " << i
					// << "  pixel value " << pixels[i]
					// << "  flip index:" << columns_wanted*3 - i - 3
					// << "  flip value " << flip[columns_wanted*3 - i -3] << endl;
			} else if (i % 3 == 1) { 
				flip[columns_wanted*3 - i - 1]= pixels[i]; 
				//cout << "  pixel index " << i
				//	 << "  pixel value " << pixels[i]
				//	 << "  flip index:" << columns_wanted*3 - i - 1
				//	 << "  flip value " << flip[columns_wanted*3 - i - 1] << endl;
		 
			} else if (i % 3 == 2) { 
				flip[columns_wanted*3 - i + 1] = pixels[i];
				//cout << "  pixel index " << i
				//	 << "  pixel value " << pixels[i]
				//	 << "  flip index:" << columns_wanted*3 - i + 1
				//	 << "  flip value " << flip[columns_wanted*3 - i + 1] << endl;
			}

			if (i == (columns_wanted*3)/2 - 1) {
				for (int p = 0; p < columns_wanted*3/2; p++) {
					pixels[p] = flip[p];
					out_image << pixels[p] << " ";
				}
			}
		} else {
			if	(i % 3 == 0) { 
				flip[columns_wanted*3 - i - 9] = pixels[i]; 
				//cout << "pixel index " << i
					// << "  pixel value " << pixels[i]
					// << "  flip index:" << columns_wanted*3 - i - 3
					// << "  flip value " << flip[columns_wanted*3 - i -3] << endl;
			} else if (i % 3 == 1) { 
				flip[columns_wanted*3 - i - 7]= pixels[i]; 
				//cout << "  pixel index " << i
				//	 << "  pixel value " << pixels[i]
				//	 << "  flip index:" << columns_wanted*3 - i - 1
				//	 << "  flip value " << flip[columns_wanted*3 - i - 1] << endl;

					 
			} else if (i % 3 == 2) { 
				flip[columns_wanted*3 - i - 5] = pixels[i];
				//cout << "  pixel index " << i
				//	 << "  pixel value " << pixels[i]
				//	 << "  flip index:" << columns_wanted*3 - i + 1
				//	 << "  flip value " << flip[columns_wanted*3 - i + 1] << endl;
			}
			if (i == (columns_wanted*3/2) - 1) {
				for (int p = 0; p < columns_wanted*3/2; p++) {
					pixels[p] = flip[p];
					out_image << pixels[p] << " ";
				}
			}
			cout << "i" << i << endl;
		}
		index++;
		

	}
	
	void negateRed(ofstream &out_image, int x, int columns_wanted) {
		int negativeRed;
			if (x % 3 == 0) {
				negativeRed = 255 - pixels[x];
				pixels[x] = negativeRed;
			}
		out_image << pixels[x] << " ";
	}
	void negateGreen(ofstream &out_image, int x, int columns_wanted) {
		int negativeGreen;
			if (x % 3 == 1) {
				negativeGreen = 255 - pixels[x];
				pixels[x] = negativeGreen;
			}
			out_image << pixels[x] << " ";
	}
	void negateBlue(ofstream &out_image, int x, int columns_wanted) {
			int negativeBlue;
			if (x % 3 == 2) {
				negativeBlue = 255 - pixels[x];
				pixels[x] = negativeBlue;
			}
			out_image << pixels[x] << " ";
	}
	void flattenRed(ofstream &out_image, int x, int columns_wanted) {
			if (x % 3 == 0) {
				pixels[x] = 0;
			}
			out_image << pixels[x] << " ";
	}
	void flattenGreen(ofstream &out_image, int x, int columns_wanted) {
			if (x % 3 == 1) {
				pixels[x] = 0;
			}
			out_image << pixels[x] << " ";
	}
	void flattenBlue(ofstream &out_image, int x, int columns_wanted) {
			if (x % 3 == 2) {
				pixels[x] = 0;
			}
			out_image << pixels[x] << " ";
	}


/*
	if(choice1 = 'y'){
		//grayscale
		for (int i = 0; i < 12; i = i + 3) {
			int grayscaleTotal = 0;
			for (int i = 0; i < 3; i++) {
				in_image >> pixel_in_row;
				grayscaleTotal= grayscaleTotal + pixel_in_row;
			}
			pixels[i] = grayscaleTotal/3;
			pixels[i+1] = grayscaleTotal/3;
			pixels[i+2] = grayscaleTotal/3;
		}


	}
	if(choice2 = 'y'){
		//flip horizontally



	}
	if(choice3 = 'y'){
		//negative red
		for (int i = 0; i < 12; i = i + 3) {
			int negativeRed;
			in_image >> pixel_in_row;
			negativeRed = 255-pixel_in_row;
			pixels[i] = negativeRed;
		}

	}
	if(choice4 = 'y'){
		//negative green
		for (int i = 0; i < 12; i = i + 3) {
			int negativeGreen;
			in_image >> pixel_in_row;
			negativeGreen = 255-pixel_in_row;
			pixels[i] = negativeGreen;
		}


	}
	if(choice5 = 'y'){
		//negative blue
		for (int i = 0; i < 12; i = i + 3) {
			int negativeBlue;
			in_image >> pixel_in_row;
			negativeBlue = 255-pixel_in_row;
			pixels[i] = negativeBlue;
		}


	}
	if(choice6 = 'y'){
		//just the reds



	}if(choice7 = 'y'){
		//just the greens



	}
	if(choice8 = 'y'){
		//just the blues



	}


	*/