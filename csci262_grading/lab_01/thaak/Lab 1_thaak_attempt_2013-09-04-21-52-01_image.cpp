#include "image.h"
#include <string>
#include <fstream>

using namespace std;

//Author: TREVOR HAAK

//default constructor
image::image(){
	rows = 0;
	cols = 0;
	max = 0;
	ppm_type = "Null";
}

//reads image input
void image::read_image(ifstream &stream_in, ofstream &stream_out){
	//store header data
	stream_in >> ppm_type >> cols >> rows >> max;
	if(cols*3 > BUFFER){
		cerr <<"Image is too long horizontally! 3000px or less please..." << endl;
		system("pause");
		exit(1);
	}
	//write output file header
	stream_out << ppm_type << endl << " " << cols << " " << rows << endl << " " << max << endl;
	//push row into output file
	for(int j=0; j < rows; j++){
		for(int i=0; i < cols*3; i++){
			stream_in >> data[i];
		}
		for(int i=0; i < cols*3; i++){
			stream_out << data[i] << " ";
		}
		stream_out << endl;

	}
	return;
}

//negates red values of buffer array
void image::negate_red(){
	for(int i=0; i < cols*3; i+=3){
		data[i] = max - data[i];
	}
	return;
}

//negates green values of buffer array
void image::negate_green(){
	for(int i=1; i < cols*3; i+=3){
		data[i] = max - data[i];
	}
	return;
}

//negates blue values of buffer array
void image::negate_blue(){
		for(int i=2; i < cols*3; i+=3){
			data[i] = max - data[i];
		}
		return;
}

//flips pixels horizontally in buffer array
void image::flip_horizontal(){
	int red;
	int green;
	int blue;
	for(int i=0; i < cols*3 / 2; i+=3){
		red = data[i];
		green = data[i+1];
		blue = data[i+2];
		data[i] = data[cols*3-i - 3];
		data[i+1] = data[cols*3-i - 2];
		data[i+2] = data[cols*3-i - 1];
		data[cols*3-i - 3] = red;
		data[cols*3-i - 2] = green;
		data[cols*3-i - 1] = blue;
	}
	return;
}

//converts color to greyscale
void image::grey_scale(){
	int avg;
	for(int i=0; i < cols*3; i+=3){
		avg = (data[i] + data[i+1] + data[i+2]) / 3;
		data[i] = avg;
		data[i+1] = avg;
		data[i+2] = avg;
	}
	return;
}

//zeroes red values of buffer array
void image::flatten_red(){
	for(int i=0; i < cols*3; i+=3){
		data[i] = 0;
	}
	return;
}

//zeroes green values of buffer array
void image::flatten_green(){
	for(int i=1; i < cols*3; i+=3){
		data[i] = 0;
	}
	return;
}

//zeroes blue values of buffer array
void image::flatten_blue(){
	for(int i=2; i < cols*3; i+=3){
		data[i] = 0;
	}
	return;
}

//returns max value
int image::get_max(){
	int maxxy;
	maxxy = max;
	return maxxy;
}

//performs functions common to select_effects function
void image::image_setup(ifstream &st_in, ofstream &st_out, string fi_in, string fi_out){
	st_in.close();
	st_in.open(fi_in);
	st_out.close();
	st_out.open(fi_out);
	//store header data
	st_in >> ppm_type >> cols >> rows >> max;
	//write output file header
	st_out << ppm_type << endl << " " << cols << " " << rows << endl << " " << max << endl;
	return;
}

//prompts user with effects menu and carries out those effects
void image::select_effects(string fi_in, string fi_out){
	char yesno = 'n';
	ifstream st_in (fi_in.c_str());
	ofstream st_out (fi_out.c_str());
	//check for no file streams
	if(!st_in){
		cerr << "Error finding input file for processing!" << endl;
		system("pause");
		exit(1);
	}
	if(!st_out){
		cerr << "Error finding output file for processing!" << endl;
		system("pause");
		exit(1);
	}
	//prompt user to wait
	cout << "One moment please..." << endl;
	//transfer regular image
	read_image(st_in, st_out);
	//prompt user with menu
	cout << "Please select which image effects you would like to apply:" << endl;
	//Effect [1] ****************************************
	cout << "[1] Apply Negate Red? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			negate_red();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Negate Red applied!" << endl << endl;
	}
	//Effect [2] ****************************************
	cout << "[2] Apply Negate Green? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			negate_green();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Negate Green applied!" << endl << endl;
	}
	//Effect [3] ****************************************
	cout << "[3] Apply Negate Blue? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			negate_blue();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Negate Blue applied!" << endl << endl;
	}
	//Effect [4] ****************************************
	cout << "[4] Apply Flip Horizontal? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			flip_horizontal();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Flip Horizontal applied!" << endl << endl;
	}
	//Effect [5] ****************************************
	cout << "[5] Apply Convert to Greyscale? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			grey_scale();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Convert to Greyscale applied!" << endl << endl;
	}
	//Effect [6] ****************************************
	cout << "[6] Apply Flatten Red? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			flatten_red();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Flatten Red applied!" << endl << endl;
	}
	//Effect [7] ****************************************
	cout << "[7] Apply Flatten Green? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			flatten_green();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Flatten Green applied!" << endl << endl;
	}
	//Effect [8] ****************************************
	cout << "[8] Apply Flatten Blue? (y/n)  ";
	cin >> yesno;
	if(yesno == 'y'){
		image_setup(st_in, st_out, fi_in, fi_out);
		cout << "One moment please... ";
		for(int j=0; j < rows; j++){
			for(int i=0; i < cols*3; i++){
				st_in >> data[i];
			}
			flatten_blue();
			for(int i=0; i < cols*3; i++){
				st_out << data[i] << " ";
			}
			st_out << endl;
		}
		cout << "Flatten Blue applied!" << endl << endl;

	}
	st_in.close();
	st_out.close();
	return;
}