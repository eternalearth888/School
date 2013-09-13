#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const int maxColor = 255;
const int BUFFER_SIZE = 4000;
void negate_red(vector<int> &b,int c){
	for (int i=0; i<(c*3.0); i=i+3) {
		b.at(i)=maxColor-b.at(i);
	}
}
void negate_green(vector<int> &b,int c){
	for (int i=1; i<(c*3.0); i=i+3) {
		b.at(i)=maxColor-b.at(i);
	}
}
void negate_blue(vector<int> &b,int c){
	for (int i=2; i<(c*3.0); i=i+3) {
		b.at(i)=maxColor-b.at(i);
	}
}
void flip_horizontal(vector<int> &b,int c){
	vector<int> swapVal(3);
	for (int i=0;i<(c*3/2.0);i=i+3){
		swapVal.at(0)=b.at((c*3)-i-3);
		swapVal.at(1)=b.at((c*3)-i-2);
		swapVal.at(2)=b.at((c*3)-i-1);
		b.at((c*3)-i-3)=b.at(i);
		b.at((c*3)-i-2)=b.at(i+1);
		b.at((c*3)-i-1)=b.at(i+2);
		b.at(i)=swapVal.at(0);
		b.at(i+1)=swapVal.at(1);
		b.at(i+2)=swapVal.at(2);
	}
}
void grey_scale(vector<int> &b,int c){
	double average;
	vector<int> swapVal(3);
	for (int i=0;i<(c*3);i=i+3){
		average=b.at(i);
		average+=b.at(i+1);
		average+=b.at(i+2);
		average/=3.0;
		b.at(i)=average;
		b.at(i+1)=average;
		b.at(i+2)=average;
	}
}
void flatten_red(vector<int> &b,int c){
	for (int i=0; i<(c*3.0); i=i+3) {
		b.at(i)=0;
	}
}
void flatten_green(vector<int> &b,int c){
	for (int i=1; i<(c*3.0); i=i+3) {
		b.at(i)=0;
	}
}
void flatten_blue(vector<int> &b,int c){
	for (int i=2; i<(c*3.0); i=i+3) {
		b.at(i)=0;
	}
}
void horizontal_blur(vector<int> &b,int c){
	double average;
	for (int i=0;i<(c*3);i=i+9){
		average=b.at(i);
		average+=b.at(i+3);
		average+=b.at(i+6);
		average/=3.0;
		b.at(i)=average;
		b.at(i+3)=average;
		b.at(i+6)=average;
		average=b.at(i+1);
		average+=b.at(i+4);
		average+=b.at(i+7);
		average/=3.0;
		b.at(i+1)=average;
		b.at(i+4)=average;
		b.at(i+7)=average;
		average=b.at(i+2);
		average+=b.at(i+5);
		average+=b.at(i+8);
		average/=3.0;
		b.at(i+2)=average;
		b.at(i+5)=average;
		b.at(i+8)=average;	
	}
}
void extreme_contrast(vector<int> &b,int c){
	for (int i=0;i<(c*3);i++){
		if (b.at(i)>=(maxColor/2)){
			b.at(i)=maxColor;
		} else {
			b.at(i)=0;
		}
	}
}

void random_noise(vector<int> &b,int c, int r){
	for (int i=0;i<(c*3);i++){
		if (rand() % 2 == 1){
			b.at(i)+=rand() % r;
		} else {
			b.at(i)-=rand() % r;
		}
		if (b.at(i)<0){
			b.at(i)=0;
		} else if (b.at(i)>maxColor){
			b.at(i)=maxColor;
		}
	}
}
int main() {
	vector<int> buffer(BUFFER_SIZE);
	vector< vector<int> > image;
	string inputFile;
	string outputFile;
	ifstream input;
	ofstream output;
	int range;
	cout << "Portable Pixmap (PPM) Image Editor\n\n";
	cout << "Enter name of image file: ";
	cin >> inputFile;
	input.open(inputFile);
	while (!input){
		cout << "Image file could not be opened" << endl;
		cout << "Enter name of image file: ";
		cin >> inputFile;
		input.open(inputFile);
	}
	cout << "Enter name of output file: ";
	cin >> outputFile;
	output.open(outputFile);
	while (!output){
		cout << "Output file could not be opened for writing" << endl;
		cout << "Enter name of output file: ";
		cin >> outputFile;
		output.open(outputFile);
	}
	cout <<endl << "Image Processing Options:\n[a] Convert to Greyscale [b] Flip Horizontally [c] Flip Vertically\n[d] Negative Reds [e] Negative Greens [f] Negative Blues\n[g] Flatten Reds [h] Flatten Greens [i] Flatten Blues\n[j] Horizontal Blur [k] Extreme Contrast [l] Random Noise\n\nEnter All Options you Would Like at Once\n:"; 
	string options;
	cin >> options;
	cout << "Processing your image with the following options:\n";
	if (options.find('a') != string::npos){
		cout << "Greyscale\n";
	}
	if (options.find('b') != string::npos){
		cout << "Flip Horizontally\n";
	}
	if (options.find('c') != string::npos){
		cout << "Flip Vertically\n";
	}
	if (options.find('d') != string::npos){
		cout << "Negative Reds\n";
	}
	if (options.find('e') != string::npos){
		cout << "Negative Greens\n";
	}
	if (options.find('f') != string::npos){
		cout << "Negative Blues\n";
	}
	if (options.find('g') != string::npos){
		cout << "Flatten Reds\n";
	}
	if (options.find('h') != string::npos){
		cout << "Flatten Greens\n";
	}
	if (options.find('i') != string::npos){
		cout << "Flatten Blues\n";
	}
	if (options.find('j') != string::npos){
		cout << "Horizontal Blur\n";
	}
	if (options.find('k') != string::npos){
		cout << "Extreme Contrast\n";
	}
	if (options.find('l') != string::npos){
		cout << "Random Noise\nEnter Random Noise Range (>0): ";
		cin >> range;
	}


			
	char c;
	int n;
	//parse ppm header
	input >> c;
	output << c;
	input >> n;
	output << n << endl;
	input >> n;
	int columns = n;
	output << n << " ";
	input >> n;
	int rows = n;
	output << n << endl;
	input >> n;
	output << n << endl;
	image.resize(columns,vector<int>(rows));
	if (columns<(BUFFER_SIZE/3.0)){
		//parse ppm body
		for (int i=0; i<rows; i++) {
			for (int j=0; j<columns*3; j++) {
				input >> buffer.at(j);
			}
			if (options.find('a') != string::npos){
				grey_scale(buffer,columns);
			}
			if (options.find('b') != string::npos){
				flip_horizontal(buffer,columns);
			}
			
			if (options.find('d') != string::npos){
				negate_red(buffer,columns);
			}
			if (options.find('e') != string::npos){
				negate_green(buffer,columns);
			}
			if (options.find('f') != string::npos){
				negate_blue(buffer,columns);
			}
			if (options.find('g') != string::npos){
				flatten_red(buffer,columns);
			}
			if (options.find('h') != string::npos){
				flatten_green(buffer,columns);
			}
			if (options.find('i') != string::npos){
				flatten_blue(buffer,columns);
			}
			if (options.find('j') != string::npos){
				horizontal_blur(buffer,columns);
			}
			if (options.find('k') != string::npos){
				extreme_contrast(buffer,columns);
			}
			if (options.find('l') != string::npos){
				random_noise(buffer,columns,range);
			}
			for (int l=0; l<columns*3; l++) {
				if (options.find('c') == string::npos){
					output << " " ;
					output << buffer.at(l);
				} else {
					image.at(rows-1-i)=buffer;
				}
			}
		}
		if (options.find('c') != string::npos){
			for (int i=0; i<rows; i++){
				for (int j=0; j<columns*3; j++) {
					output << " " << image.at(i).at(j);
				}
			}
		}
		cout << outputFile << " created" << endl;
	} else {
		cout << "Image too large for buffer";
	}
	input.close();
	output.close();
	system("pause");
	return 0;
}